#include "Command.h"
#include <string>


Command::Command()
{
}

Command::Command(std::string com) {
	commandCode = com;

}


Command::~Command()
{
}
