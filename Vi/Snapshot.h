#pragma once
#include "Point.h"
class Snapshot
{
public:
	Snapshot();
	Snapshot(string, string);
	void setCommand(string);
	void setData(string);
	~Snapshot();
private:
	string changedData;
	string undoCommand;
};

