#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "defns.h"

using namespace std;

int main()
{

	//creating a symbol object S
	symbol S[128];

	//initializing values inside S
	for(int i=0;i<128;i++)
	{
		S[i].symbol = (char)i;
		S[i].freq = 0;
		S[i].parent = NULL;
		S[i].left = NULL;
		S[i].right = NULL;
		S[i].encoding[0] = ' ';
	}

	int size = 0;

	//initializing string with a max size of 10000
	char str[20000];

	//taking input from the user
	cin.getline(str,20000,'\0');

	//size is the used true size of the string str
	for(int i = 0;str[i]!='\0';i++)
	{
		size++;
	}

	//increasing frequency
	for(int i=0; i<size; i++)
	{
		S[str[i]].freq++;
	}

	//printing the frequency
	for(int i=0; i<128;i++)
	{
		if(S[i].freq>0)
		cout <<  i << "\t" << S[i].freq << "\n";
	}
	return 0;
}
