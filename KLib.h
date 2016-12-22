#ifndef KLIB_H
#define KLIB_H

#include "Jaura.h"
#include "Types.h"
#include "Errors.h"

int StrCompare(PCHAR,PCHAR);
PCHAR StrCopy(PCHAR,PCHAR);
void StrJoin(PCHAR,PCHAR);
PCHAR StrReverse(PCHAR);
PCHAR StrUpper(PCHAR);
PCHAR StrLower(PCHAR);
UINT StrLength(PCHAR);
int MemCompare(void*, void*, UINT);
void MemCopy(void*, void *,UINT);
void MemFill(PVOID,char,UINT);
int AscToInt(PCHAR,int);
int AscToUint(PCHAR,int);
void UintToAsc(UINT,PCHAR,int);
void IntToAsc(int,PCHAR,int);
void PortOut8(USHORT,UCHAR);
UCHAR PortIn8(USHORT);
void PortOut16(USHORT,USHORT);
USHORT PortIn16(USHORT);
void memset(void *, char, UINT);


#endif