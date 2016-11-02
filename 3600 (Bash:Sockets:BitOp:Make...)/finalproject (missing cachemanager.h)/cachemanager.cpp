#include "cachemanager.h"

using namespace std;
//INITIALIZING ALL THE VALUES JUST TO BE SAFE
cachemanager::cachemanager(){};


void cachemanager::inputErrorDetect(int argc, char *argv[]){
        if(!strcmp(argv[1], "-sizeL1") || strcmp(argv[3], "-sizeL2")  || strcmp(argv[5], "-type") || strcmp(argv[7], "WRITE_POLICY"))//
        {
                cout << "INVALID ARGUMENT SET    please use:" << endl;  //Then display on the terminal invalid argument
                cout << "./[executable] -sizeL1 ### -sizeL2 ### -type ### < [tracefile.trace]" << endl << argv[1] << endl << endl;  //And also diplay for user to enter the parameters in the right format
                print_write_policy();
                exit(1);
        }

        else{
                        cout<<"\nEnter size of L1"<<endl;
                        cin>>l1;
                        cout<<"\nEnter size of L2"<<endl;
                        cin>>l2;
                        cout<<"Cache simulation will implement the full associativity\n";
                exit(1);
        }
        return; //Done;
};

void cachemanager::print_write_policy(){

 cout<<"USAGER:\n"<<endl;
 cout<<"./a.out -sizeL1 ### -sizeL2 ### -type ('direct' or 'fa') -write_policy ('wb' or 'wt')"<<endl;


};





//****Function to interpret the trace file
// containing address in hex format (0x12345678 or 0X12345678)
//------------------------------------------------------------//                
void cachemanager::get_values(char temp[]){

                                        char *store;
                                        char *p;

                                        store=strtok(temp,"  \n");
                                        do
                                        {  if(*store>60)
                                                {
                                                strcpy(MODE,store);
                                                //printf("--%s \t",MODE);
                                                }
                                                else if(strncmp(store,"0x",2)==0 || strncmp(store,"0X",2)==0)
                                                {
                                                ADDRESS=strtol(store,&p,16);
                                                //printf("%x -%ld\n",ADDRESS, ADDRESS);
                                                }


                                }
                                while(store=strtok(NULL,"  \n"));

                                return;



}; //END OF GET VALUES

                ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                //Function name is settings_file, we can read from a setting file in the same directory instead of executing the program in the command line     //
                //The settings file just has configuration for our cache simulations                                                                                                                                                     //
                //Hence we have                                                                                                                                                                                                                                                                  //
            //          SIZE OF CACHE in the first line                                                                                                                                                                                                                  //
                //              ASSOCITIVITY CODE WHICH IS 1 for DIRECT MAPPING AND 0 FOR FULL ASSOCITIVITY
                //              BLOCK_SIZE IN in bytes
                //              WRITE_POLICY (WB for write_back and wt for write_through)
                //      FINALLY THE L2 SIZE IN BLOCKS
                /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*void cachemanager::settings_file(int check, char temp[]){
                                if (check==3)
                {
                char t[20];
                char *store;
                int line =0;

                cout<<"Config file name is "<<temp<<endl;
                FILE *cp;
                                cp=fopen(temp,"r");
                                if(cp==NULL)
                                        {cout<<"error"<<endl;return;}
                //Reading from file
                while(!feof(cp))
                {
                        fgets(t,20,cp);
                        if(!strncmp(t,"\n",5))
                        {continue;}
                        store=strtok(t,"\n");

                        switch(line)
                        {
                        case 0:
                                CACHE_SIZE=atoi(store);
                                cout<<"\nCACHE_SIZE"<<CACHE_SIZE<<endl;
                                break;
                        case 1:
                                ASSOCIATIVITY=atoi(store);
                                cout<<"\nASSOCIATIVITY "<<ASSOCIATIVITY<<endl;
                                break;
                        case 2:
                                BLOCK_SIZE=atoi(store);
                                cout<<"\nBLOCK_SIZE :"<<BLOCK_SIZE<<endl;
                                break;
                        case 3:
                                strcpy(WRITE_POLICY,store);
                                cout<<"\nWRITE_POLICY :"<<WRITE_POLICY<<endl;
                                break;
                        case 4:
                                VICTIM_SIZE=atoi(store);
                                cout<<"\nVICTIM_SIZE :"<<L2_SIZE<<endl;
                                break;
                        default:
                                cout<<"\n--CONFIG file error---\n"<<endl;
                                break;
                        }//switch ends

                line++;
                }//while ends

        fclose(cp);
        }//if(config file included) ---ends

        else{
                        printf("No, Config file included so enter configurations\n");

                        cout<<"\nEnter L1_SIZE (in Bytes):\t";
                        cin>>CACHE_SIZE;
                        cout<<"\nEnter ASSOCIATIVITY \n(0 for fully associative 1 for direct mapped else any integer value ):\t";
                        getline(cin ,ASSOCIATIVITY);
                        cout<<"\nEnter BLOCK_SIZE       (in Bytes):\t";
                        cin>>BLOCK_SIZE;
                        cout<<"\nEnter WRITE_POLICY \n(WB for write-back or WT for write-through):\t";
                        getline(cin,WRITE_POLICY);
                        cout<<"\nEnter L2_SIZE (in BLOCKS):\t";
                        getline(cin,VICTIM_SIZE);

        }//end of else
};*/


//-------------------------------------------------------------------------------------
//function name: Create_cache()
//creates cache for the given requirements in terms of no of blocks
//-------------------------------------------------------------------------------------
void cachemanager::get_write_policy(string argument){

}; //working on this






//-------------------------------------------------------------------------------------
//function name: Create_cache()
//creates cache for the given requirements in terms of no of blocks
//-------------------------------------------------------------------------------------

block_t * cachemanager::create_cache(block_t *dummy, int size){
                //cout<<size<<" Blocks(each "<<BLOCK_SIZE<<" byes)\n"<<endl; just for testing and version control
                dummy=(block_t *)malloc(size*sizeof(block_t));

                return dummy;


}; //End of create_cache()







                  //-------------------------------------------------------------------------------------
//function name: produce()
//
//Uses the ADDRESS provided for current transaction and produces tag & set numbers
//-------------------------------------------------------------------------------------
void cachemanager::produce(){
                        int w=sizeof(ADDRESS)*8;
                        int x=log2(CACHE_SIZE);
                        int y=log2(BLOCK_SIZE);
                        int z=log2(ASSOCIATIVITY);

                        SET= ADDRESS<<(w-(y+z));                // (0x12345678 minus TAG) at MSB

                        if(ASSOCIATIVITY==1)
                        
                                {SET=SET>>(w-z-1);SET=SET>>1;}
                        else
                                {SET= SET>>(w-z);}                              //set number bits only
                        TAG= ADDRESS>>(y+z);

                        printf("Adress: %lx -Tag: %lx -Set: %lx\n",ADDRESS,TAG,SET);

                return;

                }; //End of create_cache()






//function name: search()
//
//To search for particular tag value in a cache
//arguments type: 0 for L1 cache search, 1 for victim search

//returns: -1 not found else returns offset from the starting of the set
//-------------------------------------------------------------------------------------         
int cachemanager::search(int type){
        int i=0;

        if(type == 0)           //to search inside L1 cache
        {
                for(i=0;i<INDEX;i++)
                {
                        if( (l1_cache+(SET*INDEX)+i)->tag == TAG && (l1_cache+(SET*INDEX)+i)->valid == 1 )
                                {return i;}
                        else
                                {continue;}
                }//for end
        }//if ends

        else                            //to search inside victim cache
        {
                        for(i=0;i< (L2_SIZE) ;i++)
                        {
                                if( (l2_cache +i)->tag == TAG && (l2_cache +i)->valid ==1 )
                                                {return i;}
                                else
                                                {continue;}
                        }//for end
        }//else ends   
        return -1;

}; //



//-------------------------------------------------------------------------------------
//function name: lru()
//
//In a given instance it finds the least used block in a set

//returns offset from the beginning of the set
//returns -1 if fails to find
//-------------------------------------------------------------------------------------

int cachemanager::lru(int type){
                                int i=0;
        int k=0;
    unsigned long int j = 0;
                if(type == 0)           //to search inside L1 cache
                {
                        for(i=0;i<INDEX;i++)
                        {
                                if( ((l1_cache+(SET*INDEX)+i)->age) >= j && (l1_cache+(SET*INDEX)+i)->valid == 1 )
                                        {
                                        j = (l1_cache+(SET*INDEX)+i)->age;//update new higher age
                                        k = i;                                                  //Note down the offset
                                        }
                                else
                                        {continue;}
                        }//for end

                        return k;
                }//if ends

                else                            //to search inside victim cache
                {
                                for(i=0;i< (L2_SIZE) ;i++)
                                {
                                        if( (l2_cache +i)->age >= j && (l2_cache +i)->valid ==1 )
                                                        {
                                                        j = (l2_cache +i)->age ;                //update new higher age
                                                        k = i;                                          //Note down the offset
                                                        }
                                        else
                                                        {continue;}
                                }//for end
                return k;
         }//else ends

                        return -1;
};




                //function name: update_age()
                //
                //Updates the age of all VALID blocks of L1 & victim cache              
void cachemanager::update_age(){
                        int i=0;

                        for(i=0; i < (CACHE_SIZE/BLOCK_SIZE) ;i++)              //updating age for all valid l1 cache blocks
                        {
                                if( (l1_cache+i)->valid == 1)
                                        {((l1_cache+i)->age) = ((l1_cache+i)->age)+1;}
                                else
                                        {continue;}

                        }

                        for(i=0; i < (L2_SIZE) ;i++)            //updating age for all valid Victim cache blocks
                                {
                        if( (l2_cache+i)->valid == 1)
                                {((l2_cache+i)->age) = ((l2_cache+i)->age)+1;}
                        else
                                {continue;}

                        }

                        return;

}; //End of update_age() function


//function name: search_empty()
//
//To search for empty blocks in a cache
//arguments type: 0 for L1 cache search, 1 for L2 search

//returns: -1 not found any empty blocks else returns offset from the starting of the set
//-------------------------------------------------------------------------------------
int cachemanager::search_empty(int type){
int cachemanager::search_empty(int type){
                        int i=0;

                if(type == 0)           //to search inside L1 cache
                {
                        for(i=0;i<INDEX;i++)
                        {
                                if( (l1_cache+(SET*INDEX)+i)->valid == 0 )
                                        {return i;}
                                else
                                        {continue;}
                                }//for end
                        }//if ends

                                else                            //to search inside L2 cache
                        {
                                for(i=0;i< (L2_SIZE) ;i++)
                                {
                                        if( (l2_cache +i)->valid == 0 )
                                                        {return i;}
                                        else
                                                        {continue;}
                                        }//for end
                                }//else ends


                        return -1;

                }; //end search_empty()


                //function name: swap()
                //
                //swaps block between l1 cache & victim cache
                //argument 1: offset number of block in a set of l1 cache
                //argument 2: offset number of block in victim cache
                //-------------------------------------------------------------------------------------

void cachemanager::swap(int i, int j){
                                unsigned long int k;
                                bool v;

                                //checking for dirty bit to be set and write policy to be write-back
                                if( (l1_cache+((SET*INDEX)+i))->dirty==1 && ((strncmp(WRITE_POLICY,"WB",2)==0) || (strncmp(WRITE_POLICY,"wb",2)==0)) )
                                {
                                        //Function to write in to memory   
                                                write_memory(i);
                                }

                                //swap tag
                                        k       =       (l2_cache+j)->tag;
                                        (l1_cache+j)->tag = (l1_cache+((SET*INDEX)+i))->tag;
                                        (l1_cache+((SET*INDEX)+i))->tag = k;

                                        //swap age
                                        k       =       (l2_cache+j)->age;
                                        (l2_cache+j)->age = (l1_cache+((SET*INDEX)+i))->age;
                                        (l1_cache+((SET*INDEX)+i))->age = k;

                                        //swap validity
                                        v       =       (l2_cache+j)->valid;
                                        (l2_cache+j)->valid = (l1_cache+((SET*INDEX)+i))->valid;
                                        (l1_cache+((SET*INDEX)+i))->valid = v;


                                return;
                };//End of swap function




                //write_memory 
void cachemanager::write_memory(int i){
                        //
                        //write to memory
                        //
                                mem_acess++;

                                if( (l1_cache+((SET*INDEX)+i))->dirty==1 && ((strncmp(WRITE_POLICY,"WB",2)==0) || (strncmp(WRITE_POLICY,"wb",2)==0)) )
                                {
                                (l1_cache+( (SET*INDEX)+i ) )->dirty = 0;
                                }
                                return;

};//End of write_memory




                //Init_block will put values into the dynamically created array of of structs to store the 
void cachemanager::init_block(int i){


                                mem_acess++;

                                (l1_cache+( (SET*INDEX)+i ) ) ->tag     = TAG;
                                (l1_cache+( (SET*INDEX)+i ) ) ->valid   = 1;
                                (l1_cache+( (SET*INDEX)+i ) ) ->age     = 0;

                                if(  ((strncmp(WRITE_POLICY,"WB",2)==0) || (strncmp(WRITE_POLICY,"wb",2)==0)) )
                                {
                                if(strncmp(MODE,"l",1)==0 || strncmp(MODE,"L",1)==0 || strncmp(MODE,"r",1)==0 || strncmp(MODE,"R",1)==0)
                                { (l1_cache+( (SET*INDEX)+i ) ) ->dirty         = 0; }
                                else
                                { (l1_cache+( (SET*INDEX)+i ) ) ->dirty         = 1; }
                        }

                        return;

}; //End of member function.


void cachemanager::cache_transaction(int i, char** argv){
                        char temp[40];
                        int line=0;
                        int r=0;
                        l1_r_hit=0;
                        l1_w_hit=0;
                        l2_r_hit=0;
                        l2_w_hit=0;

                        l1_r_miss=0;
                        l1_w_miss=0;
                        l2_r_miss=0;
                        l2_w_miss=0;

                        mem_acess=0;
                        printf("Input file name is %s\n",argv[1]);

        //              get_config(argc,argv[2]);  //Getting config to create cache

                        if((argv[6] == "fa") || (argv[8] == "FA") )     //If fully associative then, ASSOCIATIVITY = total blocks in cache
                                        {ASSOCIATIVITY = CACHE_SIZE / BLOCK_SIZE;
                                        }
                                        INDEX=CACHE_SIZE/(BLOCK_SIZE*ASSOCIATIVITY); //calculates no.of blocks in a set

        //Creating L1 & victim cache
        printf(" L1 Cache of size: ");
        l1_cache = create_cache(l1_cache,L1_SIZE/BLOCK_SIZE);
        printf(" L2 Cache of size: ");
        l2_cache = create_cache(l2_cache,L2_SIZE*BLOCK_SIZE);


        //Reading from file
 if ( l1 < l2) {

                        while(cin>>r){
                                line++;
                                cin>>temp;
                                if(!strncmp(temp, "\n", 1)) //Figuring out what the first character is
                                {
                                                        continue;
                                }
                                get_values(temp); //This will get the address on that line
                                produce();              //The produce will form the TAG and SET number for the current line been processed

                                if(strncmp(MODE, "1", 1) == 0 )
                                        { read(); }
                                else if(strncmp(MODE, "0", 1) == 0){
                                        write();
                                }
                                else{
                                                cout<<"Invalid mode of operation at line"<< line<<endl;
                                }



                //Printing Statistics
                //ofstream outputdata;
                //outputdata.open("outputfile.txt");
                cout<<"L1 read hit :  "<<l1_r_hit<<endl;
                cout<<"L1 read miss : "<<l1_r_miss<<endl;
                cout<<"L2 read hit  : "<<l2_r_hit<<endl;
                cout<<"L2 read miss : "<<l2_r_miss<<endl;

                cout<<"L1 write hit : "<<l1_w_hit<<endl;
                cout<<"L1 write miss : "<<l1_w_miss<<endl;
                cout<<"L2 write hit : "<<l2_w_hit<<endl;
                cout<<"L2 write miss : "<<l2_w_miss<<endl;

                cout<<"Total memory access : "<<mem_acess<<endl;


                cout<<"L1_SIZE"<<"\t="<<L1_SIZE<<endl;
                cout<<"ASSOCIATIVITY"<<"\t="<<argv[6]<<endl;
                cout<<"BLOCK_SIZE"<<"\t="<<BLOCK_SIZE;
                cout<<"WRITE POLICY"<<"\t"<<WRITE_POLICY;
                cout<<"L2_SIZE"<<"\t="<<L2_SIZE<<endl;

                        //Creating an output file
                //outputdata.close();




                }//end of while loop
        }
};



//read function most important
void cachemanager::read()
{
  int i = search(0);            //searching for the block in L1

        //CODE FOR L1 CACHE HIT----------------------------------
        if(i != -1)                     //block found in L1
        {
                l1_r_hit++;             //L1 read hit update
                (l1_cache+( (SET*INDEX)+i ) ) ->age     = 0;
        }

  //CODE FOR L1 CACHE MISS------------------------------------
        else                            //block NOT found in L1
        {
                l1_r_miss++;            //L1 read miss update

        //CODE IF VICTIM CACHE EXISTS----------->>>>>>>>>>>
                if(L2_SIZE != 0)                //victim cache exists
                {
                        int j = search(1);      //searching for the block in victim cache

                //CODE FOR VICTIM CACHE HIT------------------------------------
                                if(j != -1)             //block found in victim cache
                                {
                                        l2_r_hit++;                                     //Victim read hit update
                                        int k = search_empty(0);        //searching for empty block in L1

                                                if(k != -1)             //empty block in L1 found
                                                {
                                                        swap(k,j);
                                                        (l1_cache+( (SET*INDEX)+ k ) ) ->age    = 0;
                                                }
                                                else                    //NO empty block in L1
                                                {
                                                        k=0;
                                                        k= lru(0);      //searching for LRU block in L1
                                                                swap(k,j);
                                                        (l1_cache+( (SET*INDEX)+ k ) ) ->age    = 0;
                                                }

                                }
                                                                                                               

   //CODE FOR VICTIM CACHE MISS------------------------------------
                                else
                                {
                                        l2_r_miss++;                                    //Victim read miss update
                                        int k = search_empty(0);        //searching for empty block in L1
                                                if(k != -1)             //empty block in L1 found
                                                {
                                                        init_block(k);  //update the L1 cache block with new values
                                                }
                                                else                    //NO empty block in L1
                                                {
                                                        k=0;
                                                        k= lru(0);                              //searching for LRU block in L1
                                                        int m =search_empty(1); //searching for empty block in Victim
                                                                if(m != -1)             //empty block in Victim cache found
                                                                {
                                                                        swap(k,m);
                                                                        init_block(k);
                                                                }
                                                                else                    //NO empty block in Victim cache
                                                                {
                                                                        m = 0;
                                                                        m = lru(1);             //searching for LRU block in victim
                                                                        swap(k,m);
                                                                        init_block(k);  //update the L1 cache block with new values
                                                                }
                                                }
                                }
                }

        //CODE IF VICTIM CACHE DOES NOT EXIST----------->>>>>>>>>>>
                else                            //VICTIM_SIZE = 0
                {
                        int k = search_empty(0);        //searching for empty block in L1
                                if(k != -1)             //empty block in L1 found
                                {
                                        init_block(k);  //update the L1 cache block with new values
                                }
                                else                    //NO empty block in L1
                                {
                                        k=0;
                                        k=lru(0);               //searching for LRU block in L1
                                        init_block(k);  //update the L1 cache block with new values
                                }
                }


        }

return;
};
//read() ends--








void cachemanager::write(){
        if(  ((strncmp(WRITE_POLICY,"WB",2)==0) || (strncmp(WRITE_POLICY,"wb",2)==0)) )
        {
                int i = search(0);//searching for the block in L1

                //CODE FOR L1 CACHE HIT----------------------------------
                if(i != -1)                     //block found in L1
                {
                        l1_w_hit++;             //L1 write hit update
                        (l1_cache+( (SET*INDEX)+i ) ) ->age     = 0;
                        (l1_cache+( (SET*INDEX)+i ) ) ->dirty   = 1;
                }

                //CODE FOR L1 CACHE MISS------------------------------------
                        else                            //block NOT found in
                        {
                                l1_w_miss++;            //L1 write miss update

                        //CODE IF VICTIM CACHE EXISTS----------->>>>>>>>>>>
                                if(L2_SIZE != 0)                //victim cache exists
                                {
                                        int j = search(1);      //searching for the block in victim cache

                                //CODE FOR VICTIM CACHE HIT------------------------------------
                                                if(j != -1)             //block found in victim cache
                                                {
                                                        l2_w_hit++;                                     //Victim write hit update
                                                        int k = search_empty(0);        //searching for empty block in L1

                                                                if(k != -1)             //empty block in L1 found
                                                                {
                                                                        swap(k,j);
                                                                        (l1_cache+( (SET*INDEX)+ k ) ) ->age    = 0;
                                                                        (l1_cache+( (SET*INDEX)+ k ) ) ->dirty  = 1;
                                                                }
                                                                else                    //NO empty block in L1
                                                                {
                                                                        k=0;
                                                                                                        k= lru(0);      //searching for LRU block in L1
                                                                                if((l1_cache+( (SET*INDEX)+ k ) ) ->dirty       == 1)
                                                                                {write_memory(k);}
                                                                                swap(k,j);
                                                                        (l1_cache+( (SET*INDEX)+ k ) ) ->age    = 0;
                                                                        (l1_cache+( (SET*INDEX)+ k ) ) ->dirty  = 1;
                                                                }

                                                }

                                //CODE FOR VICTIM CACHE MISS------------------------------------
                                                else
                                                {
                                                        l2_w_miss++;                                    //Victim write miss update
                                                        int k = search_empty(0);        //searching for empty block in L1

                                                                if(k != -1)             //empty block in L1 found
                                                                {
                                                                        init_block(k);  //update the L1 cache block with new values
                                                                }
                                                                else                    //NO empty block in L1
                                                                {
                                                                        k=0;
                                                                        k= lru(0);                              //searching for LRU block in L1
                                                                                if((l1_cache+( (SET*INDEX)+ k ) ) ->dirty       == 1)
                                                                                        {write_memory(k);}
                                                                        int m =search_empty(1); //searching for empty block in Victim
                                                                                if(m != -1)             //empty block in Victim cache found
                                                                                {
                                                                                        swap(k,m);
                                                                                        init_block(k);
                                                                                }
                                                                                else                    //NO empty block in Victim cache
                                                                                {
                                                                                        m = 0;
                                                                                        m = lru(1);             //searching for LRU block in victim
                                                                                        swap(k,m);
                                                                                        init_block(k);  //update the L1 cache block with new values
                                                                                }
                                                                }
                                                        }
                                }

                                //CODE IF VICTIM CACHE DOES NOT EXIST----------->>>>>>>>>>>
                                                else                            //VICTIM_SIZE = 0
                                                {
                                                        int k = search_empty(0);        //searching for empty block in L1
                                                                if(k != -1)             //empty block in L1 found
                                                                {
                                                                        init_block(k);  //update the L1 cache block with new values

                                                                 }
                                                                else                    //NO empty block in L1
                                                                {
                                                                        k=0;
                                                                        k=lru(0);               //searching for LRU block in L1
                                                                                if((l1_cache+( (SET*INDEX)+ k ) ) ->dirty       == 1)
                                                                                        {write_memory(k);}
                                                                        init_block(k);  //update the L1 cache block with new values
                                                                }
                                                }
                        }
        } //WB policy -- write allocate ends

        //WT policy -- No write allocate
        else
        {
                int i = search(0);
                //CODE FOR L1 CACHE HIT----------------------------------
                        if(i != -1)                     //block found in L1
                        {
                                l1_w_hit++;             //L1 write hit update
                                (l1_cache+( (SET*INDEX)+i ) ) ->age     = 0;
                                write_memory(0);
                        }
                        //CODE FOR L1 CACHE MISS------------------------------------
                                                else                            //block NOT found in L1
                                                {
                                                        l1_w_miss++;            //L1 write miss update

                                                //CODE IF VICTIM CACHE EXISTS----------->>>>>>>>>>>
                                                        if(L2_SIZE != 0)                //victim cache exists
                                                        {
                                                                int j = search(1);      //searching for the block in victim cache
                                                                write_memory(0);

                                                        //CODE FOR VICTIM CACHE HIT------------------------------------
                                                                        if(j != -1)             //block found in victim cache
                                                                        {
                                                                                l2_w_hit++;                                     //Victim write hit update
                                                                                int k = search_empty(0);        //searching for empty block in L1

                                                                                        if(k != -1)             //empty block in L1 found
                                                                                        {
                                                                                                swap(k,j);
                                                                                                (l1_cache+( (SET*INDEX)+ k ) ) ->age    = 0;
                                                                                        }
                                                                                        else                    //NO empty block in L1
                                                                                                  {
                                                                                                k=0;
                                                                                                k= lru(0);      //searching for LRU block in L1
                                                                                                swap(k,j);
                                                                                                (l1_cache+( (SET*INDEX)+ k ) ) ->age    = 0;
                                                                                        }
                                                                        }

                                                        //CODE FOR VICTIM CACHE MISS------------------------------------
                                                                        else
                                                                        {
                                                                                l2_w_miss++;                                    //Victim write miss update
                                                                        }
                                                        }

                                                //CODE IF VICTIM CACHE DOES NOT EXIST----------->>>>>>>>>>>
                                                else                            //VICTIM_SIZE = 0
                                                {write_memory(0);}

                                }//L1 miss code ends

        }//WT policy ends


return;
};
//write() ends--
