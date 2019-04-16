#include "Editor.h"
#include <fstream>
#include "windows.h"
#include <conio.h>
#include "Point.h"
#include "Snapshot.h"
#include "BinarySearchTree.h"

/* ================ NON-EDITOR CLASS FUNCTIONS ================ */
void placeCursorAt(Point<int> coordinate) {
	COORD coord;
	coord.X = coordinate.getX();
	coord.Y = coordinate.getY();
	SetConsoleCursorPosition(
		GetStdHandle(STD_OUTPUT_HANDLE),
		coord);
}

void colorText(int value) {
	COORD coord;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	FlushConsoleInputBuffer(hConsole);
	SetConsoleTextAttribute(hConsole, value);
}

void visit(string& item) {
	cout << item << " ";
}

/* CONSTANTS */
const int BACKSPACE = 8;
const int RETURN = 13;
const int ESCAPE = 27;

/* ================ EDITOR CLASS FUNCTIONS ================ */
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

	//keywords into BST
	ifstream keywords("keywords.txt");
	string word;
	while (!keywords.eof()) {
		keywords >> word;
		keywordsBST.add(word);
	}

	string line; //currently selected line
	int nextLineLength = 0; //
	string nextLine;
	Point<int> dummyPosition;

	//snapshot
	Snapshot snap;

	//point in file where command takes place
	Point<int> place(0,0);

	//last command on undo stack
	Snapshot lastCommand;

	//input while in insert mode
	string input;

	//display();
	displayColors();

	char command = _getwch();

	while (command != 'q') { //q to quit for now
		command = _getwch();

		//switch statement for command
		switch (command) {
		case 'j': //move cursor down
			//only move down if eof not reached
			if (position.getY() < lines.getLength() - 1) {

				//go to end of line, save x-coord when jumping to shorter lines
				nextLine = lines.getEntry(position.getY() + 2);
				nextLineLength = nextLine.length();

				//if next line is shorter, go to end of it, saving cursor position
				if (nextLineLength < position.getX()) {
					dummyPosition.setX(nextLineLength - 1);
					dummyPosition.setY(position.getY() + 1);
					placeCursorAt(dummyPosition);
					position.setY(position.getY() + 1);
				}
				else {
				position.setY(position.getY() + 1);
				placeCursorAt(position);
				}

			}
			break;
		case 'k': //move cursor up
			if (position.getY() > 0) { //top boundary, never negative
				//go to end of line, save x-coord when jumping to shorter lines
				nextLine = lines.getEntry(position.getY());
				nextLineLength = nextLine.length();

				//if next line is shorter, go to end of it, saving cursor position
				if (nextLineLength < position.getX()) {
					dummyPosition.setX(nextLineLength - 1);
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
			if (position.getX() < lines.getEntry(position.getY() + 1).size() - 1 &&
				lines.getEntry(position.getY() + 1).size() > 0) {
				position.setX(position.getX() + 1);
				placeCursorAt(position);
			}
			break;
		case 'd':
			command = _getwch();
			if (command == 'd') {
				//add command and deleted line to undo stack
				snap.setCommand("dd");		//command code
				place.setY(position.getY() + 1);	//line number
				snap.setData(lines.getEntry(position.getY() + 1),place); //save data and line number
				undoStack.push(snap);

				//remove current line (+1 for 0-indexing)
				lines.remove(position.getY() + 1);
				break;
			}
			break;
		case 'x': //delete character
			//add command and deleted char to undo stack
			snap.setCommand("x");		//command code
			place.setX(position.getX());		//location of char in line
			place.setY(position.getY());		//location of line in file
			snap.setData(lines.getEntry(position.getY() + 1).substr(position.getX(), 1),place); //save data/location
			undoStack.push(snap);

			//delete character
			line = lines.getEntry(position.getY() + 1); //get current line
			line.erase(position.getX(), 1); //delete one character at cursor position
			lines.replace(position.getY() + 1, line); //replace original with modified line

			break;
		case'i'://insert into file
			while (input[0] != ESCAPE) { //esc to exit insert mode

				input = _getwch();

				if (input[0] != ESCAPE) {
					//get line at current cursor position
					line = lines.getEntry(position.getY() + 1);

					if (input[0] != 8) { //if input is not a backspace...
						//insert input into that line 
						line.insert(position.getX(), input);
						//move cursor to correct position, unless backspace
						position.setX(position.getX() + 1);
					}		

					//for backspace
					if (input[0] == BACKSPACE) {
						if (position.getX() > 0) {
							//erase one character, before cursor
							line.erase(position.getX() - 1,1);
							//save line
							position.setX(position.getX() - 1);
						}
					}

					//save line to file
					lines.replace(position.getY() + 1, line);

					//for return, create new node
					if (input[0] == RETURN) {
						//create and insert new node after current node
						lines.insert(position.getY() + 2, line.substr(position.getX(), line.length()));

						//cut current line and replace
						line = line.substr(0, position.getX() - 1);
						lines.replace(position.getY() + 1, line);

						//move cursor to start of next line
						position.setX(0);
						position.setY(position.getY() + 1);
					}

					//display();
					displayColors();
				}
			}
			input = ' ';
			break;
		case 'I':
			//move cursor to start of current line
			position.setX(0);
			placeCursorAt(position);

			while (input[0] != ESCAPE) {
				//get input
				input = _getwch();
				if (input[0] != ESCAPE) {
					//get line at current cursor position
					line = lines.getEntry(position.getY() + 1);

					if (input[0] != 8) { //if input is not a backspace...
										 //insert input into that line 
						line.insert(position.getX(), input);
						//move cursor to correct position, unless backspace
						position.setX(position.getX() + 1);
					}

					//for backspace
					if (input[0] == BACKSPACE) {
						if (position.getX() > 0) {
							//erase one character, before cursor
							line.erase(position.getX() - 1, 1);
							//save line
							position.setX(position.getX() - 1);
						}
					}

					//save line to file
					lines.replace(position.getY() + 1, line);

					//for return, create new node
					if (input[0] == RETURN) {
						//create and insert new node after current node
						lines.insert(position.getY() + 2, line.substr(position.getX(), line.length()));

						//cut current line and replace
						line = line.substr(0, position.getX() - 1);
						lines.replace(position.getY() + 1, line);

						//move cursor to start of next line
						position.setX(0);
						position.setY(position.getY() + 1);
					}

					//display();
					displayColors();
				}
			}

			input = " ";
			break;
		case 'u':
			//peek at undo stack
			if (!undoStack.isEmpty()) {
				lastCommand = undoStack.peek();

				if (lastCommand.getCommand() == "x") {
					//line determined by y-coord of position saved in snapshot + 1
					line = lines.getEntry(lastCommand.getLocation().getY() + 1);
					//insert removed char into line at x-coord position saved in snapshot
					line.insert(lastCommand.getLocation().getX(),undoStack.peek().getData());
					//replace line with undone data
					lines.replace(lastCommand.getLocation().getY() + 1, line);

					//remove last command
					undoStack.pop();

				}
				if (lastCommand.getCommand() == "dd") {
					//insert line with removed data at location saved in last command
					lines.insert(lastCommand.getLocation().getY(), lastCommand.getData());

					//place cursor at start of undeleted line
					position.setY(lastCommand.getLocation().getY() - 1);
					position.setX(0);

					//remove last command
					undoStack.pop();

				}
				if (lastCommand.getCommand() == "i") { 
					//save the entire file 
				}
			}

			break;
		default:
			break;
		}

		//display();
		displayColors();
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

void Editor::displayColors() {
	system("cls");

	bool isKeyword;
	string line;
	for (int i = 1; i < lines.getLength() + 1; i++) {
		line = lines.getEntry(i); //get current line
		int k = 0;
		//check line for keywords
		for (int j = 0; j < line.size(); j++) {
			if (tolower(line[j] >= 'a' && tolower(line[j]) <= 'z')) {
				string currentWord;
				for (k = j; (tolower(line[k]) >= 'a' && tolower(line[k]) <= 'z'); k++) {
					currentWord += line[k];
				}
				isKeyword = keywordsBST.contains(currentWord);
				if (!isKeyword) colorText(FOREGROUND_BLUE |  0xF0);
				else colorText(0 | 0xF0);
				cout << currentWord;
				if (k != 0) j = k - 1;
			}
			
			else {
				colorText(00 | 0xF0);
				cout << line[j];
			}
		}
		cout << endl;
	}

	placeCursorAt(position);
}

//TODO:
// color keywords work, background is not black
// add INSERT mode indicator at bottom
// undo for inserts