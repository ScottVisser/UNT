//Main engine to consolidate logic between Level1 cache and Level2 cache

#ifndef GLOBAL_H
#define GLOBAL_H
        //Global variables
        unsigned long int ADDRESS = 0;
        char MODE[6];

        unsigned int CACHE_SIZE;
        unsigned int ASSOCIATIVITY;
        unsigned int BLOCK_SIZE;
        char WRITE_POLICY[6];
        unsigned int VICTIM_SIZE;
        unsigned int INDEX;
        int argc;
        char** argv;
        long int l1_r_hit,l1_w_hit,l2_r_hit,l2_w_hit;
        long int l1_r_miss,l1_w_miss,l2_r_miss,l2_w_miss;
        long int mem_acess;
        block_t *l1_cache;
        block_t *l2_cache;

        unsigned long int TAG,SET;//stores tag and set number for current transaction






#endif
