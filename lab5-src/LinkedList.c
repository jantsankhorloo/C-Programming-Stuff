
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "LinkedList.h"

//
// Initialize a linked list
//
void llist_init(LinkedList * list)
{
	list->head = NULL;
}

//
// It prints the elements in the list in the form:
// 4, 6, 2, 3, 8,7
//
void llist_print(LinkedList * list) {
	
	ListNode * e;

	if (list->head == NULL) {
		printf("{EMPTY}\n");
		return;
	}

	printf("{");

	e = list->head;
	while (e != NULL) {
		printf("%d", e->value);
		e = e->next;
		if (e!=NULL) {
			printf(", ");
		}
	}
	printf("}\n");
}

//
// Appends a new node with this value at the beginning of the list
//
void llist_add(LinkedList * list, int value) {
	// Create new node
	ListNode * n = (ListNode *) malloc(sizeof(ListNode));
	n->value = value;
	
	// Add at the beginning of the list
	n->next = list->head;
	list->head = n;
}

//
// Returns true if the value exists in the list.
//
int llist_exists(LinkedList * list, int value) {
	ListNode * e;
	e = list->head;
	while (e != NULL) {
	    if (e->value == value) {
	        return 1;
	    }
	    e = e->next;
	}
	return 0;
}

//
// It removes the entry with that value in the list.
//
int llist_remove(LinkedList * list, int value) {
	ListNode *curr, *prev;
	prev = NULL;
	for (curr = list->head; curr != NULL; prev = curr, curr = curr->next){
	    if (curr->value == value) {
	        if (prev == NULL) {
		    list->head = curr->next;
		}
		prev -> next = curr ->  next;
		free(curr);
	    	return 1;
	    }
	}
	return 0;
}

//
// It stores in *value the value that correspond to the ith entry.
// It returns 1 if success or 0 if there is no ith entry.
//
int llist_get_ith(LinkedList * list, int ith, int * value) {
	ListNode *curr = list->head;
	int i;
	i = 0;

	while (curr != NULL) {
	    if (i == ith) {
	        *value++ = curr->value;
		return 1;
	    }
	    i++;
	    curr = curr -> next;
	}
	return 0;
}

//
// It removes the ith entry from the list.
// It returns 1 if success or 0 if there is no ith entry.
//
int llist_remove_ith(LinkedList * list, int ith) {
	int i;

	ListNode *curr, *temp;
	curr = list->head;
	temp = NULL;

	for (i = 0; i < (ith - 1); i++) {
	    if (curr->next == NULL) {
	        return 0;
	    }
	    curr = curr->next;
	}

	temp = curr->next;
	curr->next = temp->next;
	free(temp);
	return 1;
}

//
// It returns the number of elements in the list.
//
int llist_number_elements(LinkedList * list) {
	int i;
	i = 0;
	ListNode *curr = list->head;
	while (curr != NULL) {
	     i++;
	     curr = curr->next;
	}
	return i;
}


//
// It saves the list in a file called file_name. The format of the
// file is as follows:
//
// value1\n
// value2\n
// ...
//
int llist_save(LinkedList * list, char * file_name) {
	FILE * fd = fopen(file_name, "w");
	
	ListNode * curr = list->head;
	int element;
	
	if (fd == NULL) {
	    return 0;
	} 
	while (curr != NULL) {
	    element = curr -> value;
	    fprintf(fd, "%d\n", element);
	    curr = curr->next;
	}
	fclose(fd);
	return 0;	
}

//
// It reads the list from the file_name indicated. If the list already has entries, 
// it will clear the entries.
//
int llist_read(LinkedList * list, char * file_name) {
	FILE * fd = fopen(file_name, "w+");
        
	ListNode *e = list->head;
	int element;
	
	while (e != NULL) {
	    e->value = 0;
	    e = e->next;
	}

	if (fd == NULL) {
	    return 0;
	}
        
	if (e) {
	    e->value = element;
	    e = e->next;
	    fscanf(fd, "%d",&(e->value));
	}
	fclose(fd);
	return 1;
}


//
// It sorts the list. The parameter ascending determines if the
// order si ascending (1) or descending(0).
//
void llist_sort(LinkedList * list, int ascending) {
    int swapped;
    ListNode *ptr1;
    ListNode *lptr = NULL;

    if (ptr1 == NULL) {
        return;
    }
    if (ascending == 1) {
        do {
            swapped = 0;
	    ptr1 = list->head;
	    while (ptr1->next != lptr) {
	        if (ptr1->value > ptr1->next->value) {
		    int temp = ptr1->value;
		    ptr1->value = ptr1->next->value;
		    ptr1->next->value = temp;
		    swapped = 1;
	        }
	        ptr1 = ptr1->next;
	    }
	    lptr = ptr1;
        } while (swapped);
    }
    else {
        do {
	    swapped = 0;
	    ptr1 = list->head;
	    while (ptr1->next != lptr) {
	        if (ptr1->value < ptr1->next->value) {
		    int temp = ptr1->value;
		    ptr1->value = ptr1->next->value;
		    ptr1->next->value = temp;
		    swapped = 1;
		}
		ptr1 = ptr1 -> next;
	    }
	    lptr = ptr1;
	} while (swapped);
    }
}

//
// It removes the first entry in the list and puts value in *value.
// It also frees memory allocated for the node
//
int llist_remove_first(LinkedList * list, int * value) {
	ListNode * nextNode = NULL;
	if (list->head == NULL) {
	    return 0;
	}
	nextNode = list->head->next;
	*value = list->head->value;
	free(list->head);
	list->head = nextNode;
	return 1;
}

//
// It removes the last entry in the list and puts value in *value/
// It also frees memory allocated for node.
//
int llist_remove_last(LinkedList * list, int *value) {
	
	if (list->head == NULL) {
	    return 0;
	}

	if (list->head->next == NULL) {
	    *value = list->head->value;
	    free(list->head);
	    list->head = NULL;
	    return 1;
	}
	else {
	    ListNode *curr = list->head;	
	    while (curr->next->next!=NULL) {
	        curr = curr->next;
	    }
	    *value = curr->next->value;
	    free(curr->next);
	    curr->next = NULL;
	    return 1;
	}
	return 0;
}

//
// Insert a value at the beginning of the list.
// There is no check if the value exists. The entry is added
// at the beginning of the list.
//
void llist_insert_first(LinkedList * list, int value) {
    ListNode *e = (ListNode*)malloc(sizeof(ListNode));
    e->value = value;
    e->next = list->head;
    list->head = e;
}

//
// Insert a value at the end of the list.
// There is no check if the name already exists. The entry is added
// at the end of the list.
//
void llist_insert_last(LinkedList * list, int value) {
        ListNode *curr = list->head;
	if (curr == NULL) {
	    list->head = (ListNode*)malloc(sizeof(ListNode));
	    list->head->value = value;
	    list->head->next = NULL;
	    return;
	}
	while (curr->next != NULL) {
	    curr=curr->next;
	}
	ListNode *e = (ListNode*)malloc(sizeof(ListNode));
	e->value = value;
	e->next = NULL;
	curr->next = e;
}

//
// Clear all elements in the list and free the nodes
//
void llist_clear(LinkedList *list)
{
    ListNode *e, *temp;
    temp = list->head;
    while (temp) {
        e = temp ->next;
	free(temp);
	temp = e;
    }
    list->head = NULL;
}
