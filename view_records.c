#include "view_records.h"

/**
  * Write out the defaults of the menu view
  * @return void
	*/
void Init_Display_Records(){
	Write_Characters_2_DisplayPosition("Press */# to return  DD/MM/YYYY hh:mm:ss", 0, 0, _VIEW_RECORDS);
  Write_Characters_2_DisplayPosition("DD/MM/YYYY   MIN        AVG   MAX       ", 0, 1, _VIEW_RECORDS);
  Write_Characters_2_DisplayPosition("----------------------------------------", 0, 2, _VIEW_RECORDS);
	Write_Characters_2_DisplayPosition("DD/MM/YYYY TTTT'[hh:mm] TT' TTTT'[hh:mm]", 0, 3, _VIEW_RECORDS);
  Write_Characters_2_DisplayPosition("----------------------------------------", 0, 4, _VIEW_RECORDS);
	Write_Characters_2_DisplayPosition("DD/MM/YYYY TTTT'[hh:mm] TT' TTTT'[hh:mm]", 0, 5, _VIEW_RECORDS);
  Write_Characters_2_DisplayPosition("----------------------------------------", 0, 6, _VIEW_RECORDS);
	Write_Characters_2_DisplayPosition("DD/MM/YYYY TTTT'[hh:mm] TT' TTTT'[hh:mm]", 0, 7, _VIEW_RECORDS);
  Write_Characters_2_DisplayPosition("----------------------------------------", 0, 8, _VIEW_RECORDS);
	Write_Characters_2_DisplayPosition("DD/MM/YYYY TTTT'[hh:mm] TT' TTTT'[hh:mm]", 0, 9, _VIEW_RECORDS);
  Write_Characters_2_DisplayPosition("----------------------------------------", 0, 10, _VIEW_RECORDS);
	Write_Characters_2_DisplayPosition("DD/MM/YYYY TTTT'[hh:mm] TT' TTTT'[hh:mm]", 0, 11, _VIEW_RECORDS);
  Write_Characters_2_DisplayPosition("----------------------------------------", 0, 12, _VIEW_RECORDS);
	Write_Characters_2_DisplayPosition("DD/MM/YYYY TTTT'[hh:mm] TT' TTTT'[hh:mm]", 0, 13, _VIEW_RECORDS);
  Write_Characters_2_DisplayPosition("----------------------------------------", 0, 14, _VIEW_RECORDS);
	Write_Characters_2_DisplayPosition("DD/MM/YYYY TTTT'[hh:mm] TT' TTTT'[hh:mm]", 0, 15, _VIEW_RECORDS);
}

/**
  * Initiate and then write out the changes (records) to the display
  * @return void
	*/
void View_Records(){
	Init_Display_Records();
	Display_Everyday_Record();
}

/**
  * Write out each of the nodes in the datelist to the screen on seperate rows
  * @return void
	*/
void Display_Everyday_Record(){
	char string[2];
	
	DateNode *temp = dateList;
	unsigned char row = 3;
	while(temp != 0){
		// DD
		snprintf(string, 3, "%02d", Get_2_Bytes(&temp->date, DAY));
		Write_Characters_2_DisplayPosition(string, 0, row, _VIEW_RECORDS); 
		
		// MM
		snprintf(string, 3, "%02d", Get_2_Bytes(&temp->date, MONTH));
		Write_Characters_2_DisplayPosition(string, 3, row, _VIEW_RECORDS); 
		
		// YY
		snprintf(string, 3, "%02d", Get_2_Bytes(&temp->date, MINUTES));
		Write_Characters_2_DisplayPosition(string, 6, row, _VIEW_RECORDS); 
		// YY
		snprintf(string, 3, "%02d", Get_2_Bytes(&temp->date, SECONDS));
		Write_Characters_2_DisplayPosition(string, 8, row, _VIEW_RECORDS);
		
		// TTTT
		// min temperature
		snprintf(string, 3, "% d", Get_2_Bytes(&temp->min, 4));
		if (string[0] == '1')
			string[0] = '-';
		if (string[0] == ' ' && string[1] == '0')
			Write_Characters_2_DisplayPosition("  ", 11, row, _VIEW_RECORDS); 
		else
			Write_Characters_2_DisplayPosition(string, 11, row, _VIEW_RECORDS);
		snprintf(string, 3, "%02d", Get_2_Bytes(&temp->min, 6));
		Write_Characters_2_DisplayPosition(string, 13, row, _VIEW_RECORDS);
		
		// hh from min temp
		snprintf(string, 3, "%02d", Get_2_Bytes(&temp->min, 0));
		Write_Characters_2_DisplayPosition(string, 17, row, _VIEW_RECORDS); 
		
		// mm from min temp
		snprintf(string, 3, "%02d", Get_2_Bytes(&temp->min, 2));
		Write_Characters_2_DisplayPosition(string, 20, row, _VIEW_RECORDS); 
		
		// TT
		// Average temp
		snprintf(string, 3, "%02d", temp->average);
		Write_Characters_2_DisplayPosition(string, 24, row, _VIEW_RECORDS); 
		
		// TTTT
		// max temperature
		snprintf(string, 3, "% d", Get_2_Bytes(&temp->max, 4));
		if (string[0] == '1')
			string[0] = '-';
		if (string[0] == ' ' && string[1] == '0')
			Write_Characters_2_DisplayPosition("  ", 28, row, _VIEW_RECORDS); 
		else
			Write_Characters_2_DisplayPosition(string, 28, row, _VIEW_RECORDS);
		snprintf(string, 3, "%02d", Get_2_Bytes(&temp->max, 6));
		Write_Characters_2_DisplayPosition(string, 30, row, _VIEW_RECORDS); 
		
		// hh from max temp
		snprintf(string, 3, "%02d", Get_2_Bytes(&temp->max, 0));
		Write_Characters_2_DisplayPosition(string, 34, row, _VIEW_RECORDS); 
		
		// mm from max temp
		snprintf(string, 3, "%02d", Get_2_Bytes(&temp->max, 2));
		Write_Characters_2_DisplayPosition(string, 37, row, _VIEW_RECORDS); 
		
		
		row += 2;
    temp = temp->next;
	}
}