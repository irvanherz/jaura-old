#include "DList.h"


void DListInsertAfter(DLIST *list,DLIST_NODE *node,DLIST_NODE *newNode){
	if(!node){ //nothing? append!
		if(!list->lastNode){
			list->lastNode = newNode;
			list->firstNode = newNode;
			newNode->prev = 0;
			newNode->next = 0;
		}
		else {
			newNode->next = 0;
			newNode->prev = list->lastNode;
			list->lastNode->next = newNode;
			list->lastNode = newNode;
		}
		return;
	}
	newNode->prev = node;
	if(!node->next){
		list->lastNode = newNode;
	}
	else {
		newNode->next = node->next;
		node->next->prev = newNode;
		node->next = newNode;
	}
}

void DListInsertBefore(DLIST *list,DLIST_NODE *node,DLIST_NODE *newNode){
	if(!node) //nothing? prepend!
	{
		if(!list->firstNode){
			list->firstNode = newNode;
			list->lastNode = newNode;
			newNode->prev = 0;
			newNode->next = 0;
		}
		else{
			newNode->prev = 0;
			newNode->next = list->firstNode;
			list->firstNode->prev = newNode;
			list->firstNode = newNode;
		}
		return;
	}
	newNode->next = node;
	if(!node->prev){
		list->firstNode = newNode;
	}
	else {
		newNode->prev = node->prev;
		node->prev->next = newNode;
		node->prev = newNode;
	}
}

void DListPrepend(DLIST *list,DLIST_NODE *newNode){
	if(!list->firstNode){
		list->firstNode = newNode;
		list->lastNode = newNode;
		newNode->prev = 0;
		newNode->next = 0;
	}
	else{
		newNode->prev = 0;
		newNode->next = list->firstNode;
		list->firstNode->prev = newNode;
		list->firstNode = newNode;
	}
}

void DListAppend(DLIST *list,DLIST_NODE *newNode){
	if(!list->lastNode){
		list->lastNode = newNode;
		list->firstNode = newNode;
		newNode->prev = 0;
		newNode->next = 0;
	}
	else {
		newNode->next = 0;
		newNode->prev = list->lastNode;
		list->lastNode->next = newNode;
		list->lastNode = newNode;
	}
}

void DListUnlink(DLIST *list,DLIST_NODE *node){
	if(!node->prev)
		list->firstNode = node->next;
	else
		node->prev->next = node->next;
	if(!node->next){
		list->lastNode = node->prev;
	}
	else
		node->next->prev = node->prev;
}

void DListDump(DLIST *list){
	DLIST_NODE *node = list->firstNode;
	while(node){
		KPrintf("node at %x data: %i prev: %x next: %x\n",node,node->data,node->prev,node->next);
		node = node->next;
	}
}
