all: mytest

problem=DLList.cpp

mytest: mytest.c DLList.cpp DLList.h $(problem)
	g++ -g -o mytest mytest.c $(problem)

clean:
	rm -f *.o *.out *.txt mytest none
