/*
Scott Visser
csce2110 program 2
Node header file
Node methods defined
*/

// add data to end of bucket (or empty bucket)
Node* Node::case0(int datainput)
{
	class Node *temp;
	temp = new Node;
	temp->inputdata(datainput);
	return temp;
};

// sets node data member to user input
void Node::inputdata(int datainput)
{
	data=datainput;
};

// recursively displays all data in bucket
void Node::show(void)
{
	if (next == NULL)
		cout << data;
	else
	{ 
		cout << data << " ";
		next->show();
	}
};

// add data to non empty bucket/finds empty bucket
void Node::case1(int datainput)
{
	if (datainput == data) // error
		cout << "WARNING: duplicate input: " << data << endl;
	else if (next == NULL)
		next = next->case0(datainput); // a
	else
		next->case1(datainput); // recurse to next node until empty node or duplicate input
};

// returns the next node to assign it to a different next member 
Node* Node::removeFirst(void)
{
	return next;	
};

// checks data member of next node
int Node::checknext(void)
{
	return data;
};

// remove node from bucket (if first node != NULL)
void Node::removeOther(int datainput)
{
	//recursivly traverse each node in the bucket untill the user input is found or end of bucket is reached
	if (next == NULL)
		cout << "WARNING: target value not found: " << datainput << endl;
	else if (next->checknext() == datainput)
		next = next->removeFirst();
	else
		next->removeOther(datainput);

};

// recursively traverses each node in a bucket  untill the user input is found or the end of the bucket is reached
void Node::search(int datainput)
{
	if (data == datainput)
		cout << "true" << endl;
	else if ((next == NULL) && (data != datainput))
		cout << "false" << endl;
	else
		next->search(datainput);
};







