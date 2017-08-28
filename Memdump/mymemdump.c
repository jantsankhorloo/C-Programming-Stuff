
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void mymemdump(FILE * fd, char * p , int len) {
    // Add your code here.
    // You may see p as an array.
    // p[0] will return the element 0 
    // p[1] will return the element 1 and so on
    
    int i, j, k, r;
   // fprintf(fd, "0x%016lX: ", (unsigned long) p); // Print address of the beginning of p. You need to print it every 16 byte
   //

    k = 16;
    r = 16;

    for (i=0; i < len; i+=16) {
       fprintf(fd, "0x%016lX: ", (unsigned long) p + i);
       int c = p[i]&0xFF; // Get value at [p]. The &0xFF is to make sure you truncate to 8bits or one byte.

        // Print first byte as hexadecimal
       for (j = 0; j < 16; j++ ) {
            int c = p[i + j]&0xFF;
	    
	    if (len == 20 && i == 16) {
	        if (k < 20) {
		    fprintf(fd, "%02X ", c);
		    k++;
		}
	    }

	    else {fprintf(fd, "%02X ", c);}
            
	    if ((len - j - 1) == 0) {
	       int temp;
	       temp = abs(16 - len);
	       while (temp > 0) {
		    fprintf(fd, "   ");
		    temp--;
	       }
	       break;
	    }
       }

       if (len == 20 && i != 0) {
           int count = 12;
	   while (count > 0) {
	       fprintf(fd, "   ");
	       count--;
	   }
       }
       
       fprintf(fd, " ");       

       // Print first byte as character. Only print characters >= 32 that are the printable characters.
       
       for (j = 0; j < 16; j++) {
           int c = p[i + j]&0xFF;
	   
	   if (len == 20 && i == 16) {
	       if (r < 20) {
	           fprintf(fd, "%c", (c >= 32 && c <= 127)?c:'.');
		   r++;
	       }
	   }

	   else {fprintf(fd, "%c", (c >= 32 && c <= 127)?c:'.');}
           
	   if ((len - j - 1) == 0) {
	       break;
	   }
       }
       if (i % 16 == 0 ) {
        fprintf(fd,"\n");
      }
    }

}

