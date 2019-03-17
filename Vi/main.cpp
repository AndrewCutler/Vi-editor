#include <iostream>
#include <fstream>

#include "Command.h"
#include "Point.h"
#include "Editor.h"
#include "ArrayStack.h"

using namespace std;

int main() {
	//open file
	string filename = "sample.txt";

	//read file into editor
	Editor editor;
	editor.readFile(filename);

	//run editor
	editor.run();

	return 0;
}