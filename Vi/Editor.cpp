#include "Editor.h"
#include <fstream>
#include "windows.h"
#include <conio.h>
#include "Point.h"


void placeCursorAt(Point<int> coordinate) {
	COORD coord;
	coord.X = coordinate.getX();
	coord.Y = coordinate.getY();
	SetConsoleCursorPosition(
		GetStdHandle(STD_OUTPUT_HANDLE),
		coord);
}

Editor::Editor()
{
}


Editor::~Editor()
{
}

void Editor::readFile(string filename)
{
	ifstream inFile(filename);
	string line;
	int lineNumber = 1;
	if (inFile.is_open()) {
		while (!inFile.eof()) {
			getline(inFile, line);
			lines.insert(lineNumber,line);
			lineNumber++;
		}
	}
}

void Editor::run()
{	
	//initialize cursor position
	position.setX(0);
	position.setY(0);

	string line;
	int currentPosition, lineAboveLength = 0;
	string lineAbove;
	Point<int> dummyPosition;


	display();
	char command = _getwch();
	while (command != 'q') { //q to quit for now
		command = _getwch();

		//switch statement for command
		switch (command) {
		case 'j': //move cursor down
				  //cannot move below end of file
				  //size of file is lines.itemCount (minus 1 because of 0-indexing)
			if (position.getY() < lines.getLength() - 1) {
				position.setY(position.getY() + 1);
				placeCursorAt(position);
			}
			break;
		case 'k': //move cursor up
			if (position.getY() > 0) { //top boundary, never negative
				currentPosition = position.getX();
				lineAbove = lines.getEntry(position.getY());
				lineAboveLength = lineAbove.length();
				if (lineAboveLength < currentPosition) {
					dummyPosition.setX(lineAboveLength - 1);
					dummyPosition.setY(position.getY() - 1);
					placeCursorAt(dummyPosition);
					position.setY(position.getY() - 1);
				}
				else {
					position.setY(position.getY() - 1);
					placeCursorAt(position);
				}
			}
			break;
		case 'h': //move cursor left
			if (position.getX() > 0) { //left boundary, never negative
				position.setX(position.getX() - 1);
				placeCursorAt(position);
			}
			break;
		case 'l': //move cursor right
				  //cannot move right past size of current line
				  //current line accessed with: lines.getEntry(position) where position is cursor's Y-value + 1
				  //lines.getEntry(position) - 1 because of 0-indexing
			if (position.getX() < lines.getEntry(position.getY() + 1).size() - 1) {
				position.setX(position.getX() + 1);
				placeCursorAt(position);
			}
			break;
		case 'd':
			command = _getwch();
			//how to get second 'd' input?
			if (command == 'd') {
				//remove current line (+1 for 0-indexing)
				lines.remove(position.getY() + 1);
				display();
				break;
			}
			break;
		case 'x': //delete character
			line = lines.getEntry(position.getY() + 1); //get current line
			line.erase(position.getX(), 1); //delete one character at cursor position
			lines.replace(position.getY() + 1, line); //replace original with modified line
			display();
			break;
		default:
			break;
		}
	}
}

void Editor::display() //output data
{
	system("cls");
	int lineNumber = 1;
	while (lineNumber <= lines.getLength()) {
		cout << lines.getEntry(lineNumber) << endl;
		lineNumber++;
	}

	placeCursorAt(position);
}

/*
	TODO:
		- move cursor to end of shorter lines when moving udown (but preserve original X value) -- UP IS DONE
		- change DD command to use _getwch()
*/