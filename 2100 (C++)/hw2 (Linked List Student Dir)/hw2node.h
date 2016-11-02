/*
Scott Visser 
csce2100 hw2
(private) Node class functions/opperations
*/

//addleft/right (empty list)
Node* Node::case0(int datainput)
{
	class Node *temp;
	temp = new Node;
	temp->inputdata(datainput);
	return temp;
};
//STORE DATA TO A TEMP BEFORE ASSIGNING POINTERS
void Node::inputdata(int datainput)
{
	data=datainput;
};
//CHECKS TO SEE IF THE PREV POINTER NODE POINTS TO ANYTHING
int Node::checkprev()
{
	if (prev==NULL)
	 return 0;
	else
	 return 1;
};
//SIMILAR TO PREV
int Node::checknext()
{
	if (next==NULL)
	 return 0;
	else
	 return 1;
};
//ADDLEFT BUT NO PREV LIST ITEM
Node* Node::case1(int datainput, Node* current)
{
	class Node *temp;
	temp = new Node;
	temp->inputdata(datainput);
	prev=temp;
	temp->setnext(current);
	return temp;
};
//ADDLEFT BUT NO NEXT LIST ITEM
Node* Node::case1r(int datainput, Node* current)
{
	class Node *temp;
	temp = new Node;
	temp->inputdata(datainput);
	next=temp;
	temp->setprev(current);
	return temp;
};
//REASSIGNS NEXT POINTER TO THE POINTER PASSED TO THE FUNCTION
void Node::setnext(Node* current)
{
	next = current;
};
//ADDLEFT (INSERT INBETWEEN NODES)
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
//CASE 2 BUT FOR ADDRIGHT
void Node::case2r(int datainput, Node* current)
{
	class Node *temp;
	class Node *temp1;
	temp1 = new Node;
	temp1 = next;
	temp = new Node;	
	temp->inputdata(datainput);
	temp1->setprev(temp);
	temp->setnext(temp1);
	temp->setprev(current);
	next = temp;
};
//SIMILAR TO SET NEXT
void Node::setprev(Node* current)
{
	prev = current;
};
//GETNEXT POINTER
Node* Node::getnext()
{
	next->print();
	return next;
};
Node* Node::getprev()
{
	prev->print();
 	return prev;
};
//SEARCH FUNCTION DEFINED
void Node::search(int datainput)
{
	if (datainput==data)
	 cout << "true" << endl;
	else if (next==NULL)
	 cout << "false" << endl;
	else
	 next->search(datainput);
};

