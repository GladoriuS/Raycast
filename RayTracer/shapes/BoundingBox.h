/*
 * BoundingBox.h
 *
 *
 */

#ifndef BoundingBox_H_
#define BoundingBox_H_

#include "core/Shape.h"
#include <vector>
#include "math/geometry.h"
#include "core/RayHitStructs.h"

namespace rt{

class BoundingBox: public Shape{


	public:

	//
	// Constructors
	//
	// AABB
	BoundingBox(){};

	BoundingBox(std::vector<Shape*> shapes);

	virtual ~BoundingBox();

	Hit intersect(Ray ray);

	Vec3f getNormalAt(Vec3f point){return Vec3f(0.0);};

	std::vector<Vec3f> generatePoints(int samplesize){};

	std::vector<Vec3f> getVertecies() 
	{
		std::vector<Vec3f> verticies;
		verticies.push_back(minExtend); //(x,y,z)
		verticies.push_back(Vec3f(minExtend[0],minExtend[1],maxExtend[2])); //(x,y,c)
		verticies.push_back(Vec3f(minExtend[0],maxExtend[1],minExtend[2])); //(x,b,z)
		verticies.push_back(Vec3f(minExtend[0],maxExtend[1],maxExtend[2])); //(x,b,c)
		verticies.push_back(Vec3f(maxExtend[0],minExtend[1],minExtend[2])); //(a,y,z)
		verticies.push_back(Vec3f(maxExtend[0],minExtend[1],maxExtend[2])); //(a,y,c)
		verticies.push_back(Vec3f(maxExtend[0],maxExtend[1],minExtend[2])); //(a,b,z)
		verticies.push_back(maxExtend);
		return verticies;
	};

	// Returns the shapes included in the bounding box
	std::vector<Shape*> getShapes()
	{
		return shapes;
	}

	// Returns the center coordinates of the bounding box
	Vec3f getCenter()
	{
		return center;
	};

	// Indeicates if the box is a leaf 
	bool isLeaf()
	{
		return leaf;
	} 


private:

	std::vector<Shape*> shapes;
	Vec3f maxExtend = Vec3f(-INFINITY);
	Vec3f minExtend = Vec3f(INFINITY);
	Vec3f center = Vec3f(0.0,0.0,0.0);
	bool leaf = false;


};



} //namespace rt



#endif /* BoundingBox_H_ */