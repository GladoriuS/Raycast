/*
 * Sphere.h
 *
 *
 */

#ifndef SPHERE_H_
#define SPHERE_H_

#include "core/Shape.h"
#include "math/geometry.h"
#include "core/RayHitStructs.h"
#include <vector>

namespace rt{

class Sphere:public Shape{

public:

	//
	// Constructors
	//
	Sphere(){};

	Sphere(Vec3f center, float radius):center(center), radius(radius){};

	virtual ~Sphere();


	//
	// Functions that need to be implemented, since Sphere is a subclass of Shape
	//
	Hit intersect(Ray ray);

	Vec3f getNormalAt(Vec3f point);

	std::vector<Vec3f> generatePoints(int samplesize);

	// Calculates the uv coordinates on a sphere
	std::vector<float> getUV(Vec3f p);

	Vec3f getCenter()
	{
		Vec3f v;
		v[0] = center[0]  ;
		v[1] = center[1]  ;
		v[2] = center[2]  ;
		return v;
	};

	// Builds a box around the shpere and returns the vertecies of that box
	// reference to https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-sphere-intersection 
	std::vector<Vec3f> getVertecies() 
	{
		std::vector<Vec3f> verticies;
		verticies.push_back(center + radius*Vec3f( 1, 1, 1));
		verticies.push_back(center + radius*Vec3f( 1, 1,-1));
		verticies.push_back(center + radius*Vec3f( 1,-1, 1));
		verticies.push_back(center + radius*Vec3f( 1,-1,-1));
		verticies.push_back(center + radius*Vec3f(-1, 1, 1));
		verticies.push_back(center + radius*Vec3f(-1, 1,-1));
		verticies.push_back(center + radius*Vec3f(-1,-1, 1));
		verticies.push_back(center + radius*Vec3f(-1,-1,-1));

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

	Vec3f center;
	float radius;

};



} //namespace rt




#endif /* SPHERE_H_ */
