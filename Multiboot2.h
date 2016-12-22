#ifndef _MULTIBOOT2_H
#define _MULTIBOOT2_H
typedef unsigned char		u8;
typedef unsigned short		u16;
typedef unsigned long		u32;
typedef unsigned long long	u64;
typedef unsigned int		u_phys;
typedef unsigned int		u_virt;

#define MULTIBOOT2_SEARCH 32768 
#define MULTIBOOT2_HEADER_ALIGN 8
#define MULTIBOOT2_HEADER_MAGIC 0xe85250d6
#define MULTIBOOT2_BOOTLOADER_MAGIC 0x36d76289
#define MULTIBOOT2_MOD_ALIGN 0x00001000
#define MULTIBOOT2_INFO_ALIGN 0x00000008
#define MULTIBOOT2_TAG_ALIGN 8 
#define MULTIBOOT2_TAG_TYPE_END 0 
#define MULTIBOOT2_TAG_TYPE_CMDLINE 1 
#define MULTIBOOT2_TAG_TYPE_BOOT_LOADER_NAME 2 
#define MULTIBOOT2_TAG_TYPE_MODULE 3 
#define MULTIBOOT2_TAG_TYPE_BASIC_MEMINFO 4
#define MULTIBOOT2_TAG_TYPE_BOOTDEV 5
#define MULTIBOOT2_TAG_TYPE_MMAP 6 
#define MULTIBOOT2_TAG_TYPE_VBE 7 
#define MULTIBOOT2_TAG_TYPE_FRAMEBUFFER 8 
#define MULTIBOOT2_TAG_TYPE_ELF_SECTIONS 9 
#define MULTIBOOT2_TAG_TYPE_APM 10
#define MULTIBOOT2_HEADER_TAG_TYPE_END 0 
#define MULTIBOOT2_HEADER_TAG_TYPE_INFORMATION_REQUEST 1 
#define MULTIBOOT2_HEADER_TAG_TYPE_ADDRESS 2 
#define MULTIBOOT2_HEADER_TAG_TYPE_ENTRY_ADDRESS 3 
#define MULTIBOOT2_HEADER_TAG_TYPE_CONSOLE_FLAGS 4 
#define MULTIBOOT2_HEADER_TAG_TYPE_FRAMEBUFFER 5 
#define MULTIBOOT2_HEADER_TAG_TYPE_MODULE_ALIGN 6
#define MULTIBOOT2_ARCHITECTURE_I386 0 
#define MULTIBOOT2_ARCHITECTURE_MIPS32 4 
#define MULTIBOOT2_HEADER_TAG_OPTIONAL 1
#define MULTIBOOT2_CONSOLE_FLAGS_CONSOLE_REQUIRED 1 
#define MULTIBOOT2_CONSOLE_FLAGS_EGA_TEXT_SUPPORTED 2


typedef struct _MULTIBOOT2_HEADER {
	u32 magic;
	u32 architecture;
	u32 header_length;
	u32 checksum;
} MULTIBOOT2_HEADER;

typedef struct _MULTIBOOT2_HEADER_TAG {
	u16 type;
	u16 flags;
	u32 size;
}MULTIBOOT2_HEADER_TAG;

typedef struct _MULTIBOOT2_HEADER_TAG_INFORMATION_REQUEST {
	u16 type;
	u16 flags;
	u32 size;
	u32 requests[0];
}MULTIBOOT2_HEADER_TAG_INFORMATION_REQUEST;
typedef struct _MULTIBOOT2_HEADER_TAG_ADDRESS {
	u16 type;
	u16 flags;
	u32 size;
	u32 header_addr;
	u32 load_addr;
	u32 load_end_addr;
	u32 bss_end_addr;
} MULTIBOOT2_HEADER_TAG_ADDRESS;

typedef struct _MULTIBOOT2_HEADER_TAG_ENTRY_ADDRESS {
	u16 type; 
	u16 flags; 
	u32 size; 
	u32 entry_addr; 
} MULTIBOOT2_HEADER_TAG_ENTRY_ADDRESS;

typedef struct _MULTIBOOT2_HEADER_TAG_CONSOLE_FLAGS { 
	u16 type; 
	u16 flags;
	u32 size; 
	u32 console_flags; 
} MULTIBOOT2_HEADER_TAG_CONSOLE_FLAGS;

typedef struct _MULTIBOOT2_HEADER_TAG_FRAMEBUFFER { 
	u16 type; 
	u16 flags; 
	u32 size; 
	u32 width; 
	u32 height; 
	u32 depth; 
} MULTIBOOT2_HEADER_TAG_FRAMEBUFFER;

typedef struct _MULTIBOOT2_HEADER_TAG_MODULE_ALIGN { 
	u16 type; 
	u16 flags; 
	u32 size; 
	u32 width; 
	u32 height; 
	u32 depth; 
} MULTIBOOT2_HEADER_TAG_MODULE_ALIGN;

typedef struct _MULTIBOOT2_COLOR { 
	u8 red;
	u8 green; 
	u8 blue; 
} MULTIBOOT2_COLOR;

typedef struct _MULTIBOOT2_MMAP_ENTRY { 
	u64 addr; 
	u64 len; 
	#define MULTIBOOT2_MEMORY_AVAILABLE 1 
	#define MULTIBOOT2_MEMORY_RESERVED 2 
	#define MULTIBOOT2_MEMORY_ACPI_RECLAIMABLE 3 
	#define MULTIBOOT2_MEMORY_NVS 4 
	u32 type; 
	u32 zero; 
} __attribute__((packed)) MULTIBOOT2_MMAP_ENTRY;

typedef struct _MULTIBOOT2_TAG { 
	u32 type; 
	u32 size; 
} MULTIBOOT2_TAG;

typedef struct _MULTIBOOT2_TAG_STRING { 
	u32 type; 
	u32 size; 
	char string[0]; 
} MULTIBOOT2_TAG_STRING;

typedef struct _MULTIBOOT2_TAG_MODULE { 
	u32 type;
	u32 size; 
	u32 mod_start; 
	u32 mod_end; 
	char cmdline[0]; 
} MULTIBOOT2_TAG_MODULE;

typedef struct _MULTIBOOT2_TAG_BASIC_MEMINFO { 
	u32 type; 
	u32 size; 
	u32 mem_lower; 
	u32 mem_upper; 
} MULTIBOOT2_TAG_BASIC_MEMINFO;

typedef struct _MULTIBOOT2_TAG_BOOTDEV { 
	u32 type; 
	u32 size; 
	u32 biosdev; 
	u32 slice; 
	u32 part; 
} MULTIBOOT2_TAG_BOOTDEV;

typedef struct _MULTIBOOT2_TAG_MMAP { 
	u32 type; 
	u32 size; 
	u32 entry_size; 
	u32 entry_version; 
	MULTIBOOT2_MMAP_ENTRY entries[0]; 
} MULTIBOOT2_TAG_MMAP;

typedef struct _MULTIBOOT2_VBE_INFO_BLOCK { 
	u8 external_specification[512]; 
} MULTIBOOT2_VBE_INFO_BLOCK;

typedef struct _MULTIBOOT2_VBE_MODE_INFO_BLOCK { 
	u8 external_specification[256]; 
} MULTIBOOT2_VBE_MODE_INFO_BLOCK;

typedef struct _MULTIBOOT2_TAG_VBE { 
	u32 type; 
	u32 size;
	u16 vbe_mode;
	u16 vbe_interface_seg; 
	u16 vbe_interface_off; 
	u16 vbe_interface_len;
	MULTIBOOT2_VBE_INFO_BLOCK vbe_control_info; 
	MULTIBOOT2_VBE_MODE_INFO_BLOCK vbe_mode_info; 
} MULTIBOOT2_TAG_VBE;

typedef struct _MULTIBOOT2_TAG_FRAMEBUFFER_COMMON { 
	u32 type; 
	u32 size;
	u64 framebuffer_addr; 
	u32 framebuffer_pitch; 
	u32 framebuffer_width; 
	u32 framebuffer_height; 
	u8 framebuffer_bpp; 
	#define MULTIBOOT2_FRAMEBUFFER_TYPE_INDEXED 0 
	#define MULTIBOOT2_FRAMEBUFFER_TYPE_RGB 1 
	#define MULTIBOOT2_FRAMEBUFFER_TYPE_EGA_TEXT 2 
	u8 framebuffer_type; 
	u16 reserved; 
} MULTIBOOT2_TAG_FRAMEBUFFER_COMMON;

typedef struct _MULTIBOOT2_TAG_FRAMEBUFFER { 
	MULTIBOOT2_TAG_FRAMEBUFFER_COMMON common;
	union {
		struct {
			u16 framebuffer_palette_num_colors; 
			MULTIBOOT2_COLOR framebuffer_palette[0]; 
		};
		struct { 
			u8 framebuffer_red_field_position; 
			u8 framebuffer_red_mask_size; 
			u8 framebuffer_green_field_position; 
			u8 framebuffer_green_mask_size; 
			u8 framebuffer_blue_field_position; 
			u8 framebuffer_blue_mask_size; 
		}; 
	};
} MULTIBOOT2_TAG_FRAMEBUFFER;

typedef struct _MULTIBOOT2_TAG_ELF_SECTIONS { 
	u32 type; 
	u32 size; 
	u32 num; 
	u32 entsize; 
	u32 shndx; 
	char sections[0]; 
} MULTIBOOT2_TAG_ELF_SECTIONS;
typedef struct _MULTIBOOT2_TAG_APM { 
	u32 type; 
	u32 size; 
	u16 version; 
	u16 cseg; 
	u32 offset; 
	u16 cseg_16; 
	u16 dseg; 
	u16 flags; 
	u16 cseg_len; 
	u16 cseg_16_len; 
	u16 dseg_len; 
} MULTIBOOT2_TAG_APM;


#endif