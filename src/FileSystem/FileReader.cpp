#include <FileSystem\FileReader.h>
// #include <iostream>


FileReader::FileReader(std::string filename)
{
	this->filename = filename;
	
	this->file.open(filename, std::ios::in | std::ifstream::ate | std::ifstream::binary);
	

	if (!this->file.is_open())
		exit(1);

	file.close();
	this->length = this->file.tellg();
	this->file.open(filename, std::ios::in);
}


FileReader::~FileReader()
{
	if (file.is_open())
		file.close();
}


std::string FileReader::readLine(){
	std::string line;
	
	while (getline(this->file, line)) {
		return line;
	}
}

bool FileReader::writeLine(std::string line){
	return false;
}

bool FileReader::close() {
	if (file.is_open()) {
		file.close();
	}

	return true;
}

int FileReader::size() {
	return this->length;
}