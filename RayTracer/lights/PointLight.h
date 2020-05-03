/*
 * PointLight.h
 *
 *
 */

#ifndef POINTLIGHT_H_
#define POINTLIGHT_H_

#include "core/LightSource.h"
#include "math/geometry.h"


namespace rt{

class PointLight:public LightSource{	
	public:

	//
	// Constructors
	//
	PointLight();
	PointLight(std::string type, Vec3f position, Vec3f intensity, Vec3f specular, Vec3f diffuse);

	//
	//Destructor
	//
	~PointLight(){};

	std::vector<Vec3f> getSamples(){};

};



} //namespace rt




#endif /* POINTLIGHT_H_ */
