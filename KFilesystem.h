#ifndef KFILESYSTEM_H
#define KFILESYSTEM_H

#include "Types.h"
#include "DList.h"
#include "Device.h"

typedef struct _FNODE FNODE;
typedef struct _FILE FILE;
typedef struct _FILESYSTEM FILESYSTEM;
typedef struct _MOUNT MOUNT;
typedef enum _FNODE_TYPE {FNODE_REGULAR,FNODE_DIRECTORY,FNODE_BLOCKDEV,FNODE_CHARDEV} FNODE_TYPE;

typedef struct _FNODE_METHOD {
	int					(*create)(FNODE *,char *);		//fnode src,name
	int					(*mkdir)(FNODE *,char *);		//fnode src,name
	int					(*mknod)(FNODE *,char *,ULONG);
	int					(*read)(FNODE *,void *,UINT,UINT);		//fnode,buffer,offt,cnt
	int					(*write)(FNODE *,void *,int,int);
	int					(*ioctl)(FNODE *,int,int);				//fnode,cmd,arg
	int					(*lookup)(FNODE *,char *,FNODE**);
	int					(*bread)(FNODE *,ULONGLONG,ULONG,void**);
}FNODE_METHOD;

struct _FNODE {
	DLIST_NODE			 myNode;
	char				*name;
	MOUNT				*ownerMount;
	struct _FNODE		*parentNode;
	struct _FNODE		*cover;
	DLIST				 childNodes;
	UINT				 refCount;
	FNODE_TYPE			 type;
	FNODE_METHOD		*method;
	void*				 data;
};

typedef struct _FILESYSTEM_METHOD{
	int					(*mount)(MOUNT *mount);
	int					(*unmount)(MOUNT *mount);
}FILESYSTEM_METHOD;

struct _FILESYSTEM {
	char				*name;
	FILESYSTEM_METHOD	*method;
	DLIST_NODE		 	 lnode;
};

struct _MOUNT {
	FILESYSTEM			*fs;
	FILESYSTEM_METHOD	*fsMethod;
	DEVICE				 mountDev;
	DLIST_NODE			 lnode;
	FNODE				*rootFnode;
	FNODE				*coveredFnode;
	FNODE				*deviceFnode;
	char				*data;
};


typedef struct _FILE_METHOD {
	int (*open)(char *,UINT,FILE **);
	int (*close)(FILE *);
	int (*read)(FILE *,void *,UINT,UINT);
	int (*write)(FILE *,void *,UINT,UINT);
}FILE_METHOD;

struct _FILE {
	UINT		 position;
	UINT		 mode;
	FILE_METHOD	*method;
	FNODE		*fnode;
};

#endif
