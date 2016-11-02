/*
Scott Visser
Csce2100
Hw2
Linked list implementation
*/

#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;

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
	 Node* case1(int datainput, Node* current);
	 void setnext(Node* current);
	 void setprev(Node* current);
	 void printall();
	 void case2(int datainput, Node* current);
};
Node::Node()
{
	data= -1;
	prev=NULL;
	next=NULL;
};
Node* Node::case0(int datainput)
{
	class Node *temp;
	temp = new Node;
	temp->inputdata(datainput);
	return temp;
};
void Node::inputdata(int datainput)
{
	data=datainput;
};
int Node::checkprev()
{
	if (prev==NULL)
	 return 0;
	else
	 return 1;
};
Node* Node::case1(int datainput, Node* current)
{
	class Node *temp;
	temp = new Node;
	temp->inputdata(datainput);
	prev=temp;
	temp->setnext(current);
	return temp;
};
void Node::setnext(Node* current)
{
	next = current;
};
void Node::case2(int datainput, Node* current)
{
	class Node *temp;
	class Node *temp1;
	temp1 = new Node;
	temp1 = prev;
	temp = new Node;	
	temp->inputdata(datainput);
	temp1->setnext(temp);
	temp->setprev(temp1);
	temp->setnext(current);
	prev = temp;
};
void Node::setprev(Node* current)
{
	prev = current;
};


class List
{
	private:
	 class Node *tail;
	 class Node *head;
	 class Node *current;
	public:
	 List();
	 void addleft(int datainput);
	 void printall();
};
List::List()
{
	tail=NULL;
	head=NULL;
	current=NULL;
};
void List::addleft(int datainput)
{
	class node *temp;
	if (current==NULL)
	{
		current = current->case0(datainput);
		tail=current;
		head=current;
	}
	else if (current->checkprev() == 0)
	{
		tail = current->case1(datainput,current);
	}
	else
	{
		current->case2(datainput,current);
	}
};
void List::printall()
{
	if (tail==NULL)
	 cout << "Error! Empty List" << endl;
	else
	 tail->printall();
};
void Node::printall()
{
	cout << data;
	if (next==NULL)
	 cout << endl;
	else
	{
	cout << "-";
	next->printall();
	}
};
void Node::print()
{
	cout << data << endl;
};


int main(void)
{
	class List list;

	string option;
	int datainput;
	
	cout << "Commands:" << endl;
	cout << "addleft x" << endl;
	cout << "addright x" << endl;
	cout << "right" << endl;
	cout << "left" << endl;
	cout << "search" << endl;
	cout << "print" << endl;
	cout << "quit" << endl << endl;

/****NEED HELP WITH INPUT******/
	while(1)
	{
		cout << "list> ";
		cin >> option >> datainput;

		if (option=="addleft")
		 list.addleft(datainput);

		else if (option=="print")
		 list.printall();	
		else if (option=="quit")
		 break;	
		else 
		 cout << "invalid input" << endl;

	}
		
return 0;
}
