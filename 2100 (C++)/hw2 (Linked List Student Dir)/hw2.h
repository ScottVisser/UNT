/*
Scott Visser
csce2100 hw2
main header file (class declerations and libraries)
*/
//libraries
#include <cstdlib>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
//NAMESPACE
using namespace std;
//NODE CLASS DECLERATION 
class Node
{
	private:
	 int data;
	 class Node *prev;
	 class Node *next;
	public:
	 Node();
	 Node* case0(int datainput);
	 void inputdata(int datainput);
	 void print();
	 int checkprev();
	 int checknext();
	 Node* case1(int datainput, Node* current);
	 Node* case1r(int datainput, Node* current);
	 void setnext(Node* current);
	 void setprev(Node* current);
	 void printall();
	 void case2(int datainput, Node* current);
	 void case2r(int datainput, Node* current);
	 Node* getnext();
	 Node* getprev();
	 void search(int datainput);
};
Node::Node() //CONSTRUCTOR
{
	data= -1;
	prev=NULL;
	next=NULL;
};
//LIST CLASS DECLERATION
class List
{
	private:
	 class Node *tail;
	 class Node *head;
	 class Node *current;
	public:
	 List();
	 void addleft(int datainput);
	 void addright(int datainput);
	 void left();
	 void right();
	 void printall();
	 void search(int datainput);
};
List::List()//CONSTRUCTOR
{
	tail=NULL;
	head=NULL;
	current=NULL;
};
