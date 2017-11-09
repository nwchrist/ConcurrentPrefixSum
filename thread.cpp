#include "thread.h"
#include <string.h>
#include <stdio.h>

/*
 * Author: Nicholas Christensen					User ID: nwchrist
 * Due Date: 11/2/2017
 * Class: CS3331
 * Program Assignment #3
 * File Name: thread.cpp
 * Program Purpose:
 *		This file is the thread implementation for program3, 
 *		and computes the prefix sum of index i then stores
 *		it in the next row of B
 */

thread::thread(int g, int i, int r, int ** a)
{
	gap = g;
	run = r;
	index = i;
	array = a;
	ThreadName.seekp(0, ios::beg);
	ThreadName << "Thread" << (r+1) << "-" << i << '\0';
}

void thread::ThreadFunc()
{
	Thread::ThreadFunc();
	
	//Print out info about the thread being created
	char output [10000];
	char buffer [1000];
	char * outputPointer = output;
	char name [20];
	sprintf(name, "   Thread%d-%d", (run+1), index);
	sprintf(output, "   %s created\n", name);
	write(1, outputPointer, strlen(output));
	memset(outputPointer, '\0', sizeof(output));
	
	if (index - gap < 0)
	{
		//If the index - gap is < 0, just copy the index over
		array[run+1][index] = array[run][index];
		
		sprintf(output, "   %s copies x[%d]\n", name, index);
		write(1, outputPointer, strlen(output));
	} else {
		//Otherwise, compute the new value for the index
		array[run+1][index] = (array[run][index]) + (array[run][index - gap]);
		
		sprintf(output, "   %s computes x[%d] + x[%d-2^(%d-1)]\n", name, index, index, run+1);
		write(1, outputPointer, strlen(output));
	}
	memset(outputPointer, '\0', sizeof(output));
	sprintf(output, "   %s exits\n", name);
	write(1, outputPointer, strlen(output));
	Exit();
}
