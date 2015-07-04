/*
 * ModelReader.cpp
 *
 *  Created on: 15 июня 2015 г.
 *      Author: Сергей
 */

#include <FileSystem\ObjModelReader.h>
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

	 for (int i = 0; i < this->faces.size(); i++) {
		 std::cout << "f" << faces[i];
		 if ((i + 1) % 3 == 0) {
			 std::cout << std::endl;
		 }
	 }

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
		this->verticesNumber++;
		std::cout << "vv"<<vec<<"\n";

	}
	else if (line[0] == 'f') {
		std::cout << "ff";
		CVector3 vec;
		short result = parseFaces(line, vec);
	}
	else if (line[0] == 'o') {
		this->id = parseId(line);
	}

	std::cout<<line<<"\n";
}


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
		}
		// std::cout << token << std::endl;
		line.erase(0, pos + delimiter.length());
	} 
	vector.z = atof(line.c_str());
	// std::cout << line << std::endl;
	// std::cout << vector << std::endl;

	return EXIT_SUCCESS; 
}


short ObjModelReader::parseFaces(std::string line, CVector3& res) {
	std::string delimiter = " ";
	std::string internalDelimiter = "/";

	size_t pos = 0;
	size_t internalPos = 0;
	std::string token;
	std::string tokens;

	unsigned short pe;
	
	while ((pos = line.find(delimiter)) != std::string::npos) {
		pe = PREFIX;
		token = line.substr(0, pos);
		std::cout << token << std::endl;
		line.erase(0, pos + delimiter.length());
		
		if ((internalPos = token.find(internalDelimiter)) != std::string::npos) {
			do {
				tokens = token.substr(0, internalPos);

				std::cout << "ts::" << tokens << "::tn::" << token << std::endl;
				switch (++pe) {
				case PREFIX: break;
				case X: res.x = atof(tokens.c_str()); std::cout << "x<-" << tokens << "(" << res.x << ")\n"; break;
				case Y: res.y = atof(tokens.c_str()); std::cout << "z<-" << tokens << "(" << res.y << ")\n";  break;
				}
				std::cout << "t:" << tokens << std::endl;
				token.erase(0, internalPos + internalDelimiter.length());
			} while ((internalPos = token.find(internalDelimiter)) != std::string::npos);
		}
		else {
			continue;
		}
			
		std::cout << "ts::" << tokens << "::tn::" << token << std::endl;
		res.z = atof(token.c_str());
		std::cout << "z<-" << token << "(" << res.z << ")\n";
		std::cout << res << std::endl;
		this->faces.push_back(res);
		this->facesNumber++;
	}

	std::cout << "line::" + line << std::endl;
	std::cout << "token::" + token<<std::endl;
	token = line;
	pe = PREFIX;
	while ((internalPos = token.find(internalDelimiter)) != std::string::npos) {
		tokens = token.substr(0, internalPos);

		std::cout << "ts::" << tokens << "::tn::" << token << std::endl;
		switch (++pe) {
		case PREFIX: break;
		case X: res.x = atof(tokens.c_str()); std::cout << "x<-" << tokens << "(" << res.x << ")\n"; break;
		case Y: res.y = atof(tokens.c_str()); std::cout << "z<-" << tokens << "(" << res.y << ")\n";  break;
		}
		std::cout << "t:" << tokens << std::endl;
		token.erase(0, internalPos + internalDelimiter.length());
	}
	std::cout << "ts::" << tokens << "::tn::" << token << std::endl;
	res.z = atof(token.c_str());
	this->faces.push_back(res);
	this->facesNumber++;
	std::cout << "z<-" << token << "(" << res.z << ")\n";
	std::cout << res << std::endl;
	return EXIT_SUCCESS;
}

std::string ObjModelReader::parseId(std::string line) {
	std::string delimiter = " ";

	size_t pos = 0;
	std::string token;

	unsigned short pe = PREFIX;

	while ((pos = line.find(delimiter)) != std::string::npos) {
		token = line.substr(0, pos);
		line.erase(0, pos + delimiter.length());
		break;
	}
	std::cout << "id::" + line + "::id\n";
	return line.c_str();
}

//Model ObjModelReader::getModel() {
	// Model m;
	//m.
//}
