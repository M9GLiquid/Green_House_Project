#ifndef TIMELIST_H
  #define TIMELIST_H

	// Includes
	#include "byte_manipulator.h"
	#include "datelist.h"
	#include <stdlib.h>
	#include <stdio.h>

	// Global Variable
	extern short listSize;

  //Functions
  struct Time_Node *Create_TimeNode(struct Time_Node **time_list, unsigned int timestamp_temp);
  void Disconnect(struct Time_Node **time_list, struct Time_Node *node_element);
  int Is_Member(struct Time_Node **time_list, struct Time_Node *node_element);
  void Put_First(struct Time_Node **time_list, struct Time_Node *node_element);
  void Clear_Memory(struct Time_Node **time_list);

	// Structs
  typedef struct Time_Node{
		// timestamp_temp - hhmmTTTT - 15200021, hour:15, minute:20 and temperature:20
  	unsigned int timestamp_temp; 
		// pointer to the next element
  	struct Time_Node *next; 
  }TimeNode;

#endif