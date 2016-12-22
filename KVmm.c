#include "Types.h"
#include "Jaura.h"
#include "Errors.h"
#include "KVmm.h"
#include "KHeap.h"

extern VMA * MmAllocVmaDescriptor();
extern int MmFreeVmaDescriptor();

VMA * VmaAvlList	= 0;
VMA * VmaList		= 0;


INLINEFUNC void vma_add_freelist(VMA **list, VMA *vma){
	vma->next = *list;
	vma->prev = 0;
	if(*list) (*list)->prev = vma;
	*list = vma;
}

INLINEFUNC void vma_escape_free(VMA **list, VMA *vma){
	if (!vma->prev){
		*list = vma->next;
		//if(*list) (*list)->prev = 0;
	}
	//if(!vma->prev && !vma->next)*list=0;
	
	if(vma->next) vma->next->prev = vma->prev;
	if(vma->prev) vma->prev->next = vma->next;
	vma->prev=0;
	vma->next=0;
}

INLINEFUNC void vma_lr_insert(VMA *left, VMA *vma){
	VMA *right	= left->right;
	if (left) left->right = vma;
	if (right) right->left = vma;
	
	vma->right = right;
	vma->left = left;
}

INLINEFUNC void vma_pn_insert(VMA *prev, VMA *vma){
	VMA *next = prev->next;
	if(next) next->prev = vma;
	prev->next = vma;
	vma->next = next;
	vma->prev = prev;
}

INLINEFUNC void vma_pn_escape(VMA *vma){
	VMA *prev = vma->prev;
	VMA *next = vma->next;
	
	if(prev) prev->next = next;
	if(next) next->prev = prev;
	vma->prev = 0;
	vma->next = 0;
}

INLINEFUNC void vma_lr_join(VMA *lvma, VMA *rvma){
	lvma->end = rvma->end;
	lvma->right = rvma->right;
	rvma->magic = 0;
	if(rvma->right) rvma->right->left = lvma;
	MmFreeVmaDescriptor(rvma);
}


VMA *VmmAllocVma(UINT size){
	size = PAGE_ALIGN(size);
	VMA *vma = VmaAvlList;
	
	while(vma){
		if (vma->end - vma->start < size){
			vma = vma->next;
			continue;
		}
		
		if (vma->end - vma->start == size){
			if(vma->prev == 0) VmaAvlList = vma->next;
			vma->state = 1;
			vma_escape_free(&VmaAvlList,vma);
			return vma;
		}
		
		else {
			VMA *nvma = MmAllocVmaDescriptor();//malloc(sizeof(VMA));
			nvma->start = vma->start + size;
			nvma->end = vma->end;
			nvma->magic = VMA_MAGIC;
			vma->end = vma->start + size;
			
			vma_lr_insert(vma,nvma);
			vma_add_freelist(&VmaAvlList,nvma);
			vma_escape_free(&VmaAvlList,vma);
			vma->state = 1;
			return vma;
		}
	}
	return 0;
}

void VmmDumpFreeVma(){
	KPrintf("Free VMA Descriptor dump:\n");
	VMA *vma = VmaAvlList;
	while(vma){
		VmmDumpVma(vma);
		vma = vma->next;
	}
}

int VmmFreeVma(VMA *vma){
	if(!vma) return ERROR_INVALID;
	if(vma->magic != VMA_MAGIC) return ERROR_INVALID;
	if(!vma->state) return ERROR_INVALID;
	
	VMA *left = vma->left;
	VMA *right = vma->right;
	vma->state = 0;
	if(right){
		if(!right->state){
			vma_escape_free(&VmaAvlList,right);
			vma_lr_join(vma,right);
		}
	}
	if(left){
		if(!left->state){
			vma_escape_free(&VmaAvlList,left);
			vma_lr_join(left,vma);
			vma = left;
		}
	}
	vma_add_freelist(&VmaAvlList,vma);
	return SUCCESS;
}

void VmmDumpVma(VMA *vma){
	KPrintf("At %x MAGIC %x, state %x start %x end %x, flags %x, left %x, right %x, prev %x, next %x\n",
	vma, vma->magic,vma->state,vma->start,vma->end,vma->flags,vma->left,vma->right,vma->prev,vma->next);
}

void VmmDumpAllVma(){
	KPrintf("All VMA Descriptor dump:\n");
	VMA *vma = VmaList;
	while(vma){
		VmmDumpVma(vma);
		vma = vma->right;
	}
}

INLINEFUNC void virtual_map(UINT va, UINT pa){
	UINT ipte = va / PAGE_SIZE;
	UINT ipde = ipte / 1024;
	if (!PDE(ipde))
		PDE(ipde) = AvlFrameGet() | 3;
	PTE(ipte) = pa | 3;
}

VMA * KVirtualAlloc(UINT size){
	if(!size){
		KPrint("Alloc zero no OK\n");
		return 0;
	}
	VMA *vma;
	vma = VmmAllocVma(size);
	if(!vma){
		KPrint("KVAlloc Fail alloc VMA\n");
		return 0;
	}
	UINT va = vma->start, endva = vma->end;
	while(va < endva){
		virtual_map(va,AvlFrameGet());
		va += PAGE_SIZE;
	}
	return vma;
}
