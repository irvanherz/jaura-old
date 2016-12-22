#ifndef IO_H
#define IO_H


#include "Types.h"

INLINEFUNC void outb(USHORT port,UCHAR data){
	asm("mov dx,%0"::"g"(port));
	asm("mov al,%0"::"g"(data));
	asm("out dx,al");
}

INLINEFUNC UCHAR inb(USHORT port){
	char ret;
	asm("mov dx,%0"::"g"(port));
	asm("in %0,dx":"=r"(ret));
	return ret;
}

INLINEFUNC USHORT inw(USHORT port){
	USHORT ret;
	asm("mov dx,%0"::"g"(port));
	asm("in %0,dx":"=r"(ret));
	return ret;
}

INLINEFUNC void outw(USHORT port,USHORT data){
	asm("mov dx,%0"::"g"(port));
	asm("mov ax,%0"::"g"(data));
	asm("out dx,ax");
}

INLINEFUNC void insb(USHORT port,void *addr,UINT count){
	asm("mov dx,%0"::"g"(port));
	asm("mov edi,%0"::"g"(addr));
	asm("mov ecx,%0"::"g"(count));
	asm("cld");
	asm("rep insb");
}

INLINEFUNC void insw(USHORT port,void *addr,UINT count){
	asm("mov dx,%0"::"g"(port));
	asm("mov edi,%0"::"g"(addr));
	asm("mov ecx,%0"::"g"(count));
	asm("cld");
	asm("rep insw");
}

INLINEFUNC void insl(USHORT port,void *addr,UINT count){
	asm("mov dx,%0"::"g"(port));
	asm("mov edi,%0"::"g"(addr));
	asm("mov ecx,%0"::"g"(count));
	asm("cld");
	asm("rep insd");
}

#define hlt() (asm("hlt"))
#define cli() (asm("cli"))
#define sti() (asm("sti"))


#endif