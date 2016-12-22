#include "Types.h"

#define EI_NIDENT 16
#define ET_NONE 0
#define ET_REL 1
#define ET_EXEC 2
#define ET_DYN 3
#define ET_CORE 4
#define ET_LOPROC 0xff00
#define ET_HIPROC 0xffff

#define EM_NONE 0
#define EM_M32 1
#define EM_SPARC 2
#define EM_386 3
#define EM_68K 4
#define EM_88K 5
#define EM_860 7
#define EM_MIPS8

typedef struct _ELF32_EHDR {
	UCHAR e_ident [EI_NIDENT];
	WORD e_type;
	WORD e_machine;
	DWORD e_version;
	DWORD e_entry;
	DWORD e_phoff;
	DWORD e_shoff;
	DWORD e_flags;
	WORD e_ehsize;
	WORD e_phentsize;
	WORD e_phnum;
	WORD e_shentsize;
	WORD e_shnum;
	WORD e_shstrndx;
} ELF32_EHDR, *PELF32_EHDR;


#define SHT_NULL 0
#define SHT_PROGBITS 1
#define SHT_SYMTAB 2
#define SHT_STRTAB 3
#define SHT_RELA 4
#define SHT_HASH 5
#define SHT_DYNAMIC 6
#define SHT_NOTE 7
#define SHT_NOBITS 8
#define SHT_REL 9
#define SHT_SHLIB 10
#define SHT_DYNSYM 11
#define SHT_LOPROC 0x70000000
#define SHT_HIPROC 0x7fffffff
#define SHT_LOUSER 0x80000000
#define SHT_HIUSER 0xffffffff

#define SHF_WRITE 0x1
#define SHF_ALLOC 0x2
#define SHF_EXECINSTR 0x4
#define SHF_MASKPROC 0xf0000000

typedef struct _ELF32_SHDR{
	DWORD	sh_name;
	DWORD	sh_type;
	DWORD	sh_flags;
	DWORD	sh_addr;
	DWORD	sh_offset;
	DWORD	sh_size;
	DWORD	sh_link;
	DWORD	sh_info;
	DWORD	sh_addralign;
	DWORD	sh_entsize;
} ELF32_SHDR, *PELF32_SHDR;

#define PT_NULL 0
#define PT_LOAD 1
#define PT_DYNAMIC 2
#define PT_INTERP 3
#define PT_NOTE 4
#define PT_SHLIB 5
#define PT_PHDR 6
#define PT_LOPROC 0x70000000
#define PT_HIPROC 0x7FFFFFFF

#define PF_R 4
#define PF_W 2
#define PF_X 1

typedef struct _ELF32_PHDR {
	DWORD p_type;
	DWORD p_offset;
	DWORD p_vaddr;
	DWORD p_paddr;
	DWORD p_filesz;
	DWORD p_memsz;
	DWORD p_flags;
	DWORD p_align;
} ELF32_PHDR, *PELF32_PHDR;
