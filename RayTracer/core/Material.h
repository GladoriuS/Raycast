/*
 * Material.h
 *
 */

#ifndef MATERIAL_H_
#define MATERIAL_H_

#include "math/geometry.h"

namespace rt{

class Material{
public:
	//
	//Constructors
	//
	Material(){};
	Material(float ks, float kd, int specularExponent, Vec3f diffuseColor, float reflection):ks(ks), kd(kd), specularExponent(specularExponent),diffuseColor(diffuseColor),reflection(reflection){};

	//returns the phong color/texture color of a pixel;
	virtual Vec3f getColor(float, Vec3f, Vec3f, float, Vec3f, Vec3f, float, float) =0;

	float getKs()
	{
		return ks;
	}
	float getKd()
	{
		return kd;
	}

	int getSpecularExponent()
	{
		return specularExponent;
	}

	Vec3f getDiffuseColor()
	{
		return diffuseColor;
	}

	float getReflection()
	{
		return reflection;
	}

protected:

	float ks;
	float kd;
	int specularExponent;
	Vec3f diffuseColor;
	float reflection;
};

} //namespace rt



#endif /* MATERIAL_H_ */
