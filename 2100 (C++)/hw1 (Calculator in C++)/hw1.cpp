/*
Author: Scott Visser
Cse2100 HW1
Due: 9/29/2014

This program, is designed to take in two numbers and perform a task such
as adding or subtracting.  I adjusted my code to use the isaslpha() function 
to make sure all inputs consist of numbers.  They are accepted as strings then 
converted to doubles.  I made the inputs members of a class with each 
functions also members of that class used to manipulate the variables.
I used typedef and I added a subtract function.

*/

// include libraries & namespace std;
#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

//class with private data (2 variables)
//and public functions to manipulate/print the two inputs
class newclass
{
	private:
 	 double *d;
	 double *e;
	 string dd;
	 string ee;
	public:
	 newclass();
	 void getinput();
	 void add();
	 void subtract();
	 void multiply();
};

//constructor: allocates memory and assigns arbitrary values
newclass::newclass()
{
	d = new double;
	*d = 47.3;
	e = new double;
	*e = 22.2;
};

//recieves user input
void newclass::getinput()
{
	
	int i = 0, j =0;
        bool x = false , y = false;
	
	while(x == false)
	{
                i=0;        
		cout << "Type a number: ";
		cin >> dd;
	   
		while(dd[i]!='\0')
		{ 
	   	     	if(isalpha(dd[i]))
			{
				x = false;
              			cout << "must use numbers"<< endl;
              			break;
             		}
	     		
	     		else
 	     			x = true;
             
		i++;
       		}
      	}
      *d=strtod(dd.c_str(),NULL);
      
	
	while(y == false)
	{
		j=0;
		cout << "Type another number: ";
		cin >> ee;

		while(ee[j]!='\0')
        	{
             		if(isalpha(ee[j]))
             		{
              			y = false;
              			cout << "must use numbers"<< endl;
              			break;
             		}
             		else
            			y = true;
         	j++;
		}
    	}
      	*e=strtod(ee.c_str(),NULL);

      

};

//function that adds and prints the two numbers
void newclass::add()
{
	cout << endl << *d << " + " << *e << " = " << *d + *e;
	cout << endl << endl;
};

//function that subtracts and prints the two numbers
void newclass::subtract()
{
	cout << endl << *d << " - " << *e << " = " << *d - *e;
	cout << endl << endl;
};

//function that multiplys and prints the two numbers
void newclass::multiply()
{
	cout << endl << *d << " * " << *e << " = " << *d * *e;
	cout << endl << endl;
};

//main function
int main(void)
{

	//pointless use of typedef
	typedef newclass class1;
	//new object "c" of class type "newclass"
	class1 c;	
	
	//retrive user input for *d and *e
	c.getinput();

	// declares new string and sets it to "0"
	string option = "0";

	// once input is recieved,  enter menu loop to add subtract or multiply
	while (option != "E")
	{
		cout << endl << "Would you like to (A) Add, (M) Multiply, (S) Subtract, (I) input new numbers, or(E) Exit program?: ";
		cin >> option;

		if (option == "A")
		{
			c.add();
		}

		else if (option == "M")
		{
			c.multiply();
		}
		
		else if (option == "S")
		{
			c.subtract();
		}
		
		else if (option == "E")
		{
			cout << endl;
		}
		
		else if (option == "I")
		{
			c.getinput();
		}

		else
		{
			cout << endl << "invalid entry" << endl;
		}
	}

return 0;
}
