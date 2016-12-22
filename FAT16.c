#include "KFilesystem.h"
#include "FAT.h"

int Fat16Mount(MOUNT *);
int FatLookup(FNODE *fnode,char *name,FNODE **resnode);
int FatRead(FNODE *fnode,void *buffer,UINT offset,UINT size);

FILESYSTEM_METHOD fat16FsMethod = {
	.mount = &Fat16Mount
};

FILESYSTEM fat16Fs = {
	.name = "fat16",
	.method = &fat16FsMethod,
};

FNODE_METHOD fat16DirMethod = {
	.lookup = &FatLookup,
	.read = &FatRead
};

int FatGetType(FAT_BPB *b){
	UINT rootDirSec,fatSz,totSec,totDataSec,totClus;
	
	rootDirSec = ((b->rootEntCnt * 32) + (b->bytsPerSec - 1)) / b->bytsPerSec;
	
	if(b->fatSz16 != 0)
		fatSz = b->fatSz16;
	else
		fatSz = b->x32.fatSz32;
	
	if(b->totSec16 != 0)
		totSec = b->totSec16;
	else
		totSec = b->totSec32;
	
	totDataSec = totSec - (b->rsvdSecCnt + (b->numFats * fatSz) + rootDirSec);
	totClus = totDataSec / b->secPerClus;
	
	if(totClus < 4085)
		return 12;
	else if(totClus < 65525)
		return 16;
	else
		return 32;
}

int Fat16InitMount(FAT_MOUNT_DATA *m){
	
	//get FAT type
	m->fatType = FatGetType(&m->bpb);
	//find fat's sector
	m->fatSec = m->bpb.rsvdSecCnt;
	//find data sec and root's sector
	if(m->fatType == 32){
		m->dataSec = m->fatSec;
		m->dataSec += m->bpb.x32.fatSz32 * m->bpb.numFats;
		m->rootSec = 0;
	}
	else {
		m->rootSec = m->fatSec;
		m->rootSec += m->bpb.fatSz16 * m->bpb.numFats;
		m->dataSec = m->rootSec;
		m->dataSec += m->bpb.rootEntCnt * sizeof(FAT_DIRENT) / m->bpb.bytsPerSec;
	}
	return 0;
}

int Fat16Mount(MOUNT *m){
	FAT_MOUNT_DATA *fmd;
	void *tmp;
	
	KPrint("FAT16 Mounting begin \n");
	fmd = KMalloc(sizeof(FAT_MOUNT_DATA));
	MemFill(fmd,0,sizeof(FAT_MOUNT_DATA));
	fmd->dev = m->deviceFnode;
	FnodeBread(fmd->dev,(ULONGLONG)0,1,&tmp);
	MemCopy(&fmd->bpb, tmp, sizeof(FAT_BPB));
	Fat16InitMount(fmd);
	KPrint("FAT16 Mounting end \n");
	KFree(tmp);
	
	m->data = fmd;
	
	FNODE *root;
	root = FnodeAlloc();
	root->data = 0;
	root->method = &fat16DirMethod;
	root->ownerMount = m;
	root->type = FNODE_DIRECTORY;
	root->parentNode = 0;
	FnodeEnter(root);
	m->rootFnode = root;
}

UINT FatNextClus16(FAT_MOUNT_DATA *m, UINT clus){
	if((clus < m->cluscMin) || (clus > m->cluscMax)){
		UINT clussec = (clus * 2 / m->bpb.bytsPerSec) + m->fatSec;
		m->cluscMin = clussec / 2;
		m->cluscMax = ((clussec + 3) / 2) - 1;
		if(m->clusc) KFree(m->clusc);
		FnodeBread(m->dev,(ULONGLONG)clussec,2,&m->clusc);
	}
	return ((short*)m->clusc)[clus - m->cluscMin];
}

void *FatReadClus16(FAT_MOUNT_DATA *m, UINT *clus){
	if((*clus >= 0xFFF7) && (*clus < 2)) return 0;
	void *ret;
	FnodeBread(m->dev,(ULONGLONG)(m->dataSec + ((*clus - 2) * m->bpb.secPerClus)),m->bpb.secPerClus,&ret);
	*clus = FatNextClus16(m,*clus);
	return ret;
}

short lnamec[256];
char snamec[11];

int FatLookupRoot16(FAT_MOUNT_DATA *m, char *name, FAT_DIRENT **resdir){
	void *tmp;
	UINT sec = m->rootSec;
	UINT maxsec = m->dataSec;
	UINT dirloops = m->bpb.bytsPerSec /sizeof(FAT_DIRENT);
	FAT_LDIRENT *ld,*buffd;
	FAT_DIRENT *d;
	
	r:
	FnodeBread(m->dev,(ULONGLONG)sec,1,&tmp);
	if(sec >= maxsec) goto nomore;
	buffd = ld = (FAT_LDIRENT*)tmp;
	d = (FAT_DIRENT*)ld;
	
	for (int i=dirloops; i != 0; i--, ld++, d = (FAT_DIRENT*)ld){
		if(d->name[0] == 0){
			goto nomore;
		}
		
		if(((ld->attr & ATTR_LONG_NAME_MASK) == ATTR_LONG_NAME) && (ld->ord != 0xE5)){
			UINT p = ((ld->ord & (~0x40)) - 1) * 13;
			if(p > 255) continue;
			MemCopy(&lnamec[p],ld->name1,10);
			MemCopy(&lnamec[p + 5],ld->name2,12);
			MemCopy(&lnamec[p + 11],ld->name3,4);
		}
		
		else if(((ld->attr & ATTR_LONG_NAME_MASK) != ATTR_LONG_NAME) && (ld->ord != 0xE5)){
			/*for(int i=0; lnamec[i] !=0; i++){
				putchar(lnamec[i]);
			}
			putchar('\n');*/
			//KPrint("hey\n");
			for(int i = 0; (UINT)name[i] == (UINT)lnamec[i]; i++){
				if(name[i] == 0 && lnamec[i] == 0) goto found;
			}
		}
	}
	KFree(buffd);
	sec++;
	goto r;
	
	nomore:
	return -1;
	
	found:
	//KPrintf("found\n");
	KFree(buffd);
	*resdir = KMalloc(sizeof(FAT_DIRENT));
	MemCopy(*resdir,d,sizeof(FAT_DIRENT));
	return 0;
}

int FatLookup16(FAT_MOUNT_DATA *m, FAT_DIRENT *dir, char *name, FAT_DIRENT **resdir){
	if(!dir) return FatLookupRoot16(m,name,resdir);
	
	UINT clus = (dir->fstClusHi << 16) | dir->fstClusLo; 
	UINT dirloops = m->bpb.secPerClus * m->bpb.bytsPerSec / sizeof(FAT_DIRENT);
	FAT_LDIRENT *ld,*buffd;
	FAT_DIRENT *d;
	
	r:
	if(clus >= 0xFFF7 && clus < 2) goto nomore;
	buffd = ld = (FAT_LDIRENT*)FatReadClus16(m,&clus);
	d = (FAT_DIRENT*)ld;
	
	for (int i=dirloops; i != 0; i--, ld++, d = (FAT_DIRENT*)ld){
		if(d->name[0] == 0){
			goto nomore;
		}
		
		if(((ld->attr & ATTR_LONG_NAME_MASK) == ATTR_LONG_NAME) && (ld->ord != 0xE5)){
			UINT p = ((ld->ord & (~0x40)) - 1) * 13;
			if(p > 255) continue;
			MemCopy(&lnamec[p],ld->name1,10);
			MemCopy(&lnamec[p + 5],ld->name2,12);
			MemCopy(&lnamec[p + 11],ld->name3,4);
		}
		
		else if(((ld->attr & ATTR_LONG_NAME_MASK) != ATTR_LONG_NAME) && (ld->ord != 0xE5)){
			/*for(int i=0; lnamec[i] !=0; i++){
				putchar(lnamec[i]);
			}
			putchar('\n');*/
			//KPrint("hey\n");
			for(int i = 0; (UINT)name[i] == (UINT)lnamec[i]; i++){
				if(name[i] == 0 && lnamec[i] == 0) goto found;
			}
		}
	}
	KFree(buffd);
	goto r;
	
	nomore:
	KFree(buffd);
	return -1;
	
	found:
	KFree(buffd);
	*resdir = KMalloc(sizeof(FAT_DIRENT));
	MemCopy(*resdir,d,sizeof(FAT_DIRENT));
	//KPrintf("found\n");
	return 0;
}

FNODE *Fat16RealLookup(FNODE *fnode, char *name){
	FNODE *newFnode;
	FAT_DIRENT *dirent;
	FatLookup16(fnode->ownerMount->data,fnode->data,name,&dirent);
	if(dirent){
		//KPrintf("Found dirent %s\n",dirent->name);
		newFnode = FnodeAlloc();
		newFnode->data = dirent;
		newFnode->name = KMalloc(StrLength(name));
		StrCopy(newFnode->name,name);
		newFnode->ownerMount = fnode->ownerMount;
		newFnode->method = &fat16DirMethod;
		FnodeAddChild(fnode,newFnode);
		return newFnode;
	}
	return 0;
}

int FatLookup(FNODE *fnode,char *name,FNODE **resnode){
	FNODE *found;
	//KPrintf("FAT Lookup\n");
	
	*resnode = 0;
	found = FnodeLookupChild(fnode,name);		//find last opened node
	if(!found)
		found = Fat16RealLookup(fnode,name);	//if not, find from disk
	if(!found) return -1;
	FnodeEnter(found);							//increase ref count
	*resnode = found;
	//KPrint("TMPFS lookup found\n");
	return 0;
}

int FatRead(FNODE *fnode,void *buffer,UINT offset,UINT size){
	FAT_DIRENT		*dir = fnode->data;
	FAT_MOUNT_DATA	*fmd = fnode->ownerMount->data;
	UINT 			fsize = dir->fileSize;
	UINT 			clus = (dir->fstClusHi << 16) | dir->fstClusLo;
	UINT 			szclus = fmd->bpb.bytsPerSec * fmd->bpb.secPerClus;
	UINT 			eoffset = offset + size;
	
	UINT 			coff = 0;
	UINT 			ceoff = szclus;
	UINT 			hasread = 0;
	void 			*cbuf = 0;
	
	loop:
	if (offset >= fsize) goto finish;
	if(clus >= 0xFFF7 && clus < 2) goto nomore;
	if(ceoff > fsize) ceoff = fsize;
	
	if(offset >= ceoff){
		clus = FatNextClus16(fmd,clus);
	}
	else if((offset >= coff) && (eoffset >= ceoff)){
		cbuf = FatReadClus16(fmd,&clus);
		MemCopy(buffer,((void*)(ULONG)cbuf + (offset - coff)),ceoff - offset);
		hasread += ceoff - offset;
		buffer = (void*)((ULONG)buffer + ceoff - offset);
		offset = ceoff;
	}
	else if((offset >= coff) && (eoffset <= ceoff)){
		cbuf = FatReadClus16(fmd,&clus);
		MemCopy(buffer,(void*)((ULONG)cbuf + (offset - coff)),eoffset - offset);
		hasread += eoffset - offset;
		goto finish;
	}
	
	if(cbuf) KFree(cbuf);
	coff += szclus;
	ceoff +=szclus;
	goto loop;
	
	nomore:
	finish:
	if(cbuf) KFree(cbuf);
	return hasread;
}

int Fat16Init(){
	FsRegister(&fat16Fs);
	return 0;
}