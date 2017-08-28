
goal: testmemdump mem convert test_bits test_mystring test_array

testmemdump: mymemdump.c testmemdump.c obj/orgmemdump.o
	gcc -std=gnu99 -g -o testmemdump testmemdump.c mymemdump.c obj/orgmemdump.o

mem: mymemdump.c mem.c
	gcc -std=gnu99 -g -o mem mymemdump.c mem.c

convert: convert.c
	gcc -g -o convert convert.c -lm

test_bits: test_bits.c
	gcc -g -o test_bits test_bits.c bits.c

test_array: test_array.c array.c
	gcc -std=gnu99 -g -o test_array test_array.c array.c

test_mystring: test_mystring.c mystring.c
	gcc -std=gnu99 -g -o test_mystring test_mystring.c mystring.c

clean:
	rm -f testmemdump mem convert test_bits





