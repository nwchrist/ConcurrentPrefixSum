#include "ThreadClass.h"

/*
 * Author: Nicholas Christensen					User ID: nwchrist
 * Due Date: 11/2/2017
 * Class: CS3331
 * Program Assignment #3
 * File Name: thread.h
 * Program Purpose:
 *		This file is the header file for the thread
 *		of program 3, and contains the class definitions
 *		for that thread.
 */

class thread : public Thread
{
	public:
		thread(int g, int i, int r, int ** a);
	private:
		int gap;
		int run;
		int index;
		int ** array;
		void ThreadFunc();
};