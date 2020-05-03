/*
 * Shape.h
 *
 */

#ifndef SHAPE_H_
#define SHAPE_H_

#include "core/Material.h"
#include "rapidjson/document.h"
#include "math/geometry.h"
#include <vector>
#include "core/RayHitStructs.h"


using namespace rapidjson;

namespace rt{

class Shape{
public:

	static Shape *createShape(Value& shapeSpecs);

	static Shape *createBVH(std::vector<Shape*> shapes);

	Shape(){};

	virtual ~Shape();
	
	//
	// Shape abstract methods (to be implemented by subclasses)
	//

	virtual Hit intersect(Ray)=0;

	// Returns the normal vector to a shape at a specific point
	virtual Vec3f getNormalAt(Vec3f) =  0;

	// Generates points on the surfuce of the shape
	virtual std::vector<Vec3f> generatePoints(int) {};

	// Returns the vertecies of a shape
	// Used for BVH
	virtual std::vector<Vec3f> getVertecies() =  0;

	// Used for BVH
	virtual bool isLeaf() =  0;

	//Used for BVH
	virtual std::vector<Shape*> getShapes() =  0;

	void setMaterial(Material* material) {
		this->material = material;
	}

	Material* getMaterial() {
		return material;
	}


protected:

	Material* material;

};


} //namespace rt


#endif /* SHAPE_H_ */
