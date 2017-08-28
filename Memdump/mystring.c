
#include <stdlib.h>
#include "mystring.h"

int mystrlen(char * s) {
    char * temp = s;
    for (; *temp; ++temp);
    return (temp - s);
}

char * mystrcpy(char * dest, char * src) {
	char * rdest = dest;
	while (* src != '\0') {
	    *dest++ = *src++;
	}
	*dest++ = '\0';
	return rdest;
}

char * mystrcat(char * dest, char * src) {
	char * rdest = dest;
	while (*dest) dest++;
	while (* dest++ = * src++);
	return rdest;
}

int mystrcmp(char * s1, char * s2) {
	int i = 0;
	while (s1[i] != '\0' || s2[i] != '\0') {
	    if (s1[i] > s2[i]) {
	        return 1;
	    }
	    if (s1[i] < s2[i]) {
	        return -1;
	    }
	    i++;
	}
	return 0;
}

char * mystrstr(char * hay, char * needle) {
	while (*hay) {
	    char * p1 = hay;
	    char * p2 = needle;
	    while (*hay && *p2 && *hay == *p2) {
	        hay++;
		p2++;
	    }
	    if (!*p2) {
	        return p1;
	    }
	    hay = p1 + 1;
	}
	return NULL;
}

char * mystrdup(char * s) {
	char * temp = malloc(mystrlen(s) + 1);
	if (temp == NULL) {return NULL;}

	mystrcpy(temp, s);
	return temp;
}

char * mymemcpy(char * dest, char * src, int n) {
	char * rdest = dest;
	char * rsrc = src;
	while (n--) {
	    *rdest++ = *rsrc++;
	}
	return dest;
}

