/*
 * Triangle.h
 *
 *
 */

#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include "core/Shape.h"
#include "core/RayHitStructs.h"
#include "math/geometry.h"

namespace rt{

class Triangle: public Shape{

public:


	//
	// Functions that need to be implemented, since Sphere is a subclass of Shape
	//
	Triangle();
	Triangle(Vec3f v0, Vec3f v1, Vec3f v2):v0(v0), v1(v1), v2(v2){};

	virtual ~Triangle();

	Hit intersect(Ray ray);

	Vec3f getNormalAt(Vec3f point);

	std::vector<Vec3f> generatePoints(int samplesize);

	std::vector<Vec3f> getVertecies()
	{
		std::vector<Vec3f> verticies;
		verticies.push_back(v0);
		verticies.push_back(v1);
		verticies.push_back(v2);
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
	// Bayesian coordinate using as uv coordinates
	float b0;
	float b1;

};



} //namespace rt




#endif /* TRIANGLE_H_ */
