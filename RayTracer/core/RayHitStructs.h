/*
 * RayHitStructs.h
 */

#ifndef CORE_RAYHITSTRUCTS_H_
#define CORE_RAYHITSTRUCTS_H_

#include "math/geometry.h"

namespace rt{

/*
 * Ray structure definition
 */
enum RayType {PRIMARY, SECONDARY, SHADOW};

struct Ray{

	RayType raytype;

	//----------Ray variables to be filled------
	Vec3f origin;
	Vec3f dir;

};

class Shape;

struct Hit{
	//----------Hit variables to be filled------

	// boolean value to see if the ray intersected the shape
	bool intersected = false;
	// point of intersection
	Vec3f point;
	//distance to intersection
	float distance = INFINITY;
	//u,v coordinates for texture mapping
	float u,v;
	//shape properties of intersection
	Shape* shape;
	


};

}


#endif /* CORE_RAYHITSTRUCTS_H_ */
