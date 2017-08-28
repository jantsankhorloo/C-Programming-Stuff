#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

void defensiveBase(char num[], int basefrom, int baseto);
int toBase10(char num[], int base);
void fromBase10(int num, int base);

main(int argc, char *argv[]) {
    if (argv[1] == NULL ||
        argv[2] == NULL ||
	argv[3] == NULL) {
	printf("Usage:  convert <basefrom> <baseto> <number>\n");
        exit(0);
    }

    int basefrom, baseto;
    basefrom = atoi(argv[1]);
    baseto = atoi(argv[2]);
	
    defensiveBase(argv[3], basefrom, baseto);
    printf("Number read in base %d: %s\n", basefrom, argv[3]);
    int temp;
    temp = toBase10(argv[3], basefrom);
    printf("Converted to base 10: %d\n", temp);

    fromBase10(temp, baseto);
}

void defensiveBase(char num[], int basefrom, int baseto) {
   
   if (basefrom < 1 || basefrom > 26) {
       printf("The base should be between 2 and 25 inclusive\n");
       exit(0);
   }

   if (baseto < 1 || basefrom >= 26) {
       printf("The base should be between 2 and 25 inclusive\n");
       exit(0);
   }

   if (strlen(num) > 32) {
       printf("The number should not be longer than 32 digits\n");
       exit(0);
   }

   if (basefrom > 4) {
       char base_digits[36] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };

       int i = 0;

       do {
           int j;
	   int error = 1;

	   for (j = 0; j < basefrom; j++) {
		if (toupper(num[i]) == base_digits[j]) {
		    error = 0;
		}
	   }

	   if (error == 1) {
	       printf("Number read in base %d: ", basefrom);
	       int k;
	       for (k = 0; k < 6; k++) {
	           printf("%c", num[k]);
	       }
	       printf("\n");
	       printf("Wrong digit in number.\n");
	       exit(0);
	   }
	   i++;
       } while (num[i] != '\0');
   }
}

int toBase10(char num[], int base) {
    int val, i;
    val = 0;
    
    for (i = 0; i < strlen(num); i++) {
        int n;
	n = strlen(num) - i - 1;

	if (toupper(num[i]) > 57)
	    val += ((toupper(num[i]) - 55) * pow(base, n));
	else 
	    val += ((toupper(num[i]) - 48) * pow(base, n));
    }
    return val;
}

void fromBase10(int num, int base) {
    int result[64];
    char base_digits[26] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P'};

    int i, j;
    i = 0;

    while (num != 0) {
        result[i] = num % base;
	num = num / base;
	i++;
    }
    printf("Converted to base %d: ", base);
    for (j = i - 1; j >= 0; j--) {
        printf("%c", toupper(base_digits[result[j]]));
    }
    printf("\n");
}
