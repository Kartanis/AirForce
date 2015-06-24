/*
 * ModelReader.cpp
 *
 *  Created on: 15 июня 2015 г.
 *      Author: Сергей
 */

#include "ObjModelReader.h"
#include <iostream>
#include <fstream>

ObjModelReader::ObjModelReader() {
}

ObjModelReader::~ObjModelReader() {
	// TODO Auto-generated destructor stub
}

void ObjModelReader::load(std::string filename) {
	 std::ifstream modelFile;
	 modelFile.open (filename, std::ios::in);
	 std::string line;

	 if(!modelFile.is_open())
		 exit(1);

	 while (getline(modelFile, line)) {
		 ObjModelReader::parseLine(line);
	 }

	 modelFile.close();


}

void ObjModelReader::parseLine(std::string line) {
	
	if (line[0] == 'v' && line[1] == 'n') {
		std::cout << "nnnn";
		CVector3 vec;
		short result = parseVector(line, vec);
		this->normals.push_back(vec);
		std::cout << "vv" << vec << "\n";
	}
	else if (line[0] == 'v') {
		CVector3 vec;
		short result = parseVector(line, vec);
		this->vertices.push_back(vec);
		std::cout << "vv"<<vec<<"\n";

	}
	else if (line[0] == 'f') {
		std::cout << "ff";
		short result = parseFaces(line);
		// this->vertices.push_back(vec);
		
	}

	std::cout<<line<<"\n";
}

enum ParsingElement{
	PREFIX, X, Y, Z
};

short ObjModelReader::parseVector(std::string line, CVector3& vector) {
	std::string delimiter = " ";

	size_t pos = 0;
	std::string token;
	
	unsigned short pe = PREFIX;

	while ((pos = line.find(delimiter)) != std::string::npos) {
		token = line.substr(0, pos);
		switch (pe++) {
		case PREFIX: break;
		case X: vector.x = atof(token.c_str()); break;
		case Y: vector.y = atof(token.c_str()); break;
		case Z: vector.z = atof(token.c_str()); break;
		}
		// std::cout << token << std::endl;
		line.erase(0, pos + delimiter.length());
	} 
	vector.z = atof(line.c_str());
	// std::cout << line << std::endl;
	// std::cout << vector << std::endl;

	return EXIT_SUCCESS; 
}


short ObjModelReader::parseFaces(std::string line) {
	std::string delimiter = " ";
	std::string internalDelimiter = "/";

	size_t pos = 0;
	size_t internalPos = 0;
	std::string token;
	std::string tokens;

	unsigned short pe = PREFIX;

	while ((pos = line.find(delimiter)) != std::string::npos) {
		token = line.substr(0, pos);
		std::cout << token << std::endl;
		line.erase(0, pos + delimiter.length());
		while ((internalPos = token.find(internalDelimiter)) != std::string::npos) {
			tokens = token.substr(0, internalPos);
			std::cout << tokens << std::endl;
			token.erase(0, internalPos + internalDelimiter.length());
		}
		std::cout << token << std::endl;
	}
	
	while ((internalPos = line.find(internalDelimiter)) != std::string::npos) {
		tokens = line.substr(0, internalPos);
		std::cout << tokens << std::endl;
		line.erase(0, internalPos + internalDelimiter.length());
	}
	std::cout << line << std::endl;
	return EXIT_SUCCESS;
}