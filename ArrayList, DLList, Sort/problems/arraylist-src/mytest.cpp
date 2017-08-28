#include <iostream>
#include <sstream>
#include <string>
#include "ArrayList.cpp"

inline int getTestNum(std::string s) {
	const char * str = s.c_str();
	for (; *str && !('0' <= *str && *str <= '9'); ++str);
	std::string copy(str);
	return std::stoi(copy);
}

void printList(ArrayList<std::string> list)
{
	std::cout<<"Size: "<<list.size()<<std::endl;
	std::cout<<"{";
	for (int x = 0; x < list.size(); ++x) {
		if (x && !(x % 5))
			std::cout<<std::endl;
		std::cout<<list[x]<<((x == list.size() - 1) ? "" : ", ");
	} std::cout<<"}"<<std::endl;
}

void printList(ArrayList<int> list)
{
	std::cout<<"Size: "<<list.size()<<std::endl;
	std::cout<<"{";
	for (int x = 0; x < list.size(); ++x) {
		if (x && !(x % 5))
			std::cout<<std::endl;
		std::cout<<list[x]<<((x == list.size() - 1) ? "" : ", ");
	} std::cout<<"}"<<std::endl;
}

void test1()
{
	std::cout<<std::endl;
	std::cout<<"*******************************************************************"<<std::endl;
	ArrayList<int> list;

	list.add(4);
	list.add(5);
	list.add(6);
	list.add(12);
	list.add(13);

	std::cout<<"Size: "<<list.size()<<std::endl;
	std::cout<<"{";
	for (int x = 0; x < list.size(); ++x) {
		std::cout<<list[x]<<((x == list.size() - 1) ? "" : ", ");
	} std::cout<<"}"<<std::endl;
}

void test2()
{
	std::cout<<std::endl;
	std::cout<<"*******************************************************************"<<std::endl;
	ArrayList<int> list;

	list << 12 << 1103 << 12 << 55 << 14;

	std::cout<<"Size: "<<list.size()<<std::endl;
	std::cout<<"{";
	for (int x = 0; x < list.size(); ++x) {
		std::cout<<list[x]<<((x == list.size() - 1) ? "" : ", ");
	} std::cout<<"}"<<std::endl;
}

void test3()
{
	std::cout<<std::endl;
	std::cout<<"*******************************************************************"<<std::endl;
	ArrayList<int> list;

	list.push_front(4); list.push_front(8);
	list.push_back(12); list.push_back(16);

	std::cout<<"Size: "<<list.size()<<std::endl;
	std::cout<<"{";
	for (int x = 0; x < list.size(); ++x) {
		std::cout<<list[x]<<((x == list.size() - 1) ? "" : ", ");
	} std::cout<<"}"<<std::endl;
}

void test4()
{
	std::cout<<std::endl;
	std::cout<<"*******************************************************************"<<std::endl;
	ArrayList<int> list;

	list.add(4);  
	list.add(5);  
	list.add(6);  
	list.add(12);  
	list.add(13);

	std::cout<<"Size: "<<list.size()<<std::endl;
	std::cout<<"{";
	for (int x = 0; x < list.size(); ++x) {
		std::cout<<list[x]<<((x == list.size() - 1) ? "" : ", ");
	} std::cout<<"}"<<std::endl<<std::endl;

	std::cout<<"Removing 6..."<<std::endl<<std::endl;
	list.remove(list.indexOf(6));

	std::cout<<"Size: "<<list.size()<<std::endl;
	std::cout<<"{";
	for (int x = 0; x < list.size(); ++x) {
		std::cout<<list[x]<<((x == list.size() - 1) ? "" : ", ");
	} std::cout<<"}"<<std::endl;
}

void test5()
{
	std::cout<<std::endl;
	std::cout<<"*******************************************************************"<<std::endl;
	ArrayList<double> list;

	list<< 2.4 << 78.2 << 1.3 << 0.0001 << 207.12;

	std::cout<<"Size: "<<list.size()<<std::endl;
	std::cout<<"{";
	for (int x = 0; x < list.size(); ++x) {
		std::cout<<list[x]<<((x == list.size() - 1) ? "" : ", ");
	} std::cout<<"}"<<std::endl<<std::endl;

	std::cout<<"Removing index 22..."<<std::endl<<std::endl;
	list.remove(22);

	std::cout<<"Size: "<<list.size()<<std::endl;
	std::cout<<"{";

	for (int x = 0; x < list.size(); ++x) {
		std::cout<<list[x]<<((x == list.size() - 1) ? "" : ", ");
	} std::cout<<"}"<<std::endl;
}

void test6()
{
	std::cout<<std::endl;
	std::cout<<"*******************************************************************"<<std::endl;
	ArrayList<double> list;

	list << 4 << 32.14 << 908.3 << 0.0000001 << 12.31 << 14.0;
	
	std::cout<<"Size: "<<list.size()<<std::endl;
	std::cout<<"{";
	for (int x = 0; x < list.size(); ++x) {
		std::cout<<list[x]<<((x == list.size() - 1) ? "" : ", ");
	} std::cout<<"}"<<std::endl<<std::endl;

	std::cout<<"Sorting list..."<<std::endl<<std::endl;
	list.sort();

	std::cout<<"Size: "<<list.size()<<std::endl;
	std::cout<<"{";
	for (int x = 0; x < list.size(); ++x) {
		std::cout<<list[x]<<((x == list.size() - 1) ? "" : ", ");
	} std::cout<<"}"<<std::endl;
}

void test7()
{
	std::cout<<std::endl;
	std::cout<<"*******************************************************************"<<std::endl;
	ArrayList<int> list;

	list << 13;
	for (int x = 0; x < 100; list += x++);


	std::cout<<"Size: "<<list.size()<<std::endl;
	std::cout<<"{";
	for (int x = 0; x < list.size(); ++x) {
		if (x && !(x % 5))
			std::cout<<std::endl;
		std::cout<<list[x]<<((x == list.size() - 1) ? "" : "\t");
	} std::cout<<"}"<<std::endl<<std::endl;

	std::cout<<"Making a copy..."<<std::endl<<std::endl;
	ArrayList<int> other = list;

	std::cout<<"Size: "<<list.size()<<std::endl;
	std::cout<<"{";
	for (int x = 0; x < list.size(); ++x) {
		if (x && !(x % 5))
			std::cout<<std::endl;
		std::cout<<list[x]<<((x == list.size() - 1) ? "" : "\t");
	} std::cout<<"}"<<std::endl<<std::endl;

	std::cout<<"Equal...? "<< ((list == other) ? "Yes." : "No.")<< std::endl;
}

void test8()
{
	std::cout<<std::endl;
	std::cout<<"*******************************************************************"<<std::endl;

	ArrayList<std::string> list1;
	ArrayList<std::string> list2;

	list1<<std::string("I")<<std::string("have")<<std::string("words");
	printList(list1); std::cout<<std::endl;
	list2<<std::string("You")<<std::string("have")<<std::string("words");
	printList(list2); std::cout<<std::endl;

	std::cout<<"list1 << list2..."<<std::endl<<std::endl;
	list1 << list2;
	printList(list1); std::cout<<std::endl;

	bool ok;
	std::cout<<"Replacing first occurance of \"words\" with \"words,\"."<<std::endl;
	int index = list1.indexOf(std::string("words"));
	list1.remove(std::string("words"), &ok);
	std::cout<<"Ok? "<< ((ok) ? "Yes." : "No.")<<std::endl;
	list1.add(std::string("words,"), index);
	printList(list1);
}

void test9()
{
	std::cout<<std::endl;
	std::cout<<"*******************************************************************"<<std::endl;

	ArrayList<uint8_t> midterm_grades;
	midterm_grades << 8u << 0u << 12u << 0u << 0u << 1u;

	std::cout<<"Size: "<<midterm_grades.size()<<std::endl;
	std::cout<<"{";
	for (int x = 0; x < midterm_grades.size(); ++x) {
		std::cout<<(int) midterm_grades[x]<<((x == midterm_grades.size() - 1) ? "" : ", ");
	} std::cout<<"}"<<std::endl<<std::endl;

	std::cout<<"Contains(100)? "<<((midterm_grades.contains(100u)) ? "Yes." : "No.")<<std::endl;
	std::cout<<"IndexOf(0): "<<midterm_grades.indexOf(0)<<std::endl;
	std::cout<<"IndexOf(0, 2): "<<midterm_grades.indexOf(0, 2)<<std::endl;
	std::cout<<"LastIndexOf(0): "<<midterm_grades.lastIndexOf(0u)<<std::endl;

	std::cout<<std::endl<<"Clearing list..."<<std::endl;
	midterm_grades.clear();
	std::cout<<"Size: "<<midterm_grades.size()<<std::endl;
}

void test10()
{
	ArrayList<int> list1;
	int num = 0;
	for (int i = 0; i < 255; i++) {
		num += i;
		i % 2 ? list1.push_back(num) : list1.push_front(num);
	}
	printList(list1);

	std::cout<<std::endl<<"Contains(10011)? "<<((list1.contains(10011)) ? "Yes." : "No.")<<std::endl;
	std::cout<<"Contains(905)? "<<((list1.contains(905)) ? "Yes." : "No.")<<std::endl;

	bool ok;
	list1.remove(20503, &ok);
	std::cout<<"Remove(20503)? "<<(ok ? "Yes." : "No.")<<std::endl;
	list1.remove(20503, &ok);
	std::cout<<"Remove(20503) Again? "<<(ok ? "Yes." : "No.")<<std::endl<<std::endl;

	std::cout<<"Sorting"<<std::endl;
	list1.sort();
	printList(list1);
}


int main (int argc, char ** argv)
{
	if (argc < 2) {
		std::cerr<<"Invalid args."<<std::endl;
		std::cerr<<"Usage: mytest test1|test2|test3|test4|test5|test6|test7|test8|test9|test10";
		std::cerr<<std::endl;
		return -1;
	}

	int testNum = getTestNum(argv[1]);

	if (testNum < 1 && testNum > 10) {
		std::cerr<<"Invalid test number."<<std::endl;
		std::cerr<<"Usage: mytest test1|test2|test3|test4|test5|test6|test7|test8|test9|test10";
		std::cerr<<std::endl;
		return -2;
	}

	switch (testNum) {
		case 1:
			test1();
			break;
		case 2:
			test2();
			break;
		case 3:
			test3();
			break;
		case 4:
			test4();
			break;
		case 5:
			test5();
			break;
		case 6:
			test6();
			break;
		case 7:
			test7();
			break;
		case 8:
			test8();
			break;
		case 9:
			test9();
			break;
		case 10:
			test10();
			break;
	}

	return 0;
}
