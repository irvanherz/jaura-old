#ifndef _TYPES_H
#define _TYPES_H

typedef unsigned long long	ULONGLONG;
typedef unsigned long	ULONG;
typedef unsigned short	USHORT;
typedef unsigned char	UCHAR;
typedef unsigned int	UINT;
typedef int				BOOL;
typedef char			CHAR;
typedef unsigned char 	BYTE;
typedef unsigned short 	WORD;
typedef unsigned long	DWORD;
typedef unsigned long long	QWORD;
typedef void 			*PVOID;
typedef CHAR 			*PCHAR;
typedef BYTE 			*PBYTE;
typedef WORD 			*PWORD;
typedef DWORD 			*PDWORD;
typedef PVOID			HANDLE;
#define JRAPI			__attribute__((stdcall))
#define JRCAPI			__attribute__((cdecl))
#define TRUE			(unsigned)-1
#define FALSE			(unsigned)0
#define INLINEFUNC		inline __attribute__((always_inline))

#endif
