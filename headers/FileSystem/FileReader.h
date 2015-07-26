#pragma once
#include <string>
#include <fstream>
#include <exception>

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

class IOException : public std::exception {
private:
	const char* message;
public:
	IOException(const char* message) {
		this->message = message;
	}

	virtual const char* what() const throw() {
		return message;
	}

};