typedef struct _REGISTERS {
	unsigned long edi;
	unsigned long esi;
	unsigned long ebp;
	unsigned long esp;
	unsigned long ebx;
	unsigned long edx;
	unsigned long ecx;
	unsigned long eax;
	
	unsigned short gs;
	unsigned short fs;
	unsigned short es;
	unsigned short ds;
	
	unsigned long eip;
	unsigned short cs;
	unsigned long eflags;
} REGISTERS;

typedef void (INTERRUPT_HANDLER_PROC)(REGISTERS regs);

#define SAVE_REGISTERS() \
	__asm__("push ds"); \
	__asm__("push es"); \
	__asm__("push fs"); \
	__asm__("push gs"); \
	__asm__("pusha");
	
#define RESTORE_REGISTERS() \
	__asm__("popa"); \
	__asm__("pop gs"); \
	__asm__("pop fs"); \
	__asm__("pop es"); \
	__asm__("pop ds");

#define DEFINE_IRQ_ENTRY(name,handler) \
	__asm__(".global "#name); \
	__asm__(#name":"); \
	SAVE_REGISTERS() \
	__asm__("call "#handler); \
	RESTORE_REGISTERS(); \
	__asm__("iretd");
