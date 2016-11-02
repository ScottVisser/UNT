all:		CacheSim

CacheSim	: parser.o cache.o report.o main.o
			  g++ parser.o cache.o report.o main.o -g -o CacheSim


parser.o	: parser.cpp parser.h
			  g++ -c -g parser.cpp
			  
cache.o		: cache.cpp cache.h
			  g++ -c -g cache.cpp
			
report.o	: report.cpp report.h
			  g++ -c -g report.cpp

main.o		: main.cpp
			g++ -c -g main.cpp

clean			:
			/bin/rm CacheSim *.o 