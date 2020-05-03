/*
 * BVH.h
 *
 *
 */

#ifndef BVH_H_
#define BVH_H_

#include "core/Shape.h"
#include <vector>
#include "math/geometry.h"
#include "core/RayHitStructs.h"
#include "shapes/BoundingBox.h"

namespace rt{

class BVH: public Shape{


	public:

	//
	// Constructors
	//
	BVH(){};

	BVH(std::vector<Shape*> shapes);

	virtual ~BVH();


	//
	// Functions that need to be implemented, since Sphere is a subclass of Shape
	//
	Hit intersect(Ray ray);

	Vec3f getNormalAt(Vec3f point){return Vec3f(0.0);};

	std::vector<Vec3f> generatePoints(int samplesize){};

	std::vector<Vec3f> getVertecies() 
	{
		std::vector<Vec3f> verticies;
		return verticies;
	};

	bool isLeaf()
	{
		return false;
	};

	std::vector<Shape*> getShapes()
	{
		std::vector<Shape*> curShapes;
		return curShapes; 
	};

	// Builds the BVH tree and returns it's root component
	BoundingBox* buildTree(std::vector<BoundingBox*> bbs);



private:

	std::vector<Shape*> shapes;
	BoundingBox* root;

};



} //namespace rt



#endif /* BVH_H_ */
