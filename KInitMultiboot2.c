#include "Jaura.h"
#include "KInit.h"
#include "KPmm.h"
#include "Multiboot2.h"

char		BootCmdline[256] = {'-',0};
extern PMA	PmaTable[MAX_PMA];
UINT		AllMemorySize;
UINT		AvlMemorySize;

/**
 * @brief Initialize memary map by filling PMA array on PmaTable[]
 * @param pMmap	: Pointer to MULTIBOOT2_TAG_MMAP
 */
void KInitMultibootMmap(MULTIBOOT2_TAG_MMAP * pMmap){
	MemFill(PmaTable,0,sizeof(PMA) * MAX_PMA);
	
	for (MULTIBOOT2_MMAP_ENTRY *pMmaps = pMmap->entries;
		(UINT) pMmaps < (UINT)pMmap + (UINT)pMmap->size;
		pMmaps = (MULTIBOOT2_MMAP_ENTRY *)((UINT)pMmaps + (UINT)pMmap->entry_size))
	{
			PmmAddPma((DWORD)pMmaps->addr,(DWORD)pMmaps->len,pMmaps->type);
	}
	AllMemorySize = PmmCountAllMemory();
	AvlMemorySize = PmmCountAvlMemory();
}

/**
 * @brief Set command line
 * @param cmd	: pointer to MULTIBOOT2_TAG_STRING
 */
void KInitMultibootCmdline(MULTIBOOT2_TAG_STRING * cmd){
	StrCopy(BootCmdline,cmd->string);
}

/**
 * @brief Kernel initialization with Multiboot 2 data
 * @param pMbi	: Pointer to Multiboot info
 */
void KInitMultiboot2(PVOID pMbi){
	MULTIBOOT2_TAG 	*pMbiTag;
	for (pMbiTag = (MULTIBOOT2_TAG *) (UINT)pMbi + 8;
		 pMbiTag->type != MULTIBOOT2_TAG_TYPE_END;
		 pMbiTag = (MULTIBOOT2_TAG *)((UINT)pMbiTag + ((pMbiTag->size + 7) & ~7)))
	{
		switch (pMbiTag->type){
			case MULTIBOOT2_TAG_TYPE_MMAP:
				KInitMultibootMmap((MULTIBOOT2_TAG_MMAP *) pMbiTag);
				break;
			case MULTIBOOT2_TAG_TYPE_CMDLINE:
				KInitMultibootCmdline((MULTIBOOT2_TAG_STRING *) pMbiTag);
				break;
		}
		
	}
}
