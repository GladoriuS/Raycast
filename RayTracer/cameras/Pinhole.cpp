/*
 * Pinhole.cpp
 *
 *
 */
#include <iostream>

#include "Pinhole.h"



namespace rt{

	//
	// Pinhole constructor (example)
	//
	Pinhole::Pinhole(int width, int height, int fov, std::string type, Vec3f position, Vec3f look_at, Vec3f rotation):Camera(height, width, fov, type, position, look_at, rotation){
	// to fill

		// Calculating the direction, right and down unit vectors
		diff_btw = position - look_at;
		direction = (-diff_btw).normalize();
		right = (Vec3f(0.0,1.0,0.0).crossProduct(direction)).normalize();
		down = direction.crossProduct(right);

	}

	std::vector<Ray> Pinhole::getRay(float x,float y)
	{
		std::vector<Ray> rays;
		Ray ray;

		float curFov = fov*(M_PI/180.0);// fov converted in radians 

		ray.origin = position;
		ray.dir = ((direction + ((right * x)*curFov+ (down * y)*curFov))).normalize();

		rays.push_back(ray);
		return rays;
	}
	/**
	 * Prints camera data
	 * this function implements the abstract function of the base Camera class
	 */
	void Pinhole::printCamera(){
		printf("I am a pinhole camera! \n");
		printf("width: %dpx, height: %dpx, fov:%d, position:(%f,%f,%f), look_at:(%f,%f,%f)\n", width, height, fov, position[0], position[1], position[2], look_at[0], look_at[1], look_at[2]);
	}



} //namespace rt

