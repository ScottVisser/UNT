#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <deque>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>
#include <iomanip>
#include <list>
#include <stdlib.h>
//#include <cstdint>
//#include <bitset>
//#include <math.h>
#include "cachemanager.cpp"
#include "cachemanager.h"
#include "block_t.h"

using namespace std;
int main(int argc, char *argv[]){


cachemanager ourcache;

ourcache.cache_transaction(argc, argv);
return 0;
}//End of the main functoin
