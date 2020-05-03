/*
 * AreaLight.cpp
 *
 *
 */
#include "AreaLight.h"



namespace rt{

	AreaLight::AreaLight(std::string type, Shape* shape, Vec3f intensity, Vec3f specular, Vec3f diffuse, float samplesize):LightSource(type, intensity, specular, diffuse){
		this -> shape = shape;
		this -> samplesize = samplesize;
	}


	std::vector<Vec3f> AreaLight::getSamples()
	{
		std::vector<Vec3f> points = shape -> generatePoints(samplesize);
		return points;
	}


} //namespace rt
