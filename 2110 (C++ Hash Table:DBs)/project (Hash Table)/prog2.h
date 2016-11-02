/*
Scott Visser
csce 2110 Program 2
Main header file:  Classes/constructors defined
*/

// libraries
#include <cstdlib>
#include <iostream>
#include <string>
#include <stdio.h>
//namespace
using namespace std;

// Node class defined
class Node
{
	private:
	 int data;
	 class Node *next;
	public:
	 Node();
	 Node* case0(int datainput);
	 void case1(int datainput);
	 void inputdata(int datainput);
	 void show(void);
	 Node* removeFirst(void);
	 void removeOther(int datainput);
	 int checknext(void);
	 void search(int datainput);

};
//Node Constructor
Node::Node()
{
	data= -1;
	next = NULL;
};
//class set defined
class Set
{
	private:
	 class Node *bucket[7];
	 int bucketIndex;
	public:
	 Set();
	 void add(int datainput);
	 void show(void);
	 void remove(int datainput);
	 void search(int datainput);
};
//set constructor
Set::Set()
{
	int i;
	for (i=0; i<7; i++)
	 bucket[i] = NULL;
};
