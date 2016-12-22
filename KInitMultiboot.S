.intel_syntax noprefix
.extern KInit
.global MultibootEntry
	jmp MultibootEntry
	.align 8
	multiboot_header_start:
		.long 0xE85250D6
		.long 0
		.long multiboot_header_end - multiboot_header_start
		.long -(0xE85250D6+0+(multiboot_header_end - multiboot_header_start))
		.align 8
		address_tag:
			.short	2
			.short	0
			.long	24
			.long	multiboot_header_start - 0x80000000 + 0x1000000
			.long	KRN_TEXT_BASE_LMA
			.long	KRN_BSS_END_LMA
			.long	KRN_END_LMA
		.align 8
		entry_tag:
			.short	3
			.short	0
			.long	12
			.long	MultibootEntry - 0x80000000 + 0x1000000
			.align 8
/*Hilangkan komentar untuk mengaktifkan mode graphic 640x480 32bpp
	framebuffer_tag:
			.short	5
			.short	0
			.long	20
			.long	640
			.long	480
			.long	32
		.align 8
*/
		end_tag:
			.short	0
			.short	0
			.long	8
		.align 8
	multiboot_header_end:
	
	MultibootEntry:
		mov esp, 0xFFFFFF /*temp stack*/
		push ebx
		call KInit
		ret
		