

// It prints the bits in bitmap as 0s and 1s.
void printBits(unsigned int bitmap) {
    unsigned int i;;
    for (i = 1 << 31; i > 0; i = i/2) {
        (bitmap & i)?  printf("1"): printf("0");
    }
    printf("\n");
    printf("10987654321098765432109876543210\n");
}


// Sets the ith bit in *bitmap with the value in bitValue (0 or 1)
void setBitAt( unsigned int *bitmap, int i, int bitValue ) {
    unsigned int bit = (1 << i);
    (bitValue)?(*bitmap = ((*bitmap)|bit)):(*bitmap=((*bitmap)&(~bit)));
}

// It returns the bit value (0 or 1) at bit i
int getBitAt( unsigned int bitmap, unsigned int i) {
	// Add your code here
    
    return (bitmap & (1 << i))? 1: 0;
}

// It returns the number of bits with a value "bitValue".
// if bitValue is 0, it returns the number of 0s. If bitValue is 1, it returns the number of 1s.
int countBits( unsigned int bitmap, unsigned int bitValue) {
	// Add your code here

    unsigned int bit;
    int n1, n2, i;
    for (i = 0, n1 = 0, n2 = 0; (i<32)&&(bit=(1<<i)); i++) {
        (bitmap&bit)?n2++:n1++;
    }
    return (bitValue)?n2:n1;
}

// It returns the number of largest consecutive 1s in "bitmap".
// Set "*position" to the beginning bit index of the sequence.
int maxContinuousOnes(unsigned int bitmap, int * position) {
	// Add your code here
    
    int array[40][2],i,j,count,max;
    unsigned int bit = 1;
    for (i = 0, j = 0, count = 0, max = 0; (i < 32)&&(bit = (1<<i));i++) {
        if (bit&bitmap) {
	    count++;
	}
	else {
	    if (count > 0) {
	        array[j][0] = count;
		array[j++][1] = i - count;
	    }
	    count = 0;
	}
    }
    for (i = 0; i < j; i++) {
        if (array[i][0] > array[max][0]) {
	    max = i;
	}
    }
    *position = array[max][1];
    return array[max][0];
}


