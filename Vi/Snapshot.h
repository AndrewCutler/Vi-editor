#pragma once
#include "Point.h"
class Snapshot
{
public:
	Snapshot();
	~Snapshot();
private:
	Point<int> savedPosition;
	string savedValue;
	string savedCommand;
};

