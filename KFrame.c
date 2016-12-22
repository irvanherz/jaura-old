#include "Jaura.h"
#include "Configs.h"
#include "Types.h"
#include "Errors.h"
#include "Macros.h"
#include "KLib.h"
#include "KInit.h"
#include "KPmm.h"
#include "KVmm.h"



DWORD 	*AvlFrameBmap;
DWORD 	*AvlFrameStackBase;
DWORD 	*AvlFrameStackPtr;
DWORD 	*AvlFrameStackEnd;

#define DWMAP_OF_FRAME(addr) ((addr / PAGE_SIZE) / 32)
#define BMAP_OF_DWMAP(addr) ((addr / PAGE_SIZE) % 32)

extern PMA 		PmaTable[MAX_PMA];
extern UINT		fstart;
extern UINT		fstartv;

INLINEFUNC void avl_frame_push(UINT frame){
	*AvlFrameStackPtr = frame;
	AvlFrameStackPtr++;
}

INLINEFUNC UINT avl_frame_pop(){
	AvlFrameStackPtr--;
	if(AvlFrameStackPtr < AvlFrameStackBase) return 0;
	return *AvlFrameStackPtr;
}

INLINEFUNC void avl_frame_adds(UINT baddr, UINT eaddr){
	baddr = PAGE_ALIGN(baddr);
	eaddr = PAGE_ALIGN(eaddr - PAGE_SIZE);
	for(UINT addr = eaddr; addr > baddr; addr -= PAGE_SIZE){
		avl_frame_push(addr);
	}
	avl_frame_push(baddr);
}


INLINEFUNC BOOL avl_bmap_isset(UINT addr){
	DWORD *dwmap = AvlFrameBmap[DWMAP_OF_FRAME(addr)];
	DWORD bmap = BMAP_OF_DWMAP(addr);
	if(*dwmap & (1 << bmap)) return 1;
	else return 0;
}

INLINEFUNC BOOL avl_bmap_xset(UINT addr){
	DWORD *dwmap = &AvlFrameBmap[DWMAP_OF_FRAME(addr)];
	DWORD  bmap = BMAP_OF_DWMAP(addr);
	if(!(*dwmap & (1 << bmap))){
		*dwmap |= (1 << bmap);
		return 1;
	}
	else return 0;
}

INLINEFUNC BOOL avl_bmap_xunset(UINT addr){
	DWORD *dwmap = &AvlFrameBmap[DWMAP_OF_FRAME(addr)];
	DWORD bmap = BMAP_OF_DWMAP(addr);
	if(*dwmap & (1 << bmap)){
		*dwmap &= ~(1 << bmap);
		return 1;
	}
	else return 0;
}

INLINEFUNC void avl_bmap_sets(UINT baddr, UINT eaddr){
	while (baddr < eaddr){
		DWORD *dwmap = &AvlFrameBmap[DWMAP_OF_FRAME(baddr)];
		DWORD bmap = BMAP_OF_DWMAP(baddr);
		*dwmap |= (1 << bmap);
		baddr += PAGE_SIZE;
	}
}

INLINEFUNC void avl_bmap_unsets(UINT baddr, UINT eaddr){
	while (baddr < eaddr){
		DWORD *dwmap = &AvlFrameBmap[DWMAP_OF_FRAME(baddr)];
		DWORD bmap = BMAP_OF_DWMAP(baddr);
		*dwmap &= ~(1 << bmap);
		baddr += PAGE_SIZE;
	}
}

void AvlFrameInit(){
	PMA *first_pma	= PmaTable;
	PMA *pma 		= first_pma;
	
	UINT memsz		= PAGE_ALIGN(PmmCountAvlMemory());
	UINT stacksz	= ((memsz + PAGE_SIZE) / PAGE_SIZE) * 4;
	UINT bmapsz		= memsz / PAGE_SIZE / 8;
	
	//build stack
	AvlFrameStackBase	= (DWORD*) KiValloc(stacksz);
	AvlFrameStackPtr	= AvlFrameStackBase;
	AvlFrameStackEnd	= (DWORD*)((UINT)AvlFrameStackBase + stacksz);
	
	//build bmap
	AvlFrameBmap		= (DWORD*) KiValloc(bmapsz);
	
	//fill stack
	while (pma->magic == PMA_MAGIC){pma++;}
	while (pma >= first_pma){
		if(pma->flags == PMA_AVAILABLE)
			avl_frame_adds(pma->start,pma->start + pma->size);
			pma--;
	}
	
	//fill bmap
	memset((void*)AvlFrameBmap,0,bmapsz);
}

UINT AvlFrameGet(){
	UINT addr;
	
	get_addr:
	addr = avl_frame_pop();
	if(avl_bmap_xset(addr) == 0) goto get_addr; //failed exclusively set bitmap
	return addr;
}

UINT AvlFrameRelease(UINT addr){
	if(avl_bmap_xunset(addr) == 0) return 0; //failed exclusively set bitmap
	avl_frame_push(addr);
	return 1;
}

void EndKiValloc(){
	avl_bmap_sets(0,fstart);
}
