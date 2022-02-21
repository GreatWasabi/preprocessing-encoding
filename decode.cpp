#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include "defns.h"

using namespace std;

//insertion sort
void insertion_sort(tree  array[], int size)
{
	tree  temp;
	int j;
	for(int i=1;i<size;i++)
	{
		temp = array[i];
		j = i-1;
		while(j>=0 && array[j].freq>temp.freq)
		{
			array[j+1]=array[j];
			j--;
		}
		array[j+1]=temp;
	}
}

//merge for merge sort
void merge(tree array[], int left, int mid, int right)
{
	int i = left, j = mid+1, k=left;
	tree temp[right+1];
	while(i<=mid && j<=right)
	{
		if(array[i].freq<=array[j].freq)
		{
			temp[k]=array[i];
			i++;
			k++;
		}
		else
		{
			temp[k]=array[j];
			j++;
			k++;
		}
	}
	while(i<=mid)
	{
		temp[k]=array[i];
		i++;
		k++;
	}
	while(j<=right)
	{
		temp[k]=array[j];
		j++;
		k++;
	}
	for(int i=left;i<=right;i++)
		array[i]=temp[i];
}
//merge sort
void merge_sort(tree array[], int left_index, int right_index)
{
	if(left_index < right_index)
	{
		int middle = (left_index+right_index)/2;
		merge_sort(array,left_index,middle);
		merge_sort(array,middle+1,right_index);
		merge(array,left_index,middle,right_index);
	}
}

//main
int main(int argc, char* argv[])
{
	char file_name[20]="";
	char sort_method[10]="";
	if(argc==3)
	{
		if(strcmp(argv[2],"insertion")==0 || strcmp(argv[2],"merge")==0)
		{
			strcpy(file_name,argv[1]);
			strcpy(sort_method,argv[2]);
		}
		else
		{
			cout << "sort_method input incorrect. -- (insertion/merge) -- *CASE SENSITIVE*"<<endl;
			return 0;
		}
	}
	//if argc != 3 then the correct usage syntax will be displayed and the program will end
	else if(argc!=3)
	{
		cout << "Usage: "<<argv[0]<<"[pre-file.txt] [insertion/merge]"<<endl;
		return 0;
	}

	//opeing file
	fstream file;
	file.open(file_name);

	//create symbol array S of 128 index
	symbol S[128];
	int index, frequency;

	//initializing S
	for(int i = 0; i<128; i++)
	{
		S[i].symbol = char(i);
		S[i].freq = 0;
		S[i].parent = NULL;
		S[i].left = NULL;
		S[i].right = NULL;
		for(int j=0;j<E_LEN-1;j++)
			S[i].encoding[j] = ' ';
	}
	int size = 0;

	//taking input from file
	if(file.is_open())
	{
		while(file >> index >> frequency)
		{
			S[index].freq = frequency;
			size++;
		}
	}
	//initializing components for trees
	int Alpha_Count=-1;
	int NonAlpha_Count=-1;
	tree Alpha[52];
	tree NonAlpha[76];

	//initializing Alpha and NonAlpha tree
	for(int i=0;i<128;i++)
	{
		if(S[i].freq>0)
		{
			if(i>=65&&i<=90 || i>=97&&i<=122)
			{
				Alpha_Count++;
				Alpha[Alpha_Count].index = i;
				Alpha[Alpha_Count].symbol = char(i);
				Alpha[Alpha_Count].freq = S[i].freq;
				Alpha[Alpha_Count].root = &S[i];
			}
			else
			{
				NonAlpha_Count++;
				NonAlpha[NonAlpha_Count].index = i;
				NonAlpha[NonAlpha_Count].symbol = char(i);
				NonAlpha[NonAlpha_Count].freq = S[i].freq;
				NonAlpha[NonAlpha_Count].root = &S[i];
			}
		}
	}
	//sorting using desired sort method
	if(strcmp(sort_method,"insertion")==0)
	{
		insertion_sort(Alpha, Alpha_Count+1);
		insertion_sort(NonAlpha, NonAlpha_Count+1);
		cout<<"\nSort Method: Insertion\n";
	}
	else if(strcmp(sort_method,"merge")==0)
	{
		merge_sort(Alpha, 0, Alpha_Count);
		merge_sort(NonAlpha, 0, NonAlpha_Count);
		cout << "\nSorth Method: Merge\n";
	}
	
	file.close();
	return 0;
}
