#include <iostream>
#include <sstream>
#include <bitset>
#include <cstdint>
using namespace std;


int main(int argc, char* argv[]){
	uint32_t decimal, decimal15, decimal10;
	
	uint32_t abits = 32-atoi(argv[2]);
	
	cout<<"Size of the tag:\t"<<argv[2] << endl;
	
	cout<<"The value inserted in hexa:\t"<<argv[1]<<endl;
	std::stringstream ss;
	
	//ss << hex << "10013c68";
	ss << hex <<argv[1];
	ss >> decimal;
	cout<< "The value inserted in bynary:\t"<< (bitset<32>) decimal << endl;
	cout<<"The value inserted in decimal:\t"<< decimal<<endl;
	
	cout<<"----------------------------"<<endl;
	
	decimal15 = decimal>>15;
	cout<< "Tag value in binary:\t"<< (bitset<17>) decimal15 << endl;
	cout<<"Tag value in decimal:\t"<< decimal15<<endl;

	cout<<"----------------------------"<<endl;
	decimal10= decimal<<(32-abits);
	decimal10= decimal10>>((32-abits)+5); 
	cout<< "Block id in bynary:\t"<< (bitset<10>) decimal10 << endl;
	cout<<"Block id in decimal:\t"<< decimal10<<endl;
	
	
	
}