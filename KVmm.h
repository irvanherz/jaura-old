#ifndef KVMM_H
#define KVMM_H

#include "Jaura.h"
#include "Types.h"
#include "Configs.h"


#define PAGE_PRESENT		0x1
#define PAGE_WRITABLE		0x2
#define PAGE_USER			0x4
#define PAGE_WRITETROUGH	0x8
#define PAGE_NOCACHE		0x10


#define PTE(i) *((ULONG*)(0xFFC00000 + i * 4))
#define PDE(i) *((ULONG*)(0xFFFFF000 + i * 4))


#define PAGE_ALIGN(addr) ((addr + (PAGE_SIZE - 1)) & ~(PAGE_SIZE - 1))

#define VMA_MAGIC	0x564D4130 //VMA0

typedef struct _VMA {
	int				 magic;				//this should be VMA_MAGIC
	UINT			 start;				//start of memory area
	UINT			 end;				//end of memory area + 1
	UINT			 state;				//0 for free 
	UINT			 flags;				//this VMA property
	struct _VMA		*left, *right;		//linked list connect between VMA
	struct _VMA		*prev, *next;		//linked list connect between free VMA
} VMA;

VMA *VmmAllocVma(UINT);
VMA *VmmAllocVmaEx(UINT,UINT);

#endif
