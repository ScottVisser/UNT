#include "cache.h"
#include "parser.h"

int main(int argc, char* argv[]){
	parser p(argc, argv);
	p.readTrace();
	//cache simu;
	//simu.runSim();
	return 0;
}