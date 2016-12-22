#include "Jaura.h"
#include "Types.h"
#include "Errors.h"
#include "KInit.h"
#include "KVmm.h"
#include "KHeap.h"

extern HEAP * MmAllocHeapDescriptor();
extern int MmFreeHeapDescriptor(HEAP *);

#define BLOCK_OF_HCHUNK(chunk) ((void*)((UINT)chunk + sizeof(HCHUNK)))
#define HCHUNK_OF_BLOCK(addr) ((HCHUNK*)((UINT)addr - sizeof(HCHUNK)))
#define HCHUNK_ALIGN(size) ((size + (32 - 1)) & ~(32 - 1))

HEAP *MmHeapCreate(UINT size){
	HEAP *heap;
	VMA *vma;
	heap = MmAllocHeapDescriptor(); //malloc(sizeof(HEAP));
	vma = KVirtualAlloc(size);
	HCHUNK *chunk = (HCHUNK*) vma->start;
	
	heap->magic = HEAP_MAGIC;
	heap->vma = vma;
	heap->start = vma->start;
	heap->end = vma->end;
	heap->fchunk = chunk;
	heap->chunks = chunk;
	
	chunk->magic = HCHUNK_MAGIC;
	chunk->state = 0;
	chunk->size = vma->end - vma->start - sizeof(HCHUNK);
	chunk->left = 0;
	chunk->right = 0;
	chunk->next = 0;
	chunk->heap = heap;
	
	return heap;
}

INLINEFUNC void hchunk_add_free(HEAP *heap, HCHUNK *chunk){
	chunk->next = heap->fchunk;
	chunk->prev = 0;
	if(heap->fchunk) heap->fchunk->prev = chunk;
	heap->fchunk = chunk;
}

INLINEFUNC void hchunk_escape_free(HEAP *heap, HCHUNK *chunk){
	if (!chunk->prev){
		heap->fchunk = chunk->next;
		if(heap->fchunk) heap->fchunk->prev = 0;
	}
	if(!chunk->prev && !chunk->next)heap->fchunk=0;
	
	if(chunk->next) chunk->next->prev = chunk->prev;
	if(chunk->prev) chunk->prev->next = chunk->next;
	chunk->prev=0;
	chunk->next=0;
}

INLINEFUNC void hchunk_lr_insert(HCHUNK *left, HCHUNK *chunk){
	HCHUNK *right	= left->right;
	left->right 	= chunk;
	if (right) right->left = chunk;
	
	chunk->right = right;
	chunk->left = left;
}

INLINEFUNC void hchunk_join(HCHUNK *lchunk,HCHUNK *rchunk){
	lchunk->size += sizeof(HCHUNK) + rchunk->size;
	lchunk->right = rchunk->right;
	rchunk->magic = 0;
	if(rchunk->right)rchunk->right->left = lchunk;
}

void *MmHeapAlloc(HEAP *heap, UINT size){
	size = HCHUNK_ALIGN(size);
	HCHUNK *chunk = heap->fchunk;
	
	while(chunk){
		if (chunk->size < size){
			chunk = chunk->next;
			continue;
		}
		
		if (chunk->size == size){
			chunk->state = 1;
			hchunk_escape_free(heap,chunk);
			return BLOCK_OF_HCHUNK(chunk);
		}
		
		else {
			if((chunk->size - size) < (sizeof(HCHUNK) + HCHUNK_ALIGN(1)) ){
				chunk->state = 1;
				return BLOCK_OF_HCHUNK(chunk);
			}
			else {
				HCHUNK *nchunk = (HCHUNK *)((UINT)chunk + sizeof(HCHUNK) + size);
				nchunk->magic = HCHUNK_MAGIC;
				nchunk->state = 0;
				nchunk->heap = chunk->heap;
				nchunk->size = chunk->size - size - sizeof(HCHUNK);
				chunk->state = 1;
				chunk->size = size;
				
				hchunk_lr_insert(chunk,nchunk);
				hchunk_escape_free(heap,chunk);
				hchunk_add_free(heap,nchunk);
				return BLOCK_OF_HCHUNK(chunk);
			}
		}
	}
	return 0;
}

void *MmHeapRealloc(HEAP *heap, void *addr, UINT newsize){
	HCHUNK	*chunk;
	void	*newaddr;

	if(!addr) return 0;
	chunk = HCHUNK_OF_BLOCK(addr);
	if(chunk->magic != HCHUNK_MAGIC) return 0;
	if(chunk->state == 0) return 0;
	
	newaddr = MmHeapAlloc(heap,newsize);
	if(!newaddr) return 0;
	
	if(newsize < chunk->size)
		MemCopy(newaddr,addr,newsize);
	else
		MemCopy(newaddr,addr,chunk->size);

	MmHeapFree(addr);
	return newaddr;
}

int MmHeapFree(void *addr){
	HCHUNK *lchunk,*chunk,*rchunk;

	if(!addr) return ERROR_INVALID;
	chunk = HCHUNK_OF_BLOCK(addr);
	if(chunk->magic != HCHUNK_MAGIC) return ERROR_INVALID;
	if(chunk->state == 0) return ERROR_INVALID;
	chunk->state = 0;
	HEAP *heap = chunk->heap;
	lchunk = chunk->left;
	rchunk = chunk->right;
	
	if (rchunk){
		if(rchunk->state == 0){
			hchunk_escape_free(heap,rchunk);
			hchunk_join(chunk,rchunk);
		}
	}
	if (lchunk){
		if(lchunk->state == 0){
			hchunk_escape_free(heap,lchunk);
			hchunk_join(lchunk,chunk);
			chunk = lchunk;
		}
	}
	hchunk_add_free(heap,chunk);
}

void MmDumpHchunk(HCHUNK *chunk){
	KPrintf("At %x MAGIC %x, state %x heap %x, size %x, left %x, right %x, prev %x, next %x\n",
	chunk, chunk->magic,chunk->state,chunk->heap,chunk->size,chunk->left,chunk->right,chunk->prev,chunk->next);
}

void MmDumpFreeHchunk(HEAP *heap){
	KPrintf("Free HCHUNK Descriptor dump:\n");
	HCHUNK *chunk = heap->fchunk;
	while(chunk){
		MmDumpHchunk(chunk);
		chunk = chunk->next;
	}
}

void MmDumpAllHchunk(HEAP *heap){
	KPrintf("All HCHUNK Descriptor dump:\n");
	HCHUNK *chunk = heap->chunks;
	while(chunk){
		MmDumpHchunk(chunk);
		chunk = chunk->right;
	}
}