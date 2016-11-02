#include "parser.h"

using namespace std;

parser::parser(int argc, char* argv[]){
	reads=0;
	writes=0;
	if( argc < 2)
		cout<<"No hay argumentos"<<endl;
	else
		cout<<argv[1]<<endl;
}

void parser::readTrace(){
	string address;
	int32_t test; 
	int refType;
	while (cin >> refType >> address){
		//cout << "type "<< refType << " Ref "<< address<<endl;
		stringstream ss;
		ss << hex << address;
		ss >> test;
		//cout<< "INT:" << test << endl;
		trace.push_back(make_pair(refType,test));
		//printTrace();
	}
	countReadsWrites();
}

void parser::countReadsWrites(){
	cout<<"# reads: "<< reads<<endl;
	cout<<"# writes: "<< writes<<endl;
	for(int i=0; i< trace.size(); i++){
		if(trace[i].first == 0)
			reads++;
		else
			writes++;
	}
	cout<<"Size of Trace: " << trace.size()<<endl;
	cout<<"# reads: "<< reads<<endl;
	cout<<"# writes: "<< writes<<endl;
}

void parser::readParameters(){

}

void parser::printDebug(){

}

void parser::printTrace(){
	for(int i=0; i <trace.size(); i++)
	{
		cout<<trace[i].first<<" "<<trace[i].second<<endl;
	}
}