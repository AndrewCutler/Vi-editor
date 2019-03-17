#pragma once
#include <string>

class Command
{
private:
	std::string commandCode;

public:
	Command();
	Command(std::string);
	~Command();
};

