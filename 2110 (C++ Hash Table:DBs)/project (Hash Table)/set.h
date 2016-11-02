/*
Scott Visser
csce2110 program 2
set hedder file
set class methods defined
*/

// determines which bucket user input will be put in
void Set::add(int datainput)
{
	// hash key
	bucketIndex = (datainput * datainput) % 7;

	if (bucket[bucketIndex] == NULL)
	{
		bucket[bucketIndex] = bucket[bucketIndex]->case0(datainput);
	} 
	else
	{
		bucket[bucketIndex]->case1(datainput);
	}
	

};

void Set::show(void)
{
	// loops through each bucket and calls show (node) method for each
	int i;
	for (i=0;i<7;i++)
	{
		if (bucket[i] != NULL)
		{
			cout << "(";
			bucket[i]->show(); 
			cout << ") ";
		}
		else
			cout << "() ";
	}
	cout << endl;
};

// remove function 
void Set::remove(int datainput)
{
	// hash key: determine bucket index
	bucketIndex = (datainput * datainput) % 7;
	
	if (bucket[bucketIndex] == NULL) //no values in bucket
		cout << "WARNING: target value not found: " << datainput << endl;
	else if (bucket[bucketIndex]->checknext()  == datainput)//first value in bucket == user input
		bucket[bucketIndex] = bucket[bucketIndex]->removeFirst();
	else
		bucket[bucketIndex]->removeOther(datainput);	
};

// search function takes user input, determines bucket
void Set::search(int datainput)
{
	//hash key
	bucketIndex = (datainput * datainput) % 7;
	if (bucket[bucketIndex] == NULL)
		cout << "false" << endl;
	else
		bucket[bucketIndex]->search(datainput);


};
