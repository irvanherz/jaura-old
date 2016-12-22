#ifndef SLIST_H
#define SLIST_H

typedef struct _SLIST_NODE {
	struct _SLIST_NODE	*next;
	void				*data;
} SLIST_NODE;

typedef struct _SLIST {
	SLIST_NODE			*firstNode;
	SLIST_NODE			*lastNode;
} SLIST;

#endif
