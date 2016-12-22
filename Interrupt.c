#include "Types.h"

typedef int (STD_INTERRUPT_HANDLER)(void *);
int InterruptInit(){
	return 0;
}

int InterruptRegister(UINT vector, STD_INTERRUPT_HANDLER *proc){
	
}

int InterruptUnregister(UINT vector){
	
}
