#include "Jaura.h"
#include "KInit.h"
#include "Multiboot2.h"

GDTR Gdtr;
GDTE Gdt[] = {
	0x0000000000000000,
	0x00CF9A000000FFFF,
	0x00CF92000000FFFF
};

IDTR Idtr;
IDTE Idt[256];

void KiGdtLoad(){
	Gdtr.dwBase = (DWORD)&Gdt;
	Gdtr.wLimit = sizeof(Gdt);
	__asm__("lgdt Gdtr");
	__asm__("ljmp 8,GdtLoaded");
	__asm__("GdtLoaded:");
	__asm__("mov ax,16");
	__asm__("mov ds,ax");
	__asm__("mov es,ax");
	__asm__("mov fs,ax");
	__asm__("mov gs,ax");
	__asm__("mov ss,ax");
}

void KiIdtLoad(){
	Idtr.dwBase = (DWORD)&Idt;
	Idtr.wLimit = sizeof(Idt);
	__asm__("lidt Idtr");
}

typedef void (*STD_INTERRUPT_CALLBACK)();
HANDLE KiRegisterInterrupt(UINT nVector, STD_INTERRUPT_CALLBACK cbFunc, DWORD dwFlags){
	Idt[nVector].chFlags = (CHAR) dwFlags & 0xFF;
	Idt[nVector].wBaseHi = ((UINT)cbFunc) >> 16;
	Idt[nVector].wBaseLo = ((UINT)cbFunc) & 0xFFFF;
	Idt[nVector].wReserved = 0;
	Idt[nVector].wSelector = 0x8;
	return (HANDLE) &Idt[nVector];
}

BOOL KiUnregisterInterrupt(HANDLE hInterrupt){
	if (((UINT)hInterrupt < (UINT)&Idt) &&
	    ((UINT)hInterrupt < (UINT)&Idt + Idtr.wLimit))
		return FALSE;
	PIDTE pIdte = (IDTE*) hInterrupt;
	pIdte->chFlags = 0;
	pIdte->wBaseHi = 0;
	pIdte->wBaseLo = 0;
	pIdte->wSelector = 0;
	return TRUE;
}