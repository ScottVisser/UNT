#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

/*
Scott Visser
Recitation 1
Convert number to binary
*/

int main(void)
{

int num=0;
int i=0;
int number=0;
int a=0;
int b=0;

cout << "Please enter number: ";
cin >> num;
cout << endl;

number=num;

while (num!=0)
{
	a=num%2;
	num=num/2;
	i++;
	cout << a;
}
cout << endl << endl;

int output[i];
int input[i];
int j=0;

for (j=0;j<i;j++)
{
	input[j]=0;
	output[j]=0;
}

for (j=0;j<i;j++)
{
	b=i-j
	input[b]=number%2;
	number=number/2;
}

for (j=0;j<i;j++)
{
	cout << input[j];
}
cout << endl;

return 0;
}
