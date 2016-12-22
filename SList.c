#include "SList.h"


void SListAppend(SLIST *list,SLIST_NODE *newNode){
	if(!list->lastNode){
		list->lastNode = newNode;
		list->firstNode = newNode;
		newNode->next = 0;
	}
	else {
		list->lastNode->next = newNode;
		list->lastNode = newNode;
	}
}

void SListPrepend(SLIST *list,SLIST_NODE *newNode){
	if(!list->firstNode){
		list->firstNode = newNode;
		list->lastNode = newNode;
		newNode->next = 0;
	}
	else{
		newNode->next = list->firstNode;
		list->firstNode = newNode;
	}
}
void SListUnlink(SLIST *list,SLIST_NODE *node){
	SLIST_NODE *prevNode = list->firstNode;
	if(prevNode == node) prevNode = 0;
	while(prevNode){
		if(prevNode->next == node) break;
		if(prevNode->next == 0) return; //error
		prevNode = prevNode->next;
	}
	if(!prevNode)
		list->firstNode = node->next;
	else
		prevNode->next = node->next;
	if(!node->next){
		list->lastNode = prevNode;
	}
	return;
}

void SListDump(SLIST *list){
	SLIST_NODE *node = list->firstNode;
	KPrintf("firstNode %x lastNode %x\n",list->firstNode,list->lastNode);
	while(node){
		KPrintf("node at %x data: %i next: %x\n",node,node->data,node->next);
		node = node->next;
	}
}
