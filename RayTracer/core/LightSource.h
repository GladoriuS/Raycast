/*
 * LightSource.h
 *
 */

#ifndef LIGHTSOURCE_H_
#define LIGHTSOURCE_H_

#include "rapidjson/document.h"
#include "math/geometry.h"
#include <vector>
#include "core/RayHitStructs.h"

using namespace rapidjson;

namespace rt{

class LightSource{
public:

	//
	// Constructor
	//
	LightSource(){};
	//Point Light
	LightSource(std::string type, Vec3f position, Vec3f intensity, Vec3f specular, Vec3f diffuse):type(type), position(position), intensity(intensity), specular(specular), diffuse(diffuse){};
	//AreaLight
	LightSource(std::string type, Vec3f intensity, Vec3f specular, Vec3f diffuse):type(type), intensity(intensity), specular(specular), diffuse(diffuse){};

	//
	// Destructor
	//
	virtual ~LightSource();

	//Gets random points on the surfuce of arealight, or the position of the point light
	virtual std::vector<Vec3f> getSamples(){};

	static LightSource* createLightSource(Value& lightSourceSpecs);


	//Getters and Setters

	Vec3f getPosition() const {
		return position;
	}

	Vec3f getIntensity() const {
		return intensity;
	}

	Vec3f getSpecular() const {
		return specular;
	}

	Vec3f getDiffuse() const {
		return diffuse;
	}

	std::string getType() const {
		return type;
	}

private:

protected:

	Vec3f position;
	Vec3f intensity;
	Vec3f specular;
	Vec3f diffuse;
	std::string type;

};

} //namespace rt



#endif /* LIGHTSOURCE_H_ */
