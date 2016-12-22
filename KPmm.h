#ifndef KPMM_H
#define KPMM_H


#include "Jaura.h"
#include "Configs.h"
#include "Types.h"
#include "Errors.h"
#include "KLib.h"

#define PMA_AVAILABLE 1 
#define PMA_RESERVED 2 
#define PMA_ACPI_RECLAIMABLE 3 
#define PMA_NVS 4
#define PMA_MAGIC 0x504D4130
#define MAX_PMA 64

typedef struct _PMA{
	DWORD	magic;
	DWORD	start;
	DWORD	size;
	DWORD	flags;
}PMA, *PPMA;

void PmmAddPma(UINT,UINT,UINT);
UINT PmmCountPma();
UINT PmmCountAllMemory();
UINT PmmCountAvlMemory();


#endif
