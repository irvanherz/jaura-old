#ifndef DLIST_H
#define DLIST_H

typedef struct _DLIST_NODE {
	struct _DLIST_NODE	*next;
	struct _DLIST_NODE	*prev;
	void 				*data;
} DLIST_NODE;

typedef struct _DLIST {
	DLIST_NODE			*firstNode;
	DLIST_NODE			*lastNode;
} DLIST;

void DListInsertAfter(DLIST *list,DLIST_NODE *node,DLIST_NODE *newNode);
void DListInsertBefore(DLIST *list,DLIST_NODE *node,DLIST_NODE *newNode);
void DListPrepend(DLIST *list,DLIST_NODE *newNode);
void DListAppend(DLIST *list,DLIST_NODE *newNode);
void DListUnlink(DLIST *list,DLIST_NODE *node);
void DListDump(DLIST *list);
#endif
