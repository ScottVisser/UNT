/*
Scott Visser
Csce2100
Hw2
Linked list implementation
main file
*/
//INCLUDE HEADER FILES
#include "hw2.h"
#include "hw2list.h"
#include "hw2node.h"
//NAMESPACE
using namespace std;
//START OF MAIN
int main(void)
{
	class List list; // INITIALIZE LIST

	string option;
	int datainput;

	//PRINT MENU	
	cout << "Commands:" << endl;
	cout << "addleft x" << endl;
	cout << "addright x" << endl;
	cout << "right" << endl;
	cout << "left" << endl;
	cout << "search" << endl;
	cout << "print" << endl;
	cout << "quit" << endl << endl;
	//LOOP THAT ACCEPTS INPUT FOR LIST OPPERATIONS
	while(1)
	{
		cout << "list> ";
		cin >> option;

		if (option=="addleft")
		{
			cin >> datainput;
			list.addleft(datainput);
		}
		else if (option=="addright")
		{
			cin >> datainput;
			list.addright(datainput);
		}
		else if (option == "right")
		 list.right();
		else if (option == "left")
		 list.left();
		else if (option == "search")
		{
			cin >> datainput;
			list.search(datainput);
		}
		else if (option=="print")
		 list.printall();	
		else if (option=="quit")
		{
			cout << "Goodbye" << endl;
		 	break;	
		}
		else 
		 cout << "invalid input" << endl;

	}
		
return 0;
} // END OF MAIN
