#ifndef DEVICE_H
#define DEVICE_H

#include "Types.h"
#include "DList.h"
#include "KFilesystem.h"

#define MAX_DEVICE 0x500
#define MAX_MAJOR 0x400
#define MAX_MINOR 0x100

typedef ULONG DEVICE_ID;
typedef struct _DEVICE DEVICE;

struct _DEVICE{
	char			*name;
	void	*method;
	void			*data;
};

#define DEVICE_ID_OF (major,minor)((major << 16) & (minor & 0xFFFF))
#define MAJOR_OF(devid) (devid >> 16)
#define MINOR_OF(devid) (devid & 0xFFFF)

#endif