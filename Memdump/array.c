
#include <stdio.h>

#include "array.h"

// Return sum of the array
double sumArray(int n, double * array) {
  double sum = 0;
  
  double * p = array;
  double * pend = p+n;

  while (p < pend) {
    sum += *p;
    p++;
  }

  return sum;
}

// Return maximum element of array
double maxArray(int n, double * array) {
    double  max;
    int i;

    max = array[0];

    for (i = 0; i < n; i++) {
	if (max < array[i]) {
	    max = array[i];
	}
    }
    return max;
}

// Return minimum element of array
double minArray(int n, double * array) {
    double min;
    int i;

    min = array[0];

    for (i = 0; i < n; i++) {
        if (min > array[i]) {
	    min = array[i];
	}
    }
    return min;
}

// Find the position int he array of the first element x 
// such that min<=x<=max or -1 if no element was found
int findArray(int n, double * array, double min, double max) {
    int i;
    
    for (i = 0; i < n; i++) {
        if (array[i] > min && array[i] < max) {
	    return i;
	}
    }
    return -1;
}

// Sort array without using [] operator. Use pointers 
// Hint: Use a pointer to the current and another to the next element
int sortArray(int n, double * array) {
    int i,j;
    double temp;

    for (i = 1; i < n; i++) {
        for (j = 0; j < n - 1;j++) {
	    if (*(array + j) > *(array + j + 1)) {
	        temp = *(array + j);
		*(array + j) = *(array + j + 1);
		*(array+ j + 1) = temp;
	    }
	}
    }
    return *array;
}

// Print array
void printArray(int n, double * array) {
    int i;
    for (i = 0; i < n; i++) {
        printf("%d:%f\n", i, array[i]);
    }
}

