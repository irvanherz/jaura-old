#include "Jaura.h"
#include "KInit.h"
#include "KPmm.h"
#include "KVmm.h"
#include "KHeap.h"

extern UINT		fstart;		//available physical memory
extern UINT		fstartv;	//available virtual memory

UINT KiValloc(UINT size){
	size = PAGE_ALIGN(size);

	UINT ipde;
	UINT va = fstartv;
	UINT itarget = va / PAGE_SIZE;
	UINT iend = itarget + size / PAGE_SIZE;
	while(itarget < iend){
		ipde = itarget / 1024;
		if (!PDE(ipde)){
			PDE(ipde) = fstart | 3;
			fstart += PAGE_SIZE;
		}
		PTE(itarget) = fstart | 3;
		fstart += PAGE_SIZE;
		fstartv += PAGE_SIZE;
		itarget++;
	}
	return va;
}

