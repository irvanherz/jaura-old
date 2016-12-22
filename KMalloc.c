#include "KHeap.h"

HEAP *MallocHeap;

int KMallocInit(){
	MallocHeap = MmHeapCreate(0x100000);
	if(!MallocHeap) return -1;
	else return 0;
}

void *KMalloc(UINT size){
	return MmHeapAlloc(MallocHeap,size);
}

void *KRealloc(void *addr,UINT newsize){
	return MmHeapRealloc(MallocHeap,addr,newsize);
}

int KFree(void *addr){
	return MmHeapFree(addr);
}