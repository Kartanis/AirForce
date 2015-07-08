/*
 * CVector.h
 *
 *  Created on: 15 июня 2015 г.
 *      Author: Сергей
 */

#ifndef SRC_CORE_CVECTOR3_H_
#define SRC_CORE_CVECTOR3_H_

#include <ostream>

class CVector3 {
public:
	CVector3();
	CVector3(float, float, float);
	virtual ~CVector3();

	float x, y, z;
	friend std::ostream& operator<<(std::ostream& os, const CVector3& vec);

	
};



#endif /* SRC_CORE_CVECTOR3F_H_ */
