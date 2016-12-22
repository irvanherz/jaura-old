#include "KHeap.h"
#include "KFilesystem.h"
#include "Device.h"

int TmpfsMount(MOUNT *);
int TmpfsCreate(FNODE *fnode,char *name);
int TmpfsMkdir(FNODE *fnode,char *name);
int TmpfsMknod(FNODE *fnode,char *name,DEVICE_ID devid);
int TmpfsLookup(FNODE *fnode,char *name,FNODE **resnode);
int TmpfsRead(FNODE *fnode,void *buffer,UINT offset,UINT size);
int TmpfsWrite(FNODE *fnode,void *buffer,UINT offset,UINT size);

typedef struct _TMPFS_NODE TMPFS_NODE;
typedef struct TMPFS_SUPER{
	HEAP			*heap;
	TMPFS_NODE		*rootNode;
}TMPFS_SUPER;

typedef enum _TMPFS_NODE_TYPE{NODE_REGULAR,NODE_DIRECTORY} TMPFS_NODE_TYPE;
struct _TMPFS_NODE{
	char				*name;
	TMPFS_NODE_TYPE		 type;
	UINT				 size;
	void				*data;
	DLIST_NODE			 myNode;
	struct _TMPFS_NODE	*parentNode;
	DLIST				 childNodes;
};


FILESYSTEM_METHOD TmpfsMethod = {
	.mount = &TmpfsMount
};

FILESYSTEM Tmpfs = {
	.name = "tmpfs",
	.method = &TmpfsMethod
};

FNODE_METHOD TmpfsFnodeMethod = {
	.create = &TmpfsCreate,
	.mkdir = &TmpfsMkdir,
	.mknod = &TmpfsMknod,
	.lookup = &TmpfsLookup,
	.read = &TmpfsRead,
	.write = &TmpfsWrite
};


int TmpfsMount(MOUNT *mount){
	TMPFS_SUPER		*super;
	HEAP			*tmpfsHeap;
	TMPFS_NODE		*rootNode;
	FNODE			*rootFnode;
	
	//init super
	tmpfsHeap = MmHeapCreate(0x100000);
	super = MmHeapAlloc(tmpfsHeap,sizeof(TMPFS_SUPER));
	super->heap = tmpfsHeap;
	mount->data = super;
	//create root tnode
	rootNode = KMalloc(sizeof(TMPFS_NODE));
	rootNode->type = NODE_DIRECTORY;
	//create root fnode
	rootFnode = FnodeAlloc();
	rootFnode->method = &TmpfsFnodeMethod;
	rootFnode->data = rootNode;
	rootFnode->type = FNODE_DIRECTORY;
	rootFnode->ownerMount = mount;
	rootFnode->parentNode = 0;
	FnodeEnter(rootFnode);
	//setup
	mount->rootFnode = rootFnode;
}

int tmpfs_compare_tnode_name(TMPFS_NODE *tnode,char *name){
	return StrCompare(tnode->name,name);
}

int tmpfs_compare_fnode_name(FNODE *fnode,char *name){
	TMPFS_NODE *tnode = fnode->data;
	return StrCompare(tnode->name,name);
}

FNODE * tmpfs_lookup_real(FNODE *fnode,char *name){
	DLIST_NODE *child_lnode;
	TMPFS_NODE *tnode;
	FNODE *newFnode;
	//KPrint("Real lookup\n");
	tnode = fnode->data;
	child_lnode = tnode->childNodes.firstNode;
	while(child_lnode){
		if(tmpfs_compare_tnode_name(child_lnode->data,name) == 0){
			tnode = child_lnode->data;
			newFnode = FnodeAlloc();
			newFnode->data = child_lnode->data;
			newFnode->parentNode = fnode;
			newFnode->ownerMount = fnode->ownerMount;
			newFnode->myNode.data = newFnode;
			newFnode->method = &TmpfsFnodeMethod;
			if(tnode->type == NODE_DIRECTORY) newFnode->type = FNODE_DIRECTORY;
			else if(tnode->type == NODE_REGULAR) newFnode->type = FNODE_REGULAR;
			DListAppend(&fnode->childNodes,&newFnode->myNode);
			return newFnode;
		}
		child_lnode = child_lnode->next; 
	}
	//KPrint("Real lookup not found\n");
	return 0;
}

FNODE * tmpfs_lookup_child(FNODE *fnode,char *name){
	DLIST_NODE	*child_lnode;

	//KPrint("Child lookup\n");
	child_lnode = fnode->childNodes.firstNode;
	while(child_lnode){
		if(tmpfs_compare_fnode_name(child_lnode->data,name) == 0){
			return child_lnode->data;
		}
		child_lnode = child_lnode->next;
	}
	//KPrint("Child lookup not found\n");
	return 0;
}

int TmpfsLookup(FNODE *fnode,char *name,FNODE **resnode){
	FNODE *found;

	if(fnode->type != FNODE_DIRECTORY) return -1;
	
	*resnode = 0;
	found = tmpfs_lookup_child(fnode,name);		//find last opened node
	if(!found)
		found = tmpfs_lookup_real(fnode,name);	//if not, find from disk
	if(!found) return -1;
	FnodeEnter(found);							//increase ref count
	*resnode = found;
	//KPrint("TMPFS lookup found\n");
	return 0;
}

int TmpfsCreate(FNODE *fnode,char *name){
	FNODE		*found;
	TMPFS_NODE	*tnode;
	TMPFS_NODE	*newTnode;
	
	if(fnode->type != FNODE_DIRECTORY) return -1;
	TmpfsLookup(fnode,name,&found);
	if(found){
		FnodeLeave(found);
		return -1;
	}
	//create new tnode
	tnode = fnode->data;
	newTnode = KMalloc(sizeof(TMPFS_NODE));
	newTnode->myNode.data = newTnode;
	newTnode->parentNode = tnode;
	newTnode->type = NODE_REGULAR;
	newTnode->name = KMalloc(StrLength(name) + 1);
	StrCopy(newTnode->name,name);
	DListAppend(&tnode->childNodes,&newTnode->myNode);
}

int att = 0;
int TmpfsMkdir(FNODE *fnode,char *name){
	FNODE		*found;
	TMPFS_NODE	*tnode;
	TMPFS_NODE	*newTnode;
	TMPFS_SUPER	*tsuper;
	
	if(fnode->type != FNODE_DIRECTORY) return -1;
	TmpfsLookup(fnode,name,&found);
	if(found){
		FnodeLeave(found);
		return -1;
	}
	//create new tnode
	tnode = fnode->data;
	tsuper = fnode->ownerMount->data;
	
	newTnode = KMalloc(sizeof(TMPFS_NODE));
	newTnode->myNode.data = newTnode;
	newTnode->parentNode = tnode;
	newTnode->type = NODE_DIRECTORY;
	newTnode->name = KMalloc(StrLength(name) + 1);
	StrCopy(newTnode->name,name);
	DListAppend(&tnode->childNodes,&newTnode->myNode);

}

int TmpfsMknod(FNODE *fnode,char *name, DEVICE_ID devid){
	FNODE		*found;
	TMPFS_NODE	*tnode;
	TMPFS_NODE	*newTnode;
	TMPFS_SUPER	*tsuper;
	FNODE_METHOD *dmethod;

	dmethod = DeviceGetMethod(devid);
	if(!dmethod)
		return -1;
	
	if(fnode->type != FNODE_DIRECTORY) return -1;
	TmpfsLookup(fnode,name,&found);
	if(found){
		FnodeLeave(found);
		return -1;
	}
	//create new tnode
	tnode = fnode->data;
	tsuper = fnode->ownerMount->data;
	
	newTnode = KMalloc(sizeof(TMPFS_NODE));
	newTnode->myNode.data = newTnode;
	newTnode->parentNode = tnode;
	newTnode->type = NODE_DIRECTORY;
	newTnode->name = KMalloc(StrLength(name) + 1);
	newTnode->data = (void*)devid;
	StrCopy(newTnode->name,name);
	DListAppend(&tnode->childNodes,&newTnode->myNode);
	
	TmpfsLookup(fnode,name,&found);
	if(found){
		found->method = dmethod;
		//FnodeLeave(found); Device node better only released on deletion
		return 0;
	}
	else return -1;
}
int TmpfsRead(FNODE *fnode,void *buffer,UINT offset,UINT size){
	TMPFS_NODE	*tnode = fnode->data;
	UINT		 eoffset = offset + size;
	if(!buffer || !size) return 0;
	if(offset >= tnode->size) return 0;
	
	//KPrintf("Try read @ tnode %x cur content:'%s' and tsize %d\n",tnode,tnode->data,tnode->size);
	
	if(eoffset < tnode->size){
		MemCopy(buffer,tnode->data+offset,size);
		return size;
	}
	else {	
		MemCopy(buffer,tnode->data+offset,tnode->size - offset);
		return tnode->size - offset;
	}
}

int TmpfsWrite(FNODE *fnode,void *buffer,UINT offset,UINT size){
	TMPFS_NODE	*tnode = fnode->data;
	UINT		 eoffset = offset + size; 
	if(!buffer || !size) return 0;

	//first expand if needed
	if(eoffset > tnode->size){
		if(!tnode->data){
			tnode->data = KMalloc(eoffset);
			tnode->size = eoffset;
		}
		else{
			tnode->data = KRealloc(tnode->data,eoffset);
			tnode->size = eoffset;
		}
	}
	
	MemCopy((void*)(UINT)tnode->data + offset,buffer,size);
	return size;
}

int TmpfsInit(){
	FsRegister(&Tmpfs);
}