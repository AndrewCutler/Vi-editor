#include "Snapshot.h"

Snapshot::Snapshot()
{
}

Snapshot::Snapshot(string command, string data) {
	undoCommand = command;
	changedData = data;
}

void Snapshot::setCommand(string command)
{
	undoCommand = command;
}

void Snapshot::setData(string data)
{
	changedData = data;
}


Snapshot::~Snapshot()
{
}
