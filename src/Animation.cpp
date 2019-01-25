/***************************************************************
Filename:			Animation.cpp
Version:			1.0
Author:				Nathan Festoso
Date:				Jan 6, 2018
Purpose:			Animation of frames
***************************************************************/

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <forward_list>
#include <vector>
#include <string>
#include <string.h>
using namespace std;
#include "Display.h"
#include "SystemMemoryDisplay.h"
#include "GPUMemoryDisplay.h"
#include "Frame.h"
#include "Animation.h"

/***************************************************************
Function name:		InsertFrame
Purpose:			Insert frames into list at specified index
In parameters:		-
Out parameters:		-
Version:			1.0
Author:				Nathan Festoso
***************************************************************/
void Animation::InsertFrame() {
	vector<Display*> displays;
	string file_name, shader;
	char display_name[25];
	int num_displays, x, y, duration, index, type;

	cout << "Insert a Frame in the Animation" << endl;
	cout << "Please enter the Frame filename: ";
	cin >> file_name; cout << endl;

	cout << "Entering the Frame Displays (the sets of dimensions and durations)" << endl;
	cout << "Please enter the number of Displays: ";
	cin >> num_displays; cout << endl;

	// set vector size
	displays.reserve(num_displays);

	// get displays for frame
	for (int i = 0; i < num_displays; i++) {
		cout << "Please enter pixel x-width for Display #0 pixel_x: "; cin >> x;
		cout << "Please enter pixel y-width for Display #0 pixel_y: "; cin >> y;
		cout << "Please enter the duration for this Display: "; cin >> duration;
		cout << "Please enter the name for this Display: "; cin >> display_name;
		cout << "Please enter the type for this Display (1 = SystemMemoryDisplay, 2 = GPU MemoryDisplay): "; cin >> type;
		if (type == 2) {
			cout << "Please enter the file name of the associated GPU Shader: "; cin >> shader;
		}
		cout << endl;
		// create display
		if (type == 1) {
			displays.push_back(new SystemMemoryDisplay(x, y, duration, display_name));
		}
		else if (type == 2) {
			displays.push_back(new GPUMemoryDisplay(x, y, duration, display_name, shader));
		}
		else {
			cout << "Display type must be 1 or 2" << endl << endl;
			return;
		}
	}

	// add frame
	if (frames.empty()) {
		// first frame
		cout << "This is the first Frame in the list" << endl << endl;
		frames.push_front(Frame(file_name, displays));
	}
	else {
		// insert at specific index
		forward_list<Frame>::iterator start = frames.begin();
		forward_list<Frame>::iterator end = frames.end();

		// second frame
		if (distance(start, end) < 2) {
			frames.push_front(Frame(file_name, displays));
		}
		else {
			// user specified index
			cout << "There are " << distance(start, end) << " frames in list" << endl;
			cout << "Please specify the position, between 0" << " and " << distance(start, end)-1 << " to insert after: ";
			cin >> index;

			// insert into list
			forward_list<Frame>::iterator insert = frames.begin();
			// increment iterator
			for (int i = 0; i < index; i++, insert++); 
			// insert frame
			frames.insert_after(insert, Frame(file_name, displays));
		}
		cout << endl;
	}
}

/***************************************************************
Function name:		DeleteFrames
Purpose:			Deletes all frams from animation
In parameters:		-
Out parameters:		-
Version:			1.0
Author:				Nathan Festoso
***************************************************************/
void Animation::DeleteFrames() {
	frames.clear();
}

/***************************************************************
Function name:		operator<<
Purpose:			Allows for printing animations
In parameters:		os - output stream
					A - current animation being used
Out parameters:		os - outputstream
Version:			1.0
Author:				Nathan Festoso
***************************************************************/
ostream& operator<<(ostream& os, Animation& A) {
	forward_list<Frame>::iterator it = A.frames.begin();

	os << "Animation " << A.name << endl;
	os << "Run the Animation";

	// print frames
	for (int i = 0; i < distance(A.frames.begin(), A.frames.end()); i++, it++) {
		os << endl << "Frame #" << i << ":\t";
		os << *it;
	}
	os << "Output finished" << endl;
	return os;
}
