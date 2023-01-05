#include "dateList.h"

// Global Variables
unsigned int max = 0x0;
unsigned int min = 0x0;
short listSize = 0;
int sum = 0; 

/**
  * Insert an element node at the firstplace and move all other 
	* existing nodes to behind this one
  * @param date_list: The list to insert the node into
  * @param element_node: The node to insert
  * @return void
	*/
void Insert_First(struct Date_Node **date_list, struct Date_Node *element_node){
		// Check to see whether the list is empty
    if (*date_list == NULL){
			
			// the element is now the list
      *date_list = element_node;
			
      return;
    }
		
		// Put the "temp" list right next to the element we want to insert.
    element_node->next = *date_list; 
		
		// The new list is now the element including the old list.
    *date_list = element_node; 
}

/**
  * Create a dateNode and return it with the value of the date, max, min and average
  * @param date_list: The DateNode (List) that we start off with
  * @param time_list: The created TimeNode (List) to be inserted into the current DateNode (List)
  * @param date: Todays date to be inserted into the list
  * @return a new populated node
	*/
struct Date_Node *Create_DateNode(struct Date_Node **date_list, struct Time_Node **time_list, unsigned int date) {
  DateNode *new_date_node = malloc(sizeof(DateNode));
	// Calculate the average before we clear the listSize
	short average = sum/listSize;
	
	// Check to make sure the new_date_node got an memory allocation
  if (new_date_node == NULL){
  	DateNode *temp_node = *date_list;
		
		// Go to last element node
    while(temp_node->next != NULL)
      temp_node = temp_node->next;
		
		//Clear all timeNodes in the oldest DateNode.
    clearMemory(temp_node->time_list); 
		
		//Deleting the oldest DateNode.
    Delete(date_list, temp_node); 
		
		//Free memory in the oldest DateNode.
    //free(temp_node); 
		
		// Allocate new memory for new_date_node
    new_date_node = malloc(sizeof(DateNode));
  }
	
	// Set all the values to the new_date_node
  new_date_node->date = date;
  new_date_node->time_list = time_list;
  new_date_node->next = NULL;
  new_date_node->max = max;
  new_date_node->min = min;
  new_date_node->average = average;
	
  return new_date_node;
}

/**
  * Delete an element node in the linked list and free up its memory
  * @param date_list: the list to remove the element node from
  * @param element_node: the node to remove from the list
  * @return void
	*/
void Delete(struct Date_Node **date_list, struct Date_Node *element_node){
	
    DateNode *prevNode = NULL;
    DateNode *currentNode = *date_list;

    // ALL NULL or Element not found scenario
    if(Exist(date_list, element_node) == 0)
        return;

    //Only one element_node set date_list to NULL
    if(currentNode->next == NULL){
        *date_list = NULL;
    		free(element_node); 
        return;
    }

    // Two  or more elements
    while (currentNode != NULL) {
        // If we do not match go to next
        if (currentNode != element_node) {
            prevNode = currentNode;
            currentNode = currentNode->next;
            continue;
        }
				// First element_node to remove
        if (prevNode == NULL) { 
            currentNode = currentNode->next;
            *date_list = currentNode;
    				free(element_node); 
            return;
				// Last element_node to remove
        } else if (currentNode->next == NULL) { 
            prevNode->next = NULL;
            currentNode = NULL;
    				free(element_node); 
            return;
				// Middle element_node to remove
        } else {
            prevNode->next = currentNode->next;
            currentNode = NULL;
    				free(element_node); 
            return;
        }
    }
}

/**
  * Checks to see if the element_node exists in the date_list and if it 
	* does it returns 1 else 0
  * @param date_list: The list to be searched
  * @param element_node: The node to search for in the list
  * @return 0 or 1 depending on the result of the query
	*/
int Exist(struct Date_Node **date_list, struct Date_Node *element_node){
    DateNode *temp_node = *date_list;
		
    if(*date_list == NULL || element_node == 0)
        return 0;
		
    if(temp_node == element_node)
        return 1;
		
    while(temp_node != NULL){
        if(temp_node == element_node)
            return 1;
        temp_node = temp_node->next;
    }
		
    return 0;
}
