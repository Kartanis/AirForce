#pragma once
#include <string>
#include <fstream>
#include <exceptions/IOException.h>

class FileReader
{
private:
	std::string filename;
	std::ifstream file;
	int length;
public:
	FileReader(std::string filename);
	~FileReader();
	std::string readLine();
	int size();
	bool writeLine(std::string line);
	bool close();
};
