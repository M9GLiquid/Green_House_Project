#include "timeList.h"

/**
  * Add a new node to the head of the list
  * @param time_list: the list where the element is to be added to
  * @param node_element: the element to be added
  * @return void
	*/
void Put_First(struct Time_Node **time_list, struct Time_Node *node_element){
	// The list is empty and the node_element is the first one
  if(*time_list == NULL){
		// Start of with the new min/max and add the first to the sum
		min = node_element->timestamp_temp;
		max = node_element->timestamp_temp;
		sum = Get_4_Signed_Bytes(&node_element->timestamp_temp, 1);
    *time_list = node_element;
    return;
  }
	
	// Make this new node be the head node
  node_element->next = *time_list;
  *time_list = node_element;
}

/**
  * Create a time node with the values from the timestamp_temp
  * @param time_list: Used only if the memory is full and we need to remove the last element in the list to replace it
  * @param timestamp_temp: a collection of hhmmTTTT where hh is hour, mm is minute, TTTT is the temperature
  * @return a new TimeNode
	*/
struct Time_Node *Create_TimeNode(struct Time_Node **time_list, unsigned int timestamp_temp) {
	// Try to allocate memory for the TimeNode
  TimeNode *new_time_node = malloc(sizeof(TimeNode));
	
	// If the memory of the arduino is full, remove the last element and free up it's memory to allocate a new memory
  if (new_time_node == NULL) {
	TimeNode *tempNode = *time_list;
		while(tempNode->next != NULL)
			tempNode = tempNode->next;
    Disconnect(time_list, tempNode);
    new_time_node = malloc(sizeof(TimeNode));
  }		
	
	// Add the temp in the int to the sum
	sum += Get_4_Signed_Bytes(&timestamp_temp, 1);
	// Update todays max if needed
	if (Get_4_Signed_Bytes(&timestamp_temp, 1) > Get_4_Signed_Bytes(&max, 1))
		max = timestamp_temp;
	// Update todays min if needed
	if (Get_4_Signed_Bytes(&timestamp_temp, 1) < Get_4_Signed_Bytes(&min, 1))
		min = timestamp_temp;
	// New element added to the overall count of the day
	listSize++;
	
	// Add the values to the new time node
  new_time_node->timestamp_temp = timestamp_temp;
  new_time_node->next = NULL;
  return new_time_node;
}

/**
  * Removes the node_element from the time_list (list) and free it's memory
  * @param time_list: List to be searched through
  * @param node_element: node to be removed and freed
  * @return void
	*/
void Disconnect(struct Time_Node **time_list, struct Time_Node *node_element){
    TimeNode *prevNode = NULL;
    TimeNode *currentNode = *time_list;

		// Check if the element exist's in the list
    if(Is_Member(time_list, node_element) == 0)
        return;

		// The element is the head of the node and alone in the list, null it and free it
    if(currentNode->next == NULL){
        *time_list = NULL;
      	free(node_element);
        return;
    }

    // two  or more elements
    while (currentNode != NULL) {
        // If we do not match go to next
        if (currentNode != node_element) {
            prevNode = currentNode;
            currentNode = currentNode->next;
            continue;
        }

				// First element to remove
        if (prevNode == NULL ){ 
            currentNode = currentNode->next;
            *time_list = currentNode;
      			free(node_element);
            return;
						// Last element to remove
        }else if (currentNode->next == NULL){ 
            prevNode->next = NULL;
            currentNode = NULL;
      			free(node_element);
            return;
				// Middle element to remove
        }else{ 
            prevNode->next = currentNode->next;
            currentNode = NULL;
      			free(node_element);
            return;
        }
    }
}

						
/**
  * Checks whether node_element is a member of the time_list
  * @param time_list:
  * @param node_element:
  * @return 0 node_element not found, 1 node_element found
	*/
int Is_Member(struct Time_Node **time_list, struct Time_Node *node_element){
    TimeNode *temp = *time_list;
		
		// check if we sent in either a empty list or element
    if(*time_list == NULL || node_element == NULL)
        return 0;

		// the element is the head of the list
    if(temp == node_element)
        return 1;

		// The element is somewhere in the middle to end of the list 
    while(temp != NULL){
        if(temp == node_element)
            return 1;
        temp = temp->next;
    }
		
    return 0;
}

/**
  * Clear the entire node collection (list) and free theire memory
  * @param time_list: List to be freed
  * @return void
	*/
void Clear_Memory(struct Time_Node **time_list) {
	// Check to see if the list is empty
    if (*time_list == NULL) 
        return;
		
    TimeNode *current = *time_list;
    TimeNode *temp = NULL;

		// Clear all the elements one by one and free 
    while (current != NULL) {
      temp = current->next;
      free(current);
      current = temp;
    }
    *time_list = NULL;
		listSize = 0;
}
