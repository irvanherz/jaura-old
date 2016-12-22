#include "Interrupt.h"
#include "Io.h"

void PitIrqHandler(REGISTERS);
void PitIrq();

DEFINE_IRQ_ENTRY("PitIrq",PitIrqHandler);

void PitIrqHandler(REGISTERS regs){
	KPrintf("0");
	outb(0x20,0x20);
}

int PitInit(){
	outb(0x43,0x34);
	//counter = 0xFF55
	outb(0x40,0x55);
	outb(0x40,0xFF);
	KiRegisterInterrupt(0x20,PitIrq,0x8e);
	outb(0x21,0xFE);
	__asm__("sti");
}