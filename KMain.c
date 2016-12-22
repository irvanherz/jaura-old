#include "Jaura.h"
#include "Configs.h"
#include "Types.h"
#include "Errors.h"
#include "Macros.h"
#include "KLib.h"
#include "KVmm.h"
#include "KHeap.h"
#include "KFilesystem.h"
#include "Device.h"

char buffer[0x5000];
JRAPI int KMain(PCHAR cmd){
	KPrint("Initializing FS subsystem\n");
	FsInit();									//init FS subsystem
	KPrint("Installing TMPFS, mount as root directory\n");
	TmpfsInit();								//init Temporary filesystem
	FsMountRoot(FsFindFilesystem("tmpfs"),0,0);	//mount root with TmpFS
	
	FNODE *ataNode,*jauraNode;
	KPrint("Creating /dev and /jaura directory\n");
	FsMkdir(0,"/dev");
	FsMkdir(0,"/jaura");
	
	KPrint("Initializing ATA harddisk controller as /dev/ata\n");
	AtaInit();
	FsLookup(0,"/dev/ata",&ataNode);
	FsLookup(0,"/jaura",&jauraNode);
	KPrint("Initializing FAT16 driver\n");
	Fat16Init();
	KPrint("Mounting /dev/ata to /jaura\n");
	FsMount(FsFindFilesystem("fat16"),ataNode,jauraNode,0);
	
	KPrint("Lookup /jaura/System/System.cfg\n");
	FNODE *fsys, *fjaura,*ftxt;
	FsLookup(0,"/jaura/System/System.cfg",&ftxt);
	
	KPrint("Reading /jaura/System/System.cfg 0:100\n");
	UINT res = FnodeRead(ftxt,buffer,0,100);
	KPrintf("FnodeRead() return %d, contents:\n%s",res,buffer);
	Hang();
	return 0;
}


