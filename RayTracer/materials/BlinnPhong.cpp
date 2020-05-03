/*
 * BlinnPhong.cpp
 *
 *
 */

#include "BlinnPhong.h"



namespace rt{

	BlinnPhong::BlinnPhong(float ks, float kd, int specularExponent, Vec3f diffuseColor, float reflection):Material(ks, kd, specularExponent, diffuseColor,reflection)
	{

	}

	// reference to: https://www.scratchapixel.com/code.php?id=8&origin=%2Flessons%2F3d-basic-rendering%2Fray-tracing-overview&fbclid=IwAR2hViI8hOwwCG5LPLIqqxVfy25DsZoXaxiAgoBK1AioYQc5us1i85O3wow
	// Return the phon color
	Vec3f BlinnPhong::getColor(float RdotV, Vec3f lightSpec, Vec3f lightInt, float LdotN, Vec3f lightDiff, Vec3f lightAmpt, float u, float v)
	{
		//calculates specular color
		Vec3f specularColor = this -> ks * (powf(RdotV, this -> specularExponent))*lightSpec*lightInt;

		Vec3f phong = (this -> kd * LdotN * lightDiff * this -> diffuseColor * lightAmpt + specularColor);

		return phong;
	}


} //namespace rt
