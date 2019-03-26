#pragma once
#include "Point.h"
class Snapshot
{
public:
	Snapshot();
	Snapshot(string, string,Point<int>);

	//getters
	string getData();
	string getCommand();

	//setters
	void setCommand(string);
	void setData(string, Point<int>);

	~Snapshot();
private:
	string changedData;
	string undoCommand;
	Point<int> location;
};

