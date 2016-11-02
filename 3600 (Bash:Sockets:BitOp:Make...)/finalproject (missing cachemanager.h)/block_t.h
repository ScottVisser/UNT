//Main engine to consolidate logic between Level1 cache and Level2 cache
#pragma once
#ifndef BLOCK_T_H
#define BLOCK_T_H

//Structure for block of cache
typedef struct{
                        unsigned long int tag;
                        unsigned long int value;
                        unsigned long int age; //Use for implementation of LRU(least recently used)
                        bool valid;
                        bool dirty;


}block_t;
#endif
