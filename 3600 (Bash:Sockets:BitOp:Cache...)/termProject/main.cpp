// Author: Scott Visser
//	: Clement Cole
#include "cache.h"

int main(int argc, char *argv[])
{
	// still needs: use argc to make sure the input is in the correct format
	// compile with:
	// g++ main.cpp -stdc++0x
	// execute with:
	// ./a.out -sizeL1 ### -sizeL2 ### -type direct (...)
	// argv[0]   [1]   [2]  [3]    [4]  [5]   [6]  (< file input)

	cache simu;
//	simu.inputErrorDetect(argc, argv);
	simu.parse(argc, argv);
	simu.runSim();
	simu.report();
	return 0;
}
