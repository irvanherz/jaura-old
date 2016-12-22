#include "Types.h"

#define ATTR_RO 1
#define ATTR_HIDDEN 2
#define ATTR_SYSTEM 4
#define ATTR_VOLID 8
#define ATTR_DIR 16
#define ATTR_ARCH 32

#define ATTR_LONG_NAME (ATTR_RO | ATTR_HIDDEN | ATTR_SYSTEM | ATTR_VOLID)
#define ATTR_LONG_NAME_MASK (ATTR_RO | ATTR_HIDDEN | ATTR_SYSTEM | ATTR_VOLID | ATTR_DIR | ATTR_ARCH)
#define LAST_LONG_ENTRY 0x40
#define DIR_DELETED 0xE5

#define ALIGN_VAL(val,alg) ((val % alg) ? (val + (alg - val % alg)) : val)

typedef struct _FAT_LDIRENT{
	UCHAR	ord;
	short	name1[5];
	UCHAR	attr;
	UCHAR	type;
	UCHAR	chksum;
	short	name2[6];
	USHORT	fstClusLo;
	short	name3[2];
} __attribute__((packed)) FAT_LDIRENT;

typedef struct _FAT_DIRENT {
	UCHAR	name[11];
	UCHAR	attr;
	UCHAR	ntres;
	UCHAR	ctime_ms;
	USHORT	ctime;
	USHORT	cdate;
	USHORT	adate;
	USHORT	fstClusHi;
	USHORT	mtime,mdate;
	USHORT	fstClusLo;
	UINT	fileSize;
} __attribute__((packed)) FAT_DIRENT;


typedef struct _FAT32_XBPB{
	UINT		fatSz32;
	USHORT		extFlags;
	USHORT		fsVer;
	UINT		rootClus;
	USHORT		fsInfo;
	USHORT		bkBootSec;
	UCHAR		reserved[12];
	UCHAR		driveNum;
	UCHAR		reserved1;
	UCHAR		bootSig;
	UINT		volId;
	UCHAR		volLab[11];
	UCHAR		filSysType[8];
} __attribute__((packed)) FAT32_XBPB;

typedef struct _FAT16_XBPB{
	UCHAR		driveNum;
	UCHAR		reserved1;
	UCHAR		bootSig;
	UINT		volId;
	UCHAR		volLab[11];
	UCHAR		filSysType[8];
} __attribute__((packed)) FAT16_XBPB;


typedef struct _FAT_BPB {
	UCHAR		jmpBoot[3];
	UCHAR		oemName[8];
	USHORT		bytsPerSec;
	UCHAR		secPerClus;
	USHORT		rsvdSecCnt;
	UCHAR		numFats;
	USHORT		rootEntCnt;
	USHORT		totSec16;
	UCHAR		media;
	USHORT		fatSz16;
	USHORT		secPerTrk;
	USHORT		numHeads;
	UINT		hiddenSec;
	UINT		totSec32;
	union {
		FAT32_XBPB	x32;
		FAT16_XBPB	x16;
		UCHAR		x12[54];
	};
} __attribute__((packed)) FAT_BPB;

typedef struct _FAT_MOUNT_DATA{
	FNODE		*dev;
	char		 fatType;
	FAT_BPB		 bpb;
	UINT		 fatSec;
	UINT		 rootSec;
	UINT		 dataSec;
	void		*clusc;
	UINT		 cluscMin;
	UINT		 cluscMax;
	void		*dirCache;
}FAT_MOUNT_DATA;
