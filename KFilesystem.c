#include "Types.h"
#include "Errors.h"
#include "KFilesystem.h"
#include "DList.h"


DLIST FilesystemList;
DLIST MountList;

void FsInit(){
	MemFill(FilesystemList,0,sizeof(DLIST));
	MemFill(MountList,0,sizeof(DLIST));
}
FILESYSTEM *FsFindFilesystem(char *fsname){
	DLIST_NODE *fs = FilesystemList.firstNode;
	
	while (fs){
		if(StrCompare(((FILESYSTEM *)fs->data)->name,fsname) == 0)
			break;
		fs = fs->next;
	}
	return fs->data;
}

int FsRegister(FILESYSTEM *fs){
	if(!fs) return ERROR_INVALID;
	fs->lnode.data = fs;
	DListAppend(&FilesystemList,&fs->lnode);
	return 0;
}

int FsUnregister(FILESYSTEM *fs){
	if(!fs) return ERROR_INVALID;
	DListUnlink(&FilesystemList,&fs->lnode);
	return 0;
}

int FsMountRoot(FILESYSTEM *fs,FNODE *deviceFnode,void *data){
	MOUNT *mount = (MOUNT *) KMalloc(sizeof(MOUNT));
	mount->fs = fs;
	mount->fsMethod = fs->method;
	mount->deviceFnode = deviceFnode;
	mount->lnode.data = mount;
	DListAppend(&MountList,&mount->lnode);
	mount->fsMethod->mount(mount);
	return 0;
}

int FsMount(FILESYSTEM *fs,FNODE *deviceFnode,FNODE *target,void *data){
	MOUNT *mount = (MOUNT *) KMalloc(sizeof(MOUNT));
	mount->fs = fs;
	mount->fsMethod = fs->method;
	mount->deviceFnode = deviceFnode;
	mount->coveredFnode = target;
	mount->lnode.data = mount;
	DListAppend(&MountList,&mount->lnode);
	mount->fsMethod->mount(mount);
	target->cover = mount->rootFnode;
	return 0;
}

MOUNT *FsGetRootMount(){
	return MountList.firstNode->data;
}

int FnodeLookup(FNODE *fnode,char *fname,FNODE **resnode){
	//KPrintf("Lookup %s\n",fname);
	if(!fnode) return -1;
	if(fnode->cover) fnode = fnode->cover;
	fnode->method->lookup(fnode,fname,resnode);
	return 0;
}

int FnodeCreate(FNODE *fnode,char *fname){
	if(!fnode) return -1;
	fnode->method->create(fnode,fname);
	return 0;
}

int FnodeMkdir(FNODE *fnode,char *fname){
	if(!fnode) return -1;
	fnode->method->mkdir(fnode,fname);
	return 0;
}

#define MAX_PATH 255
int FsLookup(FNODE *base, char *path,FNODE **resfnode){
	char 	fnodeName[MAX_PATH];
	int 	ifn;
	FNODE	*fnode, *nextFnode;
	
	if(!base){
		fnode = FsGetRootMount()->rootFnode;
		FnodeEnter(fnode);
	}
	else{
		fnode = base;
		FnodeEnterAll(fnode);
	}
	
	if(*path == '/') path++;
	while(*path){
		for(ifn=0;(*path != '/') && (*path != 0);ifn++){
			fnodeName[ifn] = *path;
			path++;
		}
		fnodeName[ifn] = 0;
		
		FnodeLookup(fnode,fnodeName,&nextFnode);
		if(nextFnode){
			fnode = nextFnode;
			FnodeEnter(fnode);
		}
		else {
			KPrintf("Oops\n");
			FnodeLeaveAll(fnode);
			return -1;
		}
		//KPrintf("fnodeName: '%s'\n",fnodeName);
		if(*path == 0){
			if(path[1] == 0) break;
		}
		if(*path == 0) break;
		else path++;
	}
	*resfnode = fnode;
	return 0;
}

int FsMkdir(FNODE *base, char *path){
	char fnodeName[MAX_PATH];
	int ifn = 0;
	FNODE *pnode = 0;
	FNODE *cnode = 0;
	
	if(!base){
		pnode = FsGetRootMount()->rootFnode;
		FnodeEnter(pnode);
	}
	else{
		pnode = base;
		FnodeEnterAll(pnode);
	}

	if(*path == '/') path++;
	
	while(*path){
		for(ifn = 0;(*path != '/') && (*path != 0);ifn++){
			fnodeName[ifn] = *path;
			path++;
		}
		fnodeName[ifn] = 0;
		
		//ok, now check wether there is no name left?
		if(*path == '/') //more? ok continue
			path++;
		if(*path == 0)	//no? break. now fnode name are name for new dir
			break;
		//still more name, lookup it
		FnodeLookup(pnode,fnodeName,&cnode);
		if(cnode){ //yeah node found
			//KPrint("Found cnode\n");
			if(cnode->type == FNODE_DIRECTORY) //but check it first. is it directory?
				FnodeEnter(cnode);		//ou yeah, enter it
			else {						//no? leave it. you make bad request!
				FnodeLeaveAll(cnode);
				return -1;
			}
		}
		else {						// I will leave it too, if i cant find name
			//KPrintf("Not found cnode %s\n",fnodeName);
			FnodeLeaveAll(pnode);
			return 0;
		}
		//now, find next fnodename
		pnode = cnode;
		ifn = 0;
	}
	if(StrLength(fnodeName) == 0){ //Nothing to be done. this happen when we have 2 tail sparators
		FnodeLeaveAll(pnode);
		//KPrint("no directory to be created\n");
		return -1;
	}
	//now last step
	pnode->method->mkdir(pnode,fnodeName);
	FnodeLeaveAll(pnode);
	return 0;
}

int FsCreate(FNODE *base, char *path){
	char fnodeName[MAX_PATH];
	int ifn = 0;
	FNODE *pnode = 0;
	FNODE *cnode = 0;
	
	if(!base){
		pnode = FsGetRootMount()->rootFnode;
		FnodeEnter(pnode);
	}
	else{
		pnode = base;
		FnodeEnterAll(pnode);
	}

	if(*path == '/') path++;
	
	while(*path){
		for(ifn = 0;(*path != '/') && (*path != 0);ifn++){
			fnodeName[ifn] = *path;
			path++;
		}
		fnodeName[ifn] = 0;
		
		//ok, now check wether there is no name left?
		if(*path == '/') //more? ok continue
			path++;
		if(*path == 0)	//no? break. now fnode name are name for new dir
			break;
		//still more name, lookup it
		FnodeLookup(pnode,fnodeName,&cnode);
		if(cnode){ //yeah node found
			//KPrint("Found cnode\n");
			if(cnode->type == FNODE_DIRECTORY) //but check it first. is it directory?
				FnodeEnter(cnode);		//ou yeah, enter it
			else {						//no? leave it. you make bad request!
				FnodeLeaveAll(cnode);
				return -1;
			}
		}
		else {						// I will leave it too, if i cant find name
			//KPrintf("Not found cnode %s\n",fnodeName);
			FnodeLeaveAll(pnode);
			return 0;
		}
		//now, find next fnodename
		pnode = cnode;
		ifn = 0;
	}
	if(StrLength(fnodeName) == 0){ //Nothing to be done. this happen when we have 2 tail sparators
		FnodeLeaveAll(pnode);
		//KPrint("no directory to be created\n");
		return -1;
	}
	//now last step
	pnode->method->create(pnode,fnodeName);
	FnodeLeaveAll(pnode);
	return 0;
}

int FsMknod(FNODE *base, char *path,ULONG devid){
	char fnodeName[MAX_PATH];
	int ifn = 0;
	FNODE *pnode = 0;
	FNODE *cnode = 0;
	
	if(!base){
		pnode = FsGetRootMount()->rootFnode;
		FnodeEnter(pnode);
	}
	else{
		pnode = base;
		FnodeEnterAll(pnode);
	}

	if(*path == '/') path++;
	
	while(*path){
		for(ifn = 0;(*path != '/') && (*path != 0);ifn++){
			fnodeName[ifn] = *path;
			path++;
		}
		fnodeName[ifn] = 0;
		
		//ok, now check wether there is no name left?
		if(*path == '/') //more? ok continue
			path++;
		if(*path == 0)	//no? break. now fnode name are name for new dir
			break;
		//still more name, lookup it
		FnodeLookup(pnode,fnodeName,&cnode);
		if(cnode){ //yeah node found
			//KPrint("Found cnode\n");
			if(cnode->type == FNODE_DIRECTORY) //but check it first. is it directory?
				FnodeEnter(cnode);		//ou yeah, enter it
			else {						//no? leave it. you make bad request!
				FnodeLeaveAll(cnode);
				return -1;
			}
		}
		else {						// I will leave it too, if i cant find name
			//KPrintf("Not found cnode %s\n",fnodeName);
			FnodeLeaveAll(pnode);
			return 0;
		}
		//now, find next fnodename
		pnode = cnode;
		ifn = 0;
	}
	if(StrLength(fnodeName) == 0){ //Nothing to be done. this happen when we have 2 tail sparators
		FnodeLeaveAll(pnode);
		//KPrint("no directory to be created\n");
		return -1;
	}
	//now last step
	pnode->method->mknod(pnode,fnodeName,devid);
	FnodeLeaveAll(pnode);
	return 0;
}