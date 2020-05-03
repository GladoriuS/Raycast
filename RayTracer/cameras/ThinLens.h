/*
 * ThinLens.h
 *
 */

#ifndef THINLENS_H_
#define THINLENS_H_

#include "core/Camera.h"
#include "math/geometry.h"


namespace rt{

class ThinLens:public Camera{
public:

	//
	// Constructors
	//
	ThinLens():Camera(){};
	ThinLens(int width, int height, int fov, std::string type, Vec3f position, Vec3f look_at, Vec3f rotation, float aperture, float focus_dist, float sample_size);

	//
	//Destructor
	//
	~ThinLens(){};

	//
	// print function (implementing abstract function of base class)
	//
	void printCamera();

	// Calculates the camera rays
	std::vector<Ray> getRay(float ndx, float ndy);

	// Generates random point on the lens
	Vec3f random_in_unit_disk();

private:
	float aspect;
	float aperture;
	float focus_dist;
	float lens_radius;
	float sample_size;
	Vec3f lower_left_corner;
	Vec3f horizontal;
	Vec3f vertical;

};



} //namespace rt




#endif /* THINLENS_H_ */
