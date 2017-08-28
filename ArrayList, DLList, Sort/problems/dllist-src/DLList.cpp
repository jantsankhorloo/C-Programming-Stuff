#include "DLList.h"

DLList::DLList()
{
    head = new DLNode();
    head->next = head;
    head->prev = head;
}

DLList::~DLList()
{
    DLNode * e = head -> next;
    DLNode * tmp;
    while (e != head) {
    	tmp = e->next;
	delete e;
	e = tmp;
    }
}

void DLList::print()
{
    DLNode * e = head->next;
    while (e != head) {
        std::cout << (e->data) << std::endl;
	e = e->next;
    }
}

void DLList::printSorted()
{
    
    DLNode *ptr, *dummy, *tmpdummy, *dummy2 = new DLNode();
    /*int swap = 1;
    while (swap) {
        swap = 0;
	ptr = head->next;
	while (ptr != head) {
	     if (ptr->data < ptr->next->data) {
	          swap = 1;
		  dummy->data = ptr->data;
		  tmpdummy->data = ptr->next->data;
		  dummy2->data = dummy->data;
	     }
	     ptr = ptr->next;
	     std::cout << tmpdummy->data << std::endl;
	}
    }*/
   
}


void DLList::insertFront(int data)
{
    DLNode * e = new DLNode();
    e->data = data;
    
    e->next = head->next;
    e->prev = head;
    e->next->prev = e;
    e->prev->next = e;
}

bool DLList::removeLast(int & data)
{
	if (head->next == head) {
	    return false;
	}
	DLNode * e;
	e = head->prev; //points to last
	e->prev->next = head;
	head->prev = e->prev;
	data = e->data;
	delete e;
	return true;
}

DLList * DLList::difference(DLList & list)
{
	DLList * diff = new DLList();
	
	DLNode * node = head->next;
	DLNode *e, *tmp;
	bool flag = true;

	while (node != head) {
	    e = list.head ->next;
	    while (e != list.head) {
	        if (node->data == e->data) {
		    flag = false;
		    break;
		}
		e = e->next;
	    }
	    if (flag == true) {
	        DLNode * tmpnode = new DLNode();
	    	tmpnode->data = node->data;
		tmp = diff->head;
		tmpnode->next = tmp;
		tmpnode->prev = tmp->prev;
		tmpnode->prev->next = tmpnode;
		tmp->prev = tmpnode;
	    }
	    flag = true;
	    node = node->next;
	}
	return diff;
}

DLList * DLList::getRange(int start, int end)
{
	DLList * range = new DLList();
	DLNode * e = head->next;
	int i;
	for (i = 0; e != head; i++) {
	    if (i >= start && i <= end) {
	         insertFront(e->data);
	    }
	    e = e->next;
	}
	return range;
}

DLList * DLList::intersection(DLList & list)
{
	DLList * inter = new DLList();
	DLNode * node = head->next;
	DLNode *e, *tmp;

	while (node != head) {
	    e = list.head->next;
	    while (e != list.head) {
	         if (node ->data == e->data) {
		     DLNode *tmpnode = new DLNode();
		     tmpnode->data = node->data;
		     tmp = inter->head;
		     tmpnode->next = tmp;
		     tmpnode->prev = tmp->prev;
		     tmpnode->prev->next = tmpnode;
		     tmp->prev = tmpnode;
		     break;
		 }
		 e = e->next;
	    }
	    node = node->next;
	}
	return  inter;
}

void DLList::removeRange(int start, int end)
{

}
