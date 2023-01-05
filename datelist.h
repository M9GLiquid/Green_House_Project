#ifndef DATELIST_H
  #define DATELIST_H

	// Includes
	#include "timeList.h"
	#include "byte_manipulator.h"
	#include <stdlib.h>
	#include <stdio.h>

	// Functions
	struct Date_Node *Create_DateNode(struct Date_Node **date_node, struct Time_Node **time_node, unsigned int date );
	void Insert_First(struct Date_Node **date_list, struct Date_Node *element);
	void Delete(struct Date_Node **date_list, struct Date_Node *element);
	int Exist(struct Date_Node **date_list, struct Date_Node *node);
	void printList(struct Date_Node *date_list);

	// Structs
	typedef struct Date_Node {
		// date DDMMYYYY
		unsigned int date; 
		// hhmmTTTT
		unsigned int max; 
		// hhmmTTTT
		unsigned int min;
		short average;
		// Node for time and temperature
		struct Time_Node **time_list; 
		// The next node
		struct Date_Node *next; 
	}DateNode;
		
	// Global Variables
	extern DateNode *dateList; // The list
	extern unsigned int max, min; // hhmmTTTT
	extern int sum;
#endif	