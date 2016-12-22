#include "Types.h"
#include "DList.h"
#include "KFilesystem.h"

FNODE *FnodeLookupChild(FNODE *fnode,char *name){
	DLIST_NODE	*child_lnode;

	//KPrint("Child lookup\n");
	child_lnode = fnode->childNodes.firstNode;
	while(child_lnode){
		if(((FNODE*)child_lnode->data)->name){
			if (StrCompare(((FNODE*)child_lnode->data)->name,name) == 0)
				return child_lnode->data;
		}
		child_lnode = child_lnode->next;
	}
	//KPrint("Child lookup not found\n");
	return 0;
}

void FnodeAddChild(FNODE *p,FNODE *c){
	c->parentNode = p;
	c->myNode.data = c;
	DListAppend(&p->childNodes,&c->myNode);
}

void FnodeDelChild(FNODE *p,FNODE *c){
	c->parentNode = 0;
	DListUnlink(&p->childNodes,&c->myNode);
}

FNODE *FnodeAlloc(){
	FNODE *fnode;
	fnode = KMalloc(sizeof(FNODE));
	MemFill(fnode,0,sizeof(FNODE));
	return fnode;
}

FNODE *FnodeDuplicate(FNODE *fnode){
	FNODE *newFnode;
	newFnode = KMalloc(sizeof(FNODE));
	MemCopy(newFnode,fnode,sizeof(FNODE));
	return newFnode;
}

void FnodeFree(FNODE *fnode){
	FNODE *pfnode;
	pfnode = fnode->parentNode;
	if(pfnode)
		DListUnlink(&pfnode->childNodes,fnode);
	KFree(fnode);
}

void FnodeEnter(FNODE *fnode){
	fnode->refCount++;
}

void FnodeLeave(FNODE *fnode){
	if(fnode->refCount) fnode->refCount--;
	if(!fnode->refCount)
		FnodeFree(fnode);
}

void FnodeEnterAll(FNODE *fnode){
	while(fnode){
		fnode->refCount++;
		fnode = fnode->parentNode;
	}
}

void FnodeLeaveAll(FNODE *fnode){
	while(fnode){
		if(fnode->refCount) fnode->refCount--;
		if(!fnode->refCount)
			FnodeFree(fnode);
		fnode = fnode->parentNode;
	}
}

UINT FnodeRead(FNODE *fnode,void *buffer,UINT offset,UINT size){
	return fnode->method->read(fnode,buffer,offset,size);
}

UINT FnodeWrite(FNODE *fnode,void *buffer,UINT offset,UINT size){
	return fnode->method->write(fnode,buffer,offset,size);
}

UINT FnodeBread(FNODE *fnode,ULONGLONG sector,ULONG count,void** buffer){
	return fnode->method->bread(fnode,sector,count,buffer);
}