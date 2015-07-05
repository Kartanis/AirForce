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
#include <math/CVector3.h>

enum ParsingElement{
	PREFIX, X, Y, Z
};


class ObjModelReader {
public:
	ObjModelReader();
	virtual ~ObjModelReader();

	void load(std::string filename);
	void parseLine(std::string);

	int getVerticesNumber();
	int getFacesNumber();
	std::vector<CVector3> getVertices();
	std::vector<CVector3> getFaces();

private:
	std::string id;
	int verticesNumber;
	int verticesNormalsNumber;
	int facesNumber;

	std::vector<CVector3> vertices;
	std::vector<CVector3> normals;
	std::vector<CVector3> faces;

	short parseVector(std::string , CVector3 &vec);
	short parseFaces(std::string, CVector3& res);
	std::string parseId(std::string);
};

#endif /* SRC_FILESYESTEM_OBJMODELREADER_H_ */
