/*
 * Pinhole.h
 *
 *
 */

#ifndef PINHOLE_H_
#define PINHOLE_H_

#include "core/Camera.h"
#include "math/geometry.h"

namespace rt{

class Pinhole:public Camera{
public:

	//
	// Constructors
	//
	Pinhole();
	Pinhole(int width, int height, int fov, std::string type, Vec3f position, Vec3f look_at, Vec3f rotation);

	//
	//Destructor
	//
	~Pinhole(){};

	//
	// print function (implementing abstract function of base class)
	//
	void printCamera();
	
	// Calculates the camera rays
	std::vector<Ray> getRay(float ndx,float ndy);
};



} //namespace rt




#endif /* PINHOLE_H_ */
