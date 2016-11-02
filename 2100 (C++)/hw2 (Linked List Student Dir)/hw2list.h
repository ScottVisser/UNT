/*
Scott Visser
cse2100 Hw2
List class functions defined
*/

//ADDLEFT
void List::addleft(int datainput)
{
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
//ADDRIGHT SIMILAR TO ADDLEFT
void List::addright(int datainput)
{
	if (current == NULL)
	{
		current = current->case0(datainput);
		tail=current;
		head=current;
	}
	else if (current->checknext() == 0)
	{
		head = current->case1r(datainput,current);
	}
	else
	{
		current->case2r(datainput,current);
	}
};
//PRINTS ALL ELEMENTS IN LIST
void List::printall()
{
	if (tail==NULL)
	 cout << "Error! Empty List" << endl;
	else
	 tail->printall();
};
//MOVES CURRENT POINTER LEFT
void List::left()
{
	if (current==NULL)
	 cout << "Error! Empty List" << endl;
	else if (current->checkprev() == 0)
	{
		cout << "Error! End of List Reached" << endl;
	}
	else
	{
		current = current->getprev();
	}	
};
//MOVES CURRENT POINTER RIGHT
void List::right()
{
	if (current == NULL)
	 cout << "Error! Empty List" << endl;
	else if (current->checknext() == 0)
	{
		cout << "Error! End of List Reached" << endl;
	}
	else
	{
		current = current->getnext();
	}
};
//SEARCH FUNCTION
void List::search(int datainput)
{
	if (tail==NULL)
	 cout << "false" << endl;
	else
	 tail->search(datainput);
};
//LOST NODE FUNCTION
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
//LOST PRINT FUNCTION
void Node::print()
{
	cout << data << endl;
};
