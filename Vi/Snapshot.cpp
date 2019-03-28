#include "Snapshot.h"

Snapshot::Snapshot()
{
}

Snapshot::Snapshot(string command, string data, Point<int> place) {
	undoCommand = command;
	changedData = data;
	location = place;
}

string Snapshot::getData()
{
	return changedData;
}

string Snapshot::getCommand()
{
	return undoCommand;
}

Point<int> Snapshot::getLocation()
{
	return location;
}

void Snapshot::setCommand(string command)
{
	undoCommand = command;
}

void Snapshot::setData(string data, Point<int> place)
{
	changedData = data;
	location = place;
}


Snapshot::~Snapshot()
{
}
