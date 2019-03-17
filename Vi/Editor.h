#pragma once
#include "Point.h"
#include "ArrayStack.h"
#include "Command.h"
#include "Node.h"
#include "LinkedList.h"
#include <string>

class Editor
{
private:
	LinkedList<string> lines; //store lines
	Point<int> position;	//maintain cursor position
	ArrayStack<Command> undoStack;	//stack for undo commands


public:
	Editor();
	~Editor();
	void readFile(string); //read in lines from file
	void run(); //execute editor, run commands
	void display(); //output data
};

