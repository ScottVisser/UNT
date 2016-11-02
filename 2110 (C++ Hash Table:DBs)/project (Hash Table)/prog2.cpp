/*
Scott Visser
csce2110 Program 2
main function/loop
*/

//header files
#include "prog2.h"
#include "set.h"
#include "node.h"
// namespace
using namespace std;

//main function
int main(void)
{
	class Set myset; // initialize hash table
	string option; // user input option
	int datainput; // user input data

	// menu loop
	while(1)
	{
		cout << "set> "; // get user input
		cin >> option; 

		if (option == "add")
		{
			cin >> datainput; // get user input data
			//check here to make sure data input is an integer
			myset.add(datainput); //add function
		}
		else if (option == "show")
		{
			myset.show(); // show function displays hash table
		}
		else if (option == "delete")
		{
			cin >> datainput;
			//check here to make sure data input is an int
			myset.remove(datainput); // remove datainput from table
		}	
		else if (option == "search")
		{	
			cin >> datainput;
			myset.search(datainput); // search for data input
		}	
		else if (option == "quit")
		{		
			break; //break out of program
		}
		else  //output for illigal input
		{
			cout << "INVALID COMMAND" << endl;
		}
	}

return 0;
}
