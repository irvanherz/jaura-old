#include "Jaura.h"
#include "Configs.h"
#include "Types.h"
#include "Errors.h"
#include "Macros.h"
#include "KLib.h"
#include "KInit.h"
#include "KVmm.h"
#include "Multiboot2.h"
#include "Elf.h"


extern int	KRN_END_VMA;
extern int	KRN_END_LMA;
extern int	KRN_BASE_VMA;
extern int	KRN_BASE_LMA;
extern UINT	AllMemorySize;
extern UINT	AvlMemorySize;
UINT		fstart;
UINT		fstartv;
extern char BootCmdline[256];

extern void KiGdtLoad();
extern void KiIdtLoad();

INLINEFUNC void KInitMemoryPaging(UINT kstart, UINT kend){
	kstart			= PAGE_ALIGN(kstart);
	kend 			= PAGE_ALIGN(kend);
	UINT	ksize	= kend - kstart;
	UINT	pdt 	= kend;
	ULONG 	*p;
	
	MemFill ((PVOID) pdt,0,0x1000);
	p = (ULONG*) pdt;
	p[1023] = pdt | 3;
	
	/* Setup Kernel HIGH MEMORY map */
	ULONG	npte_hi	= ksize / PAGE_SIZE;
	ULONG	npgd_hi = ALIGN_NUM(npte_hi,1024) / 1024;
	ULONG	pgd_hi	= pdt + PAGE_SIZE;
	
	p=(ULONG*)pgd_hi;
	for (UINT i=0; i<npte_hi; i++){						//fill kernel page
		p[i] = (kstart + i * PAGE_SIZE) | 3;
	}
	p=(ULONG*)pdt;
	for (UINT i=0; i<npgd_hi; i++){						//fill kernel pde
		p[i+512] = (pgd_hi + i * PAGE_SIZE) | 3;
	}
	
	/* Setup Kernel Low MEMORY map */
	ULONG	npte_lo = kend / PAGE_SIZE;
	ULONG	npgd_lo = ALIGN_NUM(npte_lo,1024) / 1024;
	ULONG	pgd_lo	= pgd_hi + npgd_hi * PAGE_SIZE;
	
	p=(ULONG*)pgd_lo;
	for (UINT i=0; i<npte_lo; i++){						//Fill low page
		p[i] = (i * 0x1000) | 3;
	}
	p=(ULONG*)pdt;
	for (UINT i=0; i<npgd_lo; i++){						//fill low pde
		p[i] = (pgd_lo + i * 0x1000) | 3;
	}

	__asm__("mov eax, %0"::"g"(pdt));
	__asm__("mov cr3,eax");
	__asm__("mov eax,cr0");
	__asm__("or eax,0x80000000");
	__asm__("mov cr0,eax");
	__asm__("lea eax,[PagingEnabled]");
	__asm__("jmp eax");
	__asm__("PagingEnabled:");

	//p=0xFC000000;
	/*p= 0xFFFFF000;
	for (int i=0; i<npgd_lo; i++){						//fill low pde
		p[i] = 0;
	}*/
	fstart = pgd_lo + npgd_lo*PAGE_SIZE;
	fstartv = 0x80000000 + ksize;
}


JRAPI int KInit(PVOID pMbi){
	KInitMemoryPaging ((UINT) &KRN_BASE_LMA,(UINT) &KRN_END_LMA);
	KPrintInit();
	KiGdtLoad();
	KiIdtLoad();
	KInitMultiboot2(pMbi);
	KPrintf("Jaura System Started\n");
	KPrintf("Developed by irvan_herz\n");
	KPrintf("Installed memory %x bytes. Available memory %x bytes\n",AllMemorySize,AvlMemorySize);
	KPrintf("KRN_BASE_LMA:%x,KRN_END_LMA:%x,KRN_BASE_VMA:%x\n",&KRN_BASE_LMA, &KRN_END_LMA, &KRN_BASE_VMA);
	//KInitMemoryFrame(PmmGetTopmostMemory());
	AvlFrameInit();
	KInitMm();
	EndKiValloc();
	KMallocInit();
	//PicInit();
	//PitInit();
	KMain(BootCmdline);
	return 0;
}

