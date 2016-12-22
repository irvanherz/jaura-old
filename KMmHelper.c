#include "Jaura.h"
#include "Types.h"
#include "Errors.h"
#include "KInit.h"
#include "KVmm.h"
#include "KHeap.h"


extern UINT		 fstart;				//available physical memory
extern UINT		 fstartv;				//available virtual memory
extern VMA 		*VmaAvlList;			//available VMA linked list
extern VMA 		*VmaList;				//all VMA linked list from beginning

HEAP 			*HeapdHeapFirst;		//HEAP list storing HEAP descs
HEAP 			*HeapdHeap;				//current active HEAP desc's heap
HEAP 			*HeapdHeapRescue;		//last allocated HEAP desc 4 rescue

HEAP 			*VmadHeapFirst;			//HEAP list storing VMA desc
HEAP 			*VmadHeap;				//same as above
HEAP 			*VmadHeapRescue = 1;		//same...


HEAP * MmAllocHeapDescriptor(){
	HEAP *result;
	result = MmHeapAlloc(HeapdHeap,sizeof(HEAP));
	if(result){
		memset(result,0,sizeof(HEAP));
		return result;
	}
	else return 0;
}

VMA	*MmAllocVmaDescriptor() {
	VMA *result;
	
	result = MmHeapAlloc(VmadHeap,sizeof(VMA));
	if(result){
		memset(result,0,sizeof(VMA));
		return result;
	}
	else return 0;
}

int MmFreeHeapDescriptor(HEAP *heap){
	if(!heap) return ERROR_INVALID;
	if(MmHeapFree(heap)) return SUCCESS;
	else return ERROR_BAD_ADDRESS;
}

int MmFreeVmaDescriptor(VMA *vma){
	if(!vma) return ERROR_INVALID;
	if(MmHeapFree(vma)) return SUCCESS;
	else return ERROR_BAD_ADDRESS;
}