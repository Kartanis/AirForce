/*
 * ModelReader.h
 *
 *  Created on: 15 июня 2015 г.
 *      Author: Сергей
 */
#ifndef SRC_FILESYESTEM_OBJMODELREADER_H_
#define SRC_FILESYESTEM_OBJMODELREADER_H_

#include <string>
#include <vector>
#include "../model/Model.h"
#include "../Core/CVector3.h"

class ObjModelReader {
public:
	ObjModelReader();
	virtual ~ObjModelReader();

	void load(std::string filename);
	void parseLine(std::string);

private:
	int verticesNumber;
	int verticesNormalsNumber;
	int facesNumber;

	std::vector<CVector3> vertices;
	std::vector<CVector3> normals;
	std::vector<CVector3> faces;

	short parseVector(std::string , CVector3 &vec);
	short parseFaces(std::string);
};

#endif /* SRC_FILESYESTEM_OBJMODELREADER_H_ */
