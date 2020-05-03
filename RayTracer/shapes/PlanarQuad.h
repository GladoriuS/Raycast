/*
 * PlanarQuad.h
 *
 *
 */

#ifndef PLANARQUAD_H_
#define PLANARQUAD_H_

#include "core/Shape.h"
#include "core/RayHitStructs.h"
#include "math/geometry.h"
#include <vector>

namespace rt{

class PlanarQuad: public Shape{

public:


	//
	// Functions that need to be implemented, since Sphere is a subclass of Shape
	//
	PlanarQuad();
	PlanarQuad(Vec3f v0, Vec3f v1, Vec3f v2, Vec3f v3):v0(v0), v1(v1), v2(v2), v3(v3){};

	virtual ~PlanarQuad();

	Hit intersect(Ray ray);

	Vec3f getNormalAt(Vec3f point);
	
	Vec3f getCenter() {};

	std::vector<Vec3f> generatePoints(int samplesize);


	std::vector<Vec3f> getVertecies()
	{
		std::vector<Vec3f> verticies;
		verticies.push_back(v0);
		verticies.push_back(v1);
		verticies.push_back(v2);
		verticies.push_back(v3);
		return verticies;
	};

	bool isLeaf()
	{
		return false;
	};

	std::vector<Shape*> getShapes()
	{
		std::vector<Shape*> curShapes;
		curShapes.push_back(this);
		return curShapes; 
	};


private:

	Vec3f v0;
	Vec3f v1;
	Vec3f v2;
	Vec3f v3;
	Vec3f normal;


};



} //namespace rt




#endif /* PLANARQUAD_H_ */
