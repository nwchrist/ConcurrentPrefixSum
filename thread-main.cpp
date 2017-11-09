#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include "ThreadClass.h"
#include "thread.h"

/*
 * Author: Nicholas Christensen					User ID: nwchrist
 * Due Date: 11/2/2017
 * Class: CS3331
 * Program Assignment #3
 * File Name: thread-main.cpp
 * Program Purpose:
 *		This program takes an array of numbers and outputs the 
 *		prefix sum array for those numbers
 */

using namespace std;

int ** B;

int main (void)
{
	//First we will print out the initial declaration of the program
	//At this point we only have one thread, so we don't have to worry about race conditions in the output
	cout << "Concurrent Prefix Sum Computation" << endl << endl;
	
	//The first step of the program is to read n integers into the array x[*]
	int size;
	cin >> size;
	int x[size];
	
	cout << "Number of input data = " << size << endl << "Input array:" << endl;
	char output [10000];
	char * outputPointer = output;
	char buffer [100];
	sprintf(buffer, "   ");
	strcat(outputPointer, buffer);
	
	for (int i = 0; i < size; i++)
	{
		if (((i % 9) == 0) && (i != 0))
		{
			sprintf(buffer, "\n   ");
			strcat(outputPointer, buffer);
		}
		 cin >> x[i];
		 sprintf(buffer, "%4d", x[i]);
		 strcat(outputPointer, buffer);
	}
	write(1, output, strlen(output));
	cout << endl << endl;
	
	//Second, we are going to initialize B
	int k = (int) (log10(size) / log10(2));
	B = new int * [k+1];
	for (int i = 0; i < (k+1); i++)
	{
		B[i] = new int [size];
	}

	for (int i = 0; i < size; i++)
	{
		B[0][i] = x[i];
	}
	
	int gap = 1;


	//Third, we must iterate through k steps
	for (int i = 0; i < k; i++)
	{
		memset(outputPointer, '\0', sizeof(output));
		cout << "Run " << (i+1) << ":" << endl;
		//In each step we create n threads
		thread * run[size];
		for (int j = 0; j < size; j++)
		{
			run[j] = new thread(gap, j, i, B);
			run[j] -> Begin();
		}
		
		//And wait for all n threads to exit
		for (int j = 0; j < size; j++)
		{
			run[j] -> Join();
		}
		gap = gap * 2;
		cout << "Result after run " << (i+1) << ":" << endl;
		
		//After each run print out the results for the new row
		sprintf(buffer, "   ");
		strcat(outputPointer, buffer);
		for (int m = 0; m < size; m++)
		{
			if (((m % 9) == 0) && (m != 0))
			{
				sprintf(buffer, "\n   ");
				strcat(outputPointer, buffer);
			}
			sprintf(buffer, "%4d", B[i+1][m]);
			strcat(outputPointer, buffer);
		}
		write(1, output, strlen(output));
		cout << endl << endl;
	}
	
	//Lastly, we print out the last row of B, and then exit.
	cout << "Final Result after run " << k << ":" << endl;
	memset(outputPointer, '\0', sizeof(output));
	sprintf(buffer, "   ");
	strcat(outputPointer, buffer);
	for (int m = 0; m < size; m++)
	{
		if (((m % 9) == 0) && (m != 0))
		{
			sprintf(buffer, "\n   ");
			strcat(outputPointer, buffer);
		}
		sprintf(buffer, "%4d", B[k][m]);
		strcat(outputPointer, buffer);
	}
	write(1, output, strlen(output));
	cout << endl;
	Exit();
}