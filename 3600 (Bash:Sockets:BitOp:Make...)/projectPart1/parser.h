#include "defs.h"


class parser{
	private:
		vector< pair<int,int> > trace;
		int reads, writes;
		
		
	public:
		parser(int argc, char* argv[]);
		void readTrace();
		void countReadsWrites();
		void readParameters();
		void printDebug();
		void printTrace();
};
