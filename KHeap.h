#ifndef KHEAP_H
#define KHEAP_H

#include "Jaura.h"
#include "Types.h"
#include "Configs.h"
#include "KVmm.h"

#define HCHUNK_MAGIC 0x48434E4B

typedef struct _HCHUNK{
	UINT				 magic;
	UINT				 state;
	void 				*heap; //HEAP*
	UINT				 size;
	struct _HCHUNK		*left,*right;
	struct _HCHUNK		*prev,*next;
} HCHUNK;

#define HEAP_MAGIC 0x48454150
typedef struct _HEAP{
	UINT			 magic;
	VMA				*vma;
	UINT			 start;
	UINT			 end;
	HCHUNK			*chunks;
	HCHUNK			*fchunk;
	struct _HEAP	*expander;
} HEAP;

HEAP *MmHeapCreate(UINT);
void *MmHeapAlloc(HEAP *, UINT);
int MmHeapFree(void *addr);


#endif