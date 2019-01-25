/***************************************************************
Filename:			Display.cpp
Version:			1.0
Author:				Nathan Festoso
Date:				Jan 6, 2018
Purpose:			Display information of different types
***************************************************************/

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <Windows.h>
#include <string>
using namespace std;
#include "Display.h"
#include "GPUMemoryDisplay.h"
#include "SystemMemoryDisplay.h"

/***************************************************************
Function name:		Display
Purpose:			Constructor
In parameters:		x, y, duration, name
Out parameters:		Display object
Version:			1.0
Author:				Nathan Festoso
***************************************************************/
Display::Display(int x, int y, int duration, char* name) {
	pixel_x = x;
	pixel_y = y;
	this->duration = duration;
	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
}

/***************************************************************
Function name:		Display
Purpose:			Copy constructor
In parameters:		&d - Display to be copied
Out parameters:		Display object
Version:			1.0
Author:				Nathan Festoso
***************************************************************/
Display::Display(const Display& d) {
	pixel_x = d.pixel_x;
	pixel_y = d.pixel_y;
	duration = d.duration;
	name = new char[strlen(d.name) + 1];
	strcpy(name, d.name);
}

/***************************************************************
Function name:		operator<<
Purpose:			Allows for outputting display object
In parameters:		os - outputstream
					&d - display to be displayed
Out parameters:		os - output stream
Version:			1.0
Author:				Nathan Festoso
***************************************************************/
ostream& operator<<(ostream& os, Display& d) {
	os << "\tDisplay name = " << d.name << "; pixel_x = " << d.pixel_x 
		<< ", pixel_y = " << d.pixel_y << ", duration = " << d.duration << endl;
	
	// count duration
	os << "\tCounting the seconds for this Display: ";
	for (int i = 0; i < d.duration; i++) {
		os << i+1 << ", ";
		Sleep(1000);
	}
	os << endl << "\tMemory requirements = " << d.BufferSize() << " bytes" << endl;
	return os;
}
