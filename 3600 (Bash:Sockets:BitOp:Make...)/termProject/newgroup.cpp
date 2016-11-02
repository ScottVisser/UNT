#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#define MAX_ADDRESSES 1000000

using namespace std;

int main(int argc, char **argv)
{
    //Declare variables
	int szL1 = atoi(argv[2]);
	int szL2 = atoi(argv[4]); 
	string type = argv[6]; //Determines the type of cache
	//string fileN = argv[7];
    int info, i=1, j=1; //info is what is read in, i & j are testing variables
	string *rd_add = new string[MAX_ADDRESSES]; //set the max string length for what's read
    string *wrt_add = new string[MAX_ADDRESSES]; //set the max string length for what's written
	int total = 0; //total # of reads/writes
	int rds = 0; //base # of reads
	int wrt = 0; //base # of writes
	
	//check for a power of 2 for szL1
    while(1)
    {
        if(i == szL1)
            break;
        
        //Error Message
        else if(i > szL1)
        {
            cout << "Error. sizeL1 must be a power of 2. Please try again." << endl << endl;
            return 0;
        }
        
        i *= 2;
    }
    
    //cout << "size1 " << szL1 << endl;
    
	//check for a power of 2 for szL2
    while(1)
    {
        if(j == szL2)
            break;
        
        //Error 
        else if(j > szL2)
        {
            cout << "Error. sizeL2 must be a power of 2. Please try again." << endl << endl;
            return 0;
        }
        
        j *= 2;
    }
    
    //cout << "size2 " << szL2 << endl;
    
    //Check to see if szL2 is larger than szL1
    if(szL2 <= szL1)
    {
        cout << "Error. sizeL2 must be larger than sizeL1. Please try again." << endl << endl;
        return 0;
    }
	
	//Read file contents
	while( cin >> info )
    {
        //If it is a 1, increment read files
        if(info == 1)
        {
            cin >> rd_add[i++];
            rds++;
        }
        else if(info == 0)
        {
            cin >> wrt_add[j++];
            wrt++;
        }
        else
        {
        	continue;
        }
    }
	
	total = rds + wrt;
	
	//Print the arguments read
	cout << endl << "Input Parameters read:" << endl;
	cout << "SizeL1: " << szL1 << endl;
	cout << "SizeL2: " << szL2 << endl;
	cout << "Type: " << type << endl;
	
	//Print file stats
	cout << endl << "Memory References Read from File" << endl;
    cout << "Total: " << total << endl;
	cout << rds << " Reads" << endl;
	cout << wrt << " Writes" << endl;
	
	return 0;
}