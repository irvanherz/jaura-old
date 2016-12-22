#include "Jaura.h"
#include "Configs.h"
#include "Types.h"
#include "Errors.h"
#include "Macros.h"
#include "KLib.h"
#include "KVmm.h"
#include "KHeap.h"
#include "Io.h"
#include "KFilesystem.h"
#include "Device.h"

#define IS_BSY(status) (status & 0x80)
#define IS_RDY(status) (status & 0x40)
#define IS_DF(status)  (status & 0x20)
#define IS_SRV(status) (status & 0x10)
#define IS_DRQ(status) (status & 0x08)
#define IS_ERR(status) (status & 0x01)

int AtaBread(FNODE *fnode,ULONGLONG sector,ULONG count,void** buffer){
	char status;
	
	outb(0x01F6,0xE0);
	outb(0x01F2,count);
	outb(0x01F3,sector & 0xFF);
	outb(0x01F4,(sector >> 8) & 0xFF);
	outb(0x01F5,(sector >> 16) & 0xFF);
	outb(0x01F7,0x20);
	
	wait:
	status = inb(0x01F7);
	if(IS_ERR(status)) return -1;
	if(IS_BSY(status)) goto wait;
	
	*buffer = KMalloc(count * 512);
	insw(0x01F0,*buffer,count * 512 / 2);
}

FNODE_METHOD ataMethod = {
	.bread = &AtaBread
};

DEVICE ataDevice = {
	.name = "ata",
	.method = &ataMethod,
	.data = 0
};

void AtaInit(){
	DeviceAdd(0,&ataDevice);
	FsMknod(0,"/dev/ata",0);
}


