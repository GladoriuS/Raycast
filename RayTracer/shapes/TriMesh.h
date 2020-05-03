/*
 * TriMesh.h
 *
 *
 */

#ifndef TRIMESH_H_
#define TRIMESH_H_

#include "core/Shape.h"
#include "core/RayHitStructs.h"

namespace rt{

class TriMesh: public Shape{

public:


	TriMesh();

	virtual ~TriMesh();

	Hit intersect(Ray ray);

};



} //namespace rt




#endif /* TRIMESH_H_ */
