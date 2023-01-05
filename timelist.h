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
  struct Time_Node *create_timeNode(struct Time_Node **time_list, unsigned int timestamp_temp);
  void disconnect(struct Time_Node **time_list, struct Time_Node *node_element);
  int isMember(struct Time_Node **time_list, struct Time_Node *node_element);
  void putFirst(struct Time_Node **time_list, struct Time_Node *node_element);
  void clearMemory(struct Time_Node **time_list);

	// Structs
  typedef struct Time_Node{
		// timestamp_temp - hhmmTTTT - 15200021, hour:15, minute:20 and temperature:20
  	unsigned int timestamp_temp; 
		// pointer to the next element
  	struct Time_Node *next; 
  }TimeNode;

#endif