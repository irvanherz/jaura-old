#ifndef _KINIT_H
#define _KINIT_H


#include "Jaura.h"
#include "Configs.h"
#include "Types.h"
#include "Errors.h"
#include "KLib.h"

typedef struct _GDTR{
	WORD   wLimit;
	DWORD  dwBase;
}__attribute__((packed)) GDTR, *PGDTR;

typedef QWORD GDTE, *PGDTE;

typedef struct _IDTR{
	WORD   wLimit;
	DWORD  dwBase;
}__attribute__((packed)) IDTR, *PIDTR;

typedef struct _IDTE{
	WORD wBaseLo;
	WORD wSelector;
	CHAR wReserved;
	CHAR chFlags;
	WORD wBaseHi;
}__attribute__((packed)) IDTE, *PIDTE;


UINT KiValloc(UINT);
void KInitMemoryFrame(UINT);
void KInitMultiboot2(PVOID);
void KInitMm();
JRAPI int KMain(PCHAR);

#endif
