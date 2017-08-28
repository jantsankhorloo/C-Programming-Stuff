#include "mysort.h"
#include <alloca.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

//

//
// See test_sort to see how to use mysort.
/**
 * @brief Arbitrary sort func
 *
 * Sort an array of element of any type
 * using "compFunc" to sort the elements.
 * 
 * The elements are sorted such as:
 * 
 * if ascending != 0
 *   compFunc( array[ i ], array[ i+1 ] ) <= 0
 * else
 *   compFunc( array[ i ], array[ i+1 ] ) >= 0
 * 
 * @param n Number of elements.
 * @param elementSize Size of each element.
 * @param array Pointer to an array of arbitrary type.
 * @param ascending Boolean controlling the direction of the sort.
 * @param compFunc Comparison funciton.
 **/
void mysort(int n, int elementSize, void * array, int ascending, CompareFunction compFunc)
{

	/** @todo **/
	void *tmp = malloc(elementSize);
	int flag = 1;
	while (flag) {
	    flag = 0;
	    int i;
	    for (i = 0; i < n - 1; i++) {
	        void *ptr1 = (void*)((char*)array+i*elementSize);
			void *ptr2 = (void*)((char*)array+(i+1)*elementSize);
			if (ascending) {
			    if (compFunc(ptr1, ptr2) > 0) {
			        memcpy(tmp, ptr1, elementSize);
					memcpy(ptr1, ptr2, elementSize);
					memcpy(ptr2, tmp, elementSize);
					flag = 1;
		    	}
			}
	        else {
			    if (compFunc(ptr1, ptr2) < 0) { 
			        memcpy(tmp, ptr1, elementSize);
					memcpy(ptr1, ptr2, elementSize);
					memcpy(ptr2, tmp, elementSize);
					flag = 1;
		    	}
			}
	    }
	}
	free(tmp);
}


