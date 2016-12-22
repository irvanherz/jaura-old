#include "Jaura.h"
#include "Types.h"
#include "Errors.h"
#include "KPmm.h"
#include "KVmm.h"


DWORD		*PageCommited;
DWORD		*PageReserved;
DWORD 		 FrameFirstFree = 0;


PMA PmaTable[MAX_PMA];


/**
 * @brief Instruct PMM to add PMA(Physical Memory Area) to list
 * @param dwStart
 * @param dwSize
 * @param dwFlags
 */
void PmmAddPma (UINT start, UINT size, UINT flags){
	PPMA ppma = PmaTable;
	while (ppma->magic == PMA_MAGIC){
		ppma++;
	}
	ppma->flags = flags;
	ppma->size = size;
	ppma->start = start;
	ppma->magic = PMA_MAGIC;
	//KPrintf("PmaAddArea(%d,%d,%d)\n",dwStart,dwSize,dwFlags);
}

UINT PmmCountPma(){
	UINT nCount = 0;
	for(UINT i=0;PmaTable[i].magic == PMA_MAGIC; i++){
		nCount++;
	}
	return nCount;
}

UINT PmmCountAllMemory(){
	UINT nSize = 0;
	for(UINT i=0;PmaTable[i].magic == PMA_MAGIC; i++){
		nSize += PmaTable[i].size;
	}
	return nSize;
}

UINT PmmGetTopmostMemory(){
	UINT i = 0;
	while(PmaTable[i].magic == PMA_MAGIC){i++;}
	while(PmaTable[i].size == 0){KPrintf("Lho heh\n");i--;}
	return (PmaTable[i].start + PmaTable[i].size);
}

UINT PmmCountAvlMemory(){
	UINT nSize = 0;

	for(UINT i=0;PmaTable[i].magic == PMA_MAGIC; i++){
		if (PmaTable[i].flags == PMA_AVAILABLE)
			nSize += PmaTable[i].size;
	}
	return nSize;
}


