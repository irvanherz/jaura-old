#ifndef MACROS_H
#define MACROS_H


#define ALIGN_NUM(val, align) (val % align ? val + (align - val % align) : val)
#define Hang() __asm__("jmp $")

#endif