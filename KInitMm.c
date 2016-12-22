#include "Jaura.h"
#include "Types.h"
#include "Errors.h"
#include "KInit.h"
#include "KVmm.h"
#include "KHeap.h"

extern UINT		 fstart;				//available physical memory
extern UINT	 	 fstartv;				//available virtual memory
extern VMA 		*VmaAvlList;			//available VMA linked list
extern VMA 		*VmaList;				//all VMA linked list from beginning

extern HEAP 	*HeapdHeapFirst;		//HEAP list storing HEAP descs
extern HEAP 	*HeapdHeap;				//current active HEAP desc's heap
extern HEAP 	*HeapdHeapRescue;		//last allocated HEAP desc 4 rescue

extern HEAP 	*VmadHeapFirst;			//HEAP list storing VMA desc
extern HEAP 	*VmadHeap;				//same as above
extern HEAP 	*VmadHeapRescue;		//same...

/* These are the most first descriptors that will be initialized in KInitMm.
 * It will also linked to above pointers at initialization */
HEAP		heapd_heap_first;
HEAP		vmad_heap_first;
VMA			heapd_heap_first_vma;
VMA		 	vmad_heap_first_vma;
VMA		 	remaining_free_vma;


void KInitMm() {
	UINT vmad_buffer_first		= KiValloc(0x100000); //64kb
	UINT heapd_buffer_first		= KiValloc(0x100000); //64kb
	//setup vmad_heap
	vmad_heap_first_vma.magic	= VMA_MAGIC;
	vmad_heap_first_vma.start	= vmad_buffer_first;
	vmad_heap_first_vma.end		= vmad_buffer_first + 0x100000;
	vmad_heap_first_vma.state	= 1;
	vmad_heap_first_vma.flags	= 0;
	vmad_heap_first_vma.left	= 0;
	vmad_heap_first_vma.right	= &heapd_heap_first_vma;
	vmad_heap_first_vma.prev	= 0;
	vmad_heap_first_vma.next	= 0;
	
	vmad_heap_first.magic		= HEAP_MAGIC;
	vmad_heap_first.start		= vmad_buffer_first;
	vmad_heap_first.end			= vmad_buffer_first + 0x100000;
	vmad_heap_first.chunks		= (HCHUNK*) vmad_buffer_first;
	vmad_heap_first.fchunk		= (HCHUNK*) vmad_buffer_first;
	vmad_heap_first.vma			= &vmad_heap_first_vma;
	vmad_heap_first.expander	= 0;

	HCHUNK *chunk = (HCHUNK*) vmad_buffer_first;
	chunk->magic	= HCHUNK_MAGIC;
	chunk->state 	= 0;
	chunk->size 	= 0x100000 - sizeof(HCHUNK);
	chunk->left 	= 0;
	chunk->right 	= 0;
	chunk->next 	= 0;
	chunk->heap 	= &vmad_heap_first;
	
	//setup heapd_heap
	heapd_heap_first_vma.magic	= VMA_MAGIC;
	heapd_heap_first_vma.start	= heapd_buffer_first;
	heapd_heap_first_vma.end	= heapd_buffer_first + 0x100000;
	heapd_heap_first_vma.state	= 1;
	heapd_heap_first_vma.flags	= 0;
	heapd_heap_first_vma.left	= &vmad_heap_first_vma;
	heapd_heap_first_vma.right	= &remaining_free_vma;
	heapd_heap_first_vma.prev	= 0;
	heapd_heap_first_vma.next	= 0;
	
	heapd_heap_first.magic		= HEAP_MAGIC;
	heapd_heap_first.start		= heapd_buffer_first;
	heapd_heap_first.end		= heapd_buffer_first + 0x100000;
	heapd_heap_first.chunks		= (HCHUNK*) heapd_buffer_first;
	heapd_heap_first.fchunk		= (HCHUNK*) heapd_buffer_first;
	heapd_heap_first.vma		= &heapd_heap_first_vma;
	heapd_heap_first.expander	= 0;
	
	chunk = (HCHUNK*) heapd_buffer_first;
	chunk->magic	= HCHUNK_MAGIC;
	chunk->state 	= 0;
	chunk->size 	= 0x100000 - sizeof(HCHUNK);
	chunk->left 	= 0;
	chunk->right 	= 0;
	chunk->prev		= 0;
	chunk->next 	= 0;
	chunk->heap 	= &heapd_heap_first;

	//remaining free vma
	remaining_free_vma.magic	= VMA_MAGIC;
	remaining_free_vma.start	= fstartv;
	remaining_free_vma.end		= 0xffc00000;
	remaining_free_vma.state	= 0;
	remaining_free_vma.flags	= 0;
	remaining_free_vma.left		= 0;
	remaining_free_vma.right	= 0;
	remaining_free_vma.prev		= 0;
	remaining_free_vma.next		= 0;

	VmadHeapFirst	= &vmad_heap_first;
	VmadHeap		= &vmad_heap_first;
	HeapdHeapFirst	= &heapd_heap_first;
	HeapdHeap		= &heapd_heap_first;
	
	VmaList 		= &remaining_free_vma;
	VmaAvlList 		= &remaining_free_vma;
}
