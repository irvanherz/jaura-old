#include "Types.h"
#include "Macros.h"
#include "Io.h"
#include <stdarg.h>

#define WIDTH		80
#define HEIGHT		25
#define MAXWIDTH	79
#define MAXHEIGHT	24

#define XY2POS(x,y)	(y*WIDTH+x)

UINT curPos;
UINT curAttr;

void KPrintInit(){
	curPos = 0;
	curAttr = 0x07;
}

INLINEFUNC void memcpy(void *dest,void *src,UINT count){
	while (count){
		*(char*)dest = *(char*)src;
		(char*)dest++;
		(char*)src++;
		count--;
	}
}

INLINEFUNC void __putchar(char chr,char attrib,UINT pos){
	char *ptr = (char*) (((unsigned)0xB8000) + (pos * 2));
	__asm__("mov eax,%0"::"g"(ptr));
	__asm__("mov dr1,eax");
	__asm__("mov eax,%0"::"g"(pos));
	__asm__("mov dr2,eax");
	__asm__("mov eax,%0"::"g"(attrib));
	__asm__("mov dr3,eax");
	__asm__("mov eax,%0"::"g"(&curPos));
	__asm__("mov dr3,eax");
	*ptr++ = chr;
	*ptr = attrib;
}

INLINEFUNC void __move_cursor(UINT pos){
	outb(0x3d4,14);
	outb(0x3d5,pos >> 8);
	outb(0x3d4,15);
	outb(0x3d5,pos & 0xff);
}

INLINEFUNC void _scroll(){
	memcpy((void*)0xB8000, (void*) 0xB8000 + (WIDTH * 2), (MAXHEIGHT * WIDTH * 2));
	char *lastfill = (char*) (0xB8000 + MAXHEIGHT * WIDTH * 2);
	for (int i=0; i<WIDTH; i++){
		*lastfill = ' ';
		lastfill++;
		*lastfill = 0x0f;
		lastfill++;
	}
}

void _update_cursor(){
	__move_cursor(curPos);
}

void _putchar(char chr){
	if(chr=='\n'){
		if(curPos % WIDTH == 0) curPos++;
		curPos = ALIGN_NUM(curPos,WIDTH);
	}
	else {
		__putchar(chr,curAttr,curPos);
		curPos++;
	}
	if(curPos == (HEIGHT * WIDTH)) {
		_scroll();
		curPos -= WIDTH;
	}
}

//begin usable important function
void putchar(char c){
	_putchar(c);
	_update_cursor();
}

void puts(char *str){
	while (*str){
		_putchar(*str);
		str++;
	}
	_update_cursor();
}

void KPrint(char *str){
	while (*str){
		_putchar(*str);
		str++;
	}
	_update_cursor();
}

int gotoxy(UINT x,UINT y){
	if(x > MAXWIDTH || y > MAXHEIGHT)
		return 0;
	curPos = XY2POS(x,y);
	return 1;
}

void KPrintf(char *fmt, ...){
	va_list ap;
	va_start(ap, fmt);
	
	char *str;
	char temp[100];
	
	for (str=fmt; *str; str++){
		if (*str != '%'){
			_putchar(*str);
		}
		else {
			str++;
			switch (*str){
				case 's':
					KPrint(va_arg(ap, char *));
					break;
				case 'd':
					IntToAsc(va_arg(ap,int), temp, 10);
					KPrint(temp);
					break;
				case 'x':
					UintToAsc(va_arg(ap,int), temp, 16);
					KPrint(temp);
					break;					
			}
		}
	}
	_update_cursor();
	
	va_end(ap);
}
