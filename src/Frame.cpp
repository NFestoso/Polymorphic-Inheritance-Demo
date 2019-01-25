/***************************************************************
Filename:			Frame.cpp
Version:			1.0
Author:				Nathan Festoso
Date:				Jan 6, 2018
Purpose:			Single animation Frame with multiple displays of certain types
***************************************************************/

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string> 
#include <vector>
using namespace std;
#include "Display.h"
#include "SystemMemoryDisplay.h"
#include "GPUMemoryDisplay.h"
#include "Frame.h"

/***************************************************************
Function name:		Frame
Purpose:			Copy constructor
In parameters:		&f - frame to be copied
Out parameters:		Frame object
Version:			1.0
Author:				Nathan Festoso
***************************************************************/
Frame::Frame(const Frame& f) {
	fileName = f.fileName;
	for (int i = 0; i < f.displays.size(); i++) {
		if ((dynamic_cast<GPUMemoryDisplay*>(f.displays[i])) != nullptr)
			displays.push_back(new GPUMemoryDisplay(*dynamic_cast<GPUMemoryDisplay*>(f.displays[i])));
		else
			displays.push_back(new SystemMemoryDisplay(*dynamic_cast<SystemMemoryDisplay*>(f.displays[i])));
	}
}

/***************************************************************
Function name:		operator<<
Purpose:			Allows for outputting frame
In parameters:		os - output stream
					&f - current frame being used
Out parameters:		os - outputstream
Version:			1.0
Author:				Nathan Festoso
***************************************************************/
ostream& operator<<(ostream& os, Frame& f) {
	GPUMemoryDisplay *g;

	// print frame
	os << "fileName = " << f.fileName << endl;

	// print display
	for (unsigned int i = 0; i < f.displays.size(); i++) {
		os << "\tDisplay #" << i << ": ";
		if ((g = dynamic_cast<GPUMemoryDisplay*>(f.displays[i])) != nullptr)
			os << "GPU Memory Display. Shader = " << g->GetShader() << endl;
		else
			os << "System Memory Display." << endl;
		os << *f.displays[i] << endl;
	}
	return os;
}