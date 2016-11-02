#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <string>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <stdlib.h>
#include <cstdint>
#include <bitset>
#include <algorithm>
using namespace std;

// CACHE CLASS DEFINED
class cache{	
	private:
	 int l1;	//member of cache class to hold value of l1 cache level
	 int l2;	//member of cache class to hold value of l2 cache level
	 int *cache1;	// array of integers for each instant of the cache class
	 int *validBit1;	//array of pointers for each valid bit read to justify hits and misses
	 int readcount, writecount;	//primitive int variables for how many lines are read or witten during simulation part of the cache program execution
	 string type;
	 int hits, misses;		
		
	public:
	 cache();
	 void inputErrorDetect(int, char*[]); //method to detect user errors such as inputing undesirable parameters
	 void parse(int, char*[]);	//method to parse array of characters in the trace file for simulation of the cache system
	 void runSim();		//method that will kick start a chain of activities in the main method to run the cache simulation
	 void report();		//report for write policy of the cache system---
};

/////////////// CONSTRUCTOR /////////////////
cache::cache()
{
	l1 = 0; //Initializes value to 0
	l2 = 0; //Initializes value to 0
	cache1 = NULL; //sets array to NULL
	validBit1 = NULL; //sets bit to NULL
	type = "\0"; //sets type to empty string
	writecount = 0; //sets write count to 0
	readcount = 0; //sets read count to 0
	hits =0; //sets hits to 0
	misses = 0; //sets misses to 0

};

// FIRST FUNCTION CALLED.  DETECTS INPUT ERRORS     ***** 
//doesn't work! conditionals always met (error/exit).. function call commented out in main.cpp
void cache::inputErrorDetect(int argc, char *argv[])
{
	if (!strcmp(argv[1],"-sizeL1")) //|| (argv[3] != "-sizeL2") ||(argv[5] != "-type") //if the first, third and fifth argument on the terminal is not -sizeL1, -sizeL2 and -type respectively
	{
		cout << "INVALID ARGUMENT SET    please use:" << endl; 	//Then display on the terminal invalid argument
		cout << "./[executable] -sizeL1 ### -sizeL2 ### -type ### < [tracefile.trace]" << endl << argv[1] << endl << endl;  //And also diplay for user to enter the parameters in the right format
		exit(1);													 //exit after the above lines are accomplished

	}
	else if (argv[6] != "direct")  //else if the sixth argument is direct
	{
		cout << "INVALID TYPE    please use: direct" << endl << endl; //then display invalid type and suggest for user to use the valid type which includes direct for the sake of this project
		exit(1);							//Like previous if conditional statement system exit
	}
};

// SECOND FUNCTION CALLED.  PARSE FUNCTION ASSIGNS ARGUMENTS TO CACHE CLASS MEMBERS
void cache::parse(int argc, char *argv[])	//cache class method to parse the second and forth argument in the command line of the linux terminal
{	
	string size1=argv[2], size2=argv[4];	//Delcare pointers of characters in position two and four after execution of the object code of program to sizeL1 and sizeL4 respectively
	string address;				//Declare position of character arrays for address 
	l1 = atoi(size1.c_str());		//convert the string of characters stored for size1 into integers for bit manupulation
	l2 = atoi(size2.c_str());	        //Likewise convert the string stored in size2 into integers for mathematical computation
	type = argv[6];				//set position #6 after execution of object code in command line to type hence user will have to input the type of operation for this program which are direct mapping, writethrough and writeback
																										//N:B writethrough/writeback were not assigned for this project
};

// THINRD FUNCTION CALLED  READS INPUT FROM FILE AND SIMULATES CACHE BEHAVIOR
void cache::runSim() //Main method of class cache to run the simulated version of the cache system created after reading trace files
{

	uint32_t decimal, line, tag; //Declare variable unsigned integer with 32bits for decimal, line and tag to be used to simulate the cache in the main function
	int read=0; 		      //Declare regular integer read
	string address;			//Declare string of characters for address

	if ((l1 == 32000) || (l1 == 32768) || (l1 == 32)) 	//If size of l1 is 32000 or 32768 or 32, which are all powers of 2 
	{							//then do the following
		uint32_t abits = 15;				//first declare and initialize a local variable within the clause of the above condition with type unsigened integer with 32 bits with no padding bits for efficiency
		cache1 = new int [1024];			// initialize cache1 to an array of 1024 caches with type integer to store addresses and cache information 
		validBit1 = new int [1024];			// intiialize and declare an array of integer with size 1024 for the valid bits
		int j;
	
		for (j=0; j<1024; j++)				//for each count from 0 to 1024
		{						//do the following
			validBit1[j] = 0;			//set the value of each valid bit to 0
			cache1[j] = -1;				//Then set the value of each cache for each count from 0 to 1024 to -1
		}
		 
		while (cin>>read)				//while reading the file into standard input
		{
			cin >> address;				//get the address into standard input
			std::stringstream ss;			//declare string object ss whose values will be copied
			ss << hex << address;			// each address retrieved from the file will be converted into hex format then stored in the ss string object
			ss >> decimal;				//Then the value stored in the string object will be transferred into the decimal format
			tag = decimal>>abits;			//unstgned integer variable tag will hold the value of the address bits 
			line = decimal<<(32-abits);		//the address bits are then converted to decimal and stored in the unsigned integer of size 32 bits called line
			line = line>>((32-abits)+5);		//line then sends its value with an offset of 5 to address bits.

			if (read == 1)				//check if standard input is reading from the file and the first character is a 1
			{
				readcount++;			//as long as we're reading from the file count the number of times with ie post increment 
				if (cache1[line] != tag)	//as long as the line is not reading the tag
				{	
					misses++;		//count the number of misses by post increment
					cache1[line] = tag;     //assign that line as the tag of the cache
				}
				else
				 hits++;			//else if the above isn't true count it as a hit again post increment for variable int hit
			}
			else // write
			{
				writecount++;			//else if the value is other than 1 for the first character 
				if (cache1[line] != tag)	//check to make sure line is not the tab bits
				{
					misses++;		//in that case count it also as a miss
					cache1[line] = tag;	//assign the tag to cache for that line position
					validBit1[line] = 1;	//
				}
				else
				 hits++;			//or else count it as a hit
			}							
		}
	}

	else if ((l1 == 16000) || (l1 == 16384) || (l1 == 16))
	{
		cache1 = new int [512];			//first declare and initialize a local variable within the clause of the above condition with type unsigened integer with 32 bits with no padding bits for efficiency	 
		validBit1 = new int [512];		// initialize cache1 to an array of 1024 caches with type integer to store addresses and cache information 
		uint32_t abits = 14;			// intiialize and declare an array of integer with size 1024 for the valid bits
		int j,i=0;

		for (j=0; j<512; j++)			//for each count from 0 to 512
		{
			validBit1[j] = 0;		//set the value of each valid bit to 0
			cache1[j] = -1;			//set the value of each valid bit to 0
		}

		while (cin>>read)			//while reading the file into standard input
		{
			cin >> address;			//get the address into standard input
			std::stringstream ss;		//declare string object ss whose values will be copied
			ss << hex << address;		// each address retrieved from the file will be converted into hex format then stored in the ss string object
			ss >> decimal;			//Then the value stored in the string object will be transferred into the decimal format
			tag = decimal>>abits;		//unstgned integer variable tag will hold the value of the address bits 
			line = decimal<<(32-abits);	//the address bits are then converted to decimal and stored in the unsigned integer of size 32 bits called line
			line = line>>((32-abits)+5);	//line then sends its value with an offset of 5 to address bits.
	
			if (read == 1)			//check if standard input is reading from the file and the first character is a 1
			{
				readcount++;		//as long as we're reading from the file count the number of times with ie post increment
				if (cache1[line] != tag)
				{
					cache1[line] = tag;	//as long as the line is not reading the tag
					misses++;		//count the number of misses by post increment
				}
				else
				 hits++;			//or else count it as a hit
			}
			else // write
			{
				writecount++;			//else if the value is other than 1 for the first character 
				if (cache1[line] != tag)		//check to make sure line is not the tab bits
				{
					misses++;		//in that case count it also as a miss
					cache1[line] = tag;	//assign the tag to cache for that line position
					validBit1[line] = 1;
				}
				else
				 hits++;		//or else count it as a hit
			}							
		}
	}

	else if ((l1 == 64000) || (l1 == 64) || (l1 == 65536)) 
	{
		uint32_t abits = 16;			// intiialize and declare an array of integer with size 1024 for the valid bits
		cache1 = new int [2048];	//first declare and initialize a local variable within the clause of the above condition with type unsigened integer with 32 bits with no padding bits for efficiency	 
		validBit1 = new int [2048];		// initialize cache1 to an array of 1024 caches with type integer to store addresses and cache information 
		int j;

		for (j=0; j<2048; j++)			//for each count from 0 to 2048
		{
			cache1[j] = -1;			//Then set the value of each cache for each count from 0 to 1024 to -1
			validBit1[j] = 0;		//set the value of each valid bit to 0
		}		
 
		while (cin>>read)			
		{
			cin >> address;				//get the address into standard input
			std::stringstream ss;			//declare string object ss whose values will be copied
			ss << hex << address;			// each address retrieved from the file will be converted into hex format then stored in the ss string object
			ss >> decimal;				//Then the value stored in the string object will be transferred into the decimal format
			tag = decimal>>abits;			//unstgned integer variable tag will hold the value of the address bits 
			line = decimal<<(32-abits);			//the address bits are then converted to decimal and stored in the unsigned integer of size 32 bits called line
			line = line>>((32-abits)+5);			//line then sends its value with an offset of 5 to address bits.

			if (read == 1)			//check if standard input is reading from the file and the first character is a 1
			{
				readcount++;			//as long as we're reading from the file count the number of times with ie post increment
				if (cache1[line] != tag)
				{
					misses++;		//count the number of misses by post increment
					cache1[line] = tag;	//as long as the line is not reading the tag
				}
				else
				 hits++;			//or else count it as a hit
			}
			else // write
			{
				writecount++;			//else if the value is other than 1 for the first character 
				if (cache1[line] != tag)		//check to make sure line is not the tab bits
				{
					misses++;		//in that case count it also as a miss
					cache1[line] = tag;	//assign the tag to cache for that line position
					validBit1[line] = 1;
				}
				else
				 hits++;		//or else count it as a hit
			}			
		}
	}
	
	else
	{
		cout << "INVALID SIZE ENTRY (-sizeL1)    re-execute with valid size" << endl; //else tell user its an invalid entry
		cout << "valid size entrys:" << endl;	//display the following below to user as valid entries for suggestions
		cout << "64 64000 65536" << endl;
		cout << "32 32000 32768" << endl;
		cout << "16 16000 16384" << endl << endl;
		exit(1);		//exit out of program gracefully without segmentation fault
	}

};

// LAST FUNCTION CALLED BY MAIN  REPORT
void cache::report()
{
	int total = readcount+writecount; //Method will have a member that will total the number of read and write from and to cache. basically every cache that is in the trace file used for processing this simulation
	int percentHits = (hits*100)/total;	//Method will also have a member to display the percentage of hits, percentage of misses is simply 100% - (percentage of hits)

	cout << endl << "Input Parameters read:" << endl; //Display the imput parameters which are -sizeL1 <sizeofL1> -sizeL2 <sizeofL2> type direct <filename.trace>
	cout << "\tSizeL1 " << l1 << endl;		//display the value of l1 as inputed by user during before execution remember l1 = size of l1 cache level  sizel1 < sizel2, some newer systems have the same size but in this simulation l2 > l1
	cout << "\tSizeL2 " << l2 << endl;		//display the value of l2
	cout << "\tType " << type << endl << endl;	//display the type of operation, in which in this project its direct mapping 
	
	cout << "Memory reference from read from file:" << endl;	//Read the memory addresses 
	cout << "\t" << total << " Total" << endl;			//Display the total number of memory address read from trace file, idealy that is the number of lines on the trace file
	cout << "\t" << readcount << " Reads" << endl;			//display the count for how many where read
	cout << "\t" << writecount << " Write" << endl << endl;			//display the count for how many were written

	cout << "Simulation Execution" << endl;
	cout << hits << "   " << misses << endl;		//display the number of hits and misses
	cout << "\t" << percentHits << "\% hits" << endl;			//display the percentage of hits and misses
	cout << "\t" << 100 - percentHits << "\% misses" << endl << endl;
};


// 	Test output for values in binary...
//	cout << "address: " << address << "  decimal: " << decimal << endl;
//	cout << (bitset<32>) decimal << "   ";
//	cout << "tag: " << (bitset<17>) tag << "  " << "line: " << (bitset<10>) line << endl;

