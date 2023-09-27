# Smart Greenhouse Project

![Date](https://img.shields.io/badge/Date-2023--01--05-green)

**Authors:** Hieu Tran, Thomas Lundqvist
**Supervisor:** Hazem Ali, Lukas Lindqvist
**Group:** 9
**Course:** Computer System Engineering I (DT4012)
**Institution:** Halmstad University


## Abstract


The aim of this project is to monitor and control a Greenhouse climate by programming in C language on IAR Embedded Workbench IDE and connecting components to our CPU. The components are determined to measure the temperature and light intensity in order to detect the highest, lowest and average temperatures for each day to later be stored and saved in the CPU along with detecting the sun position in degrees and saving data of the amount of time there is sunlight. When the temperature is exceeding under twenty degrees or above twenty-five degrees an alarm will be triggered, and a LED light will blink constantly until it resets manually.
The project reported in this document focuses on memory efficiency and how to monitor and control a Greenhouse climate by observing the temperature and light intensity. This report includes an introduction section with an explanation of the full embedded system by using illustrative diagrams and written explanations, conclusion section where we discuss the design of the project and the possibilities for a hardware specification constraints, reference section that lists the sources of any material we have used for the document and lastly a section for the project requirements achieved and the result of fulfilling them.


## Table of Contents


- [Introduction](#introduction)
- [Discussion & Result](#discussion--result)
- [Conclusion](#conclusion)
- [References](#references)
- [Guide to the system](#guide-to-the-system)

<p>  This project is done as part of the course “Computer System Engineering I” for engineering students at Halmstad University.


## Introduction

[Back to Top](#table-of-contents)


<p>  In this document we will describe about the full embedded system using illustrative diagrams and describe the implement of several components such as the servomotor, LEDs, display and keypad to our hardware consisting of the CPU microchip SAM3X8E - ARM embedded computer platform (Arduino due) capable to operate at a maximum speed of 84MHz and has a SRAM memory between 256 to 512 Kbytes embedded flash using cache memory and consumes great amount of power (1).


## Discussion & Result

[Back to Top](#table-of-contents)


<p>  The application for the system components used in this project are two 74HC245-Chips, one of which controls a display and the other the keypad, photo sensors that senses the light intensity with photoresistors (2), one temperature sensor(MAX6575H) with a temperature range between -40 to 125 degrees to measure the temperature within a zone (3), a servo motor(HIT-HS55) that can rotate up to 180 degrees at maximum with impact of the photosensors is used to control revolutions per minute by directing towards an specific direction, a keypad 4x matrix keypad where the rows are connected to the PIO pins (Peripheral Input/Output) configured as output and columns connected to PIO pins configured as input(4), a LCD display that uses the keypad as a input to print the data received from the CPU, and LEDs to whether it is dark or light after eight hours and if the temperature exceeds above the changeable twenty to twenty five degrees.


## Conclusion

[Back to Top](#table-of-contents)


<p>  The components were determined by a computer connected to our JLink driver which is following connected to our CPU. The computer connected to the driver was used for programming to the CPU to make all the components functional by enabling and disabling certain pins connected to the respective components. An implementation of a data structure “Linked List” with a linear collection of data elements linked with a pointer was required in this project to store the data of the temperature for the duration of seven days (5).


## References

[Back to Top](#table-of-contents)


<p>  The main objective for requirement one is to have a timestamp by creating a system with a calendar that allows showing date and time represented as DD/MM/YYYY, while the time as hh:mm:ss in a 24-hour clock system. The user should be able to configure it by using the keypad and display. The timestamp created for this project is based on bytes with the help of byte manipulation.


## Guide to the system

[Back to Top](#table-of-contents)


<p>  · STEP 1 (Menu choice 0): Select Date View is displayed <br>
Start by selecting date and time <br>
We are then directed to STEP 2 <br><br>
· STEP 2: Menu View is displayed <br>
Press 0 in the menu we go back to STEP 1 <br>
Press 1 in the menu we go to STEP 3 <br>
Press 2 in the menu we go to STEP 4 <br>
Press 3 in the menu we go to STEP 5 <br>
Press 4 in the menu we go to STEP 6 <br><br>
·   	STEP 3 (Menu choice 1):  Records View is displayed <br>
Press * or # to go back to STEP 2 <br><br>
·   	STEP 4 (Menu choice 2):  Menu View is still visible  <br>
The speed factor is changed and also the actual speed of the time changes <br><br>
·   	STEP 5 (Menu choice 3): Menu View is still visible <br>
If the alarm is active then this disables it <br><br>
·   	STEP 6 (Menu choice 4): Alarm Limit View is displayed <br>
In here we can change the Alarm limits <br>
We are then presented with a choice at the end of change: <br>
Press [1-9]: go to STEP 2 <br>
Press 0: go to STEP 6 again <br>
