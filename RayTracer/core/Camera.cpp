/*
 * Camera.cpp
 *
 */
#include <iostream>

#include "Camera.h"
#include "cameras/Pinhole.h"
#include "cameras/ThinLens.h"

namespace rt{

	Camera::~Camera(){};



/**
 * Factory function that returns camera subclass based on camera specifications
 *
 * @param cameraSpecs camera specifications json object
 *
 * @return camera subclass instance
 *
 */
Camera* Camera::createCamera(Value& cameraSpecs){

	//check if cameratype is defined
	Vec3f campos;
	Vec3f camLookAt;
	Vec3f camRotation;


	if (!cameraSpecs.HasMember("type")){
		std::cerr<<"Camera type not specified"<<std::endl;
		exit(-1);
	}

	if(!cameraSpecs.HasMember("position"))
	{
		campos = Vec3f(0.0, 0.0, 0.0);
	}
	else
	{
		campos = Camera::extractVector(cameraSpecs["position"]);
	}

	if(!cameraSpecs.HasMember("look_at"))
	{
		camLookAt = Vec3f(1.0, 1.0, 1.0);
	}
	else
	{
		camLookAt = Camera::extractVector(cameraSpecs["look_at"]);
	}

	if(!cameraSpecs.HasMember("rotation"))
	{
		camRotation = Vec3f(0.0,1.0,0.0);
	}
	else
	{
		printf("here \n");
		camRotation = Camera::extractVector(cameraSpecs["Rotation"]);
	}

	std::string cameraType=cameraSpecs["type"].GetString();

	//return camera object based on camera specs
	if (cameraType.compare("pinhole")==0){


		//printf("width: %dpx, height: %dpx, fov:%d, position:(%f,%f,%f), look_at:(%f,%f,%f)\n", campos[0], campos[1], campos[2], camLookAt[0], camLookAt[1], camLookAt[2]);

		return new Pinhole(cameraSpecs["width"].GetInt(),
				cameraSpecs["height"].GetInt(),
				cameraSpecs["fov"].GetInt(),
				cameraType,
				campos,
				camLookAt,
				camRotation);

	}else if (cameraType.compare("thinlens")==0){
		
		float focus_dist = (campos -camLookAt).length();
		if(cameraSpecs.HasMember("focus_dist"))
		{
			focus_dist = cameraSpecs["height"].GetDouble();
		}

		return new ThinLens(cameraSpecs["width"].GetInt(),
				cameraSpecs["height"].GetInt(),
				cameraSpecs["fov"].GetInt(),
				cameraType,
				campos,
				camLookAt,
				camRotation,
				cameraSpecs["aperture"].GetDouble(),
				focus_dist,
				cameraSpecs["samplesize"].GetDouble());
	}		

	return 0;

}

Vec3f Camera::extractVector(Value& vectorData)
{
	float x = vectorData[0].GetDouble();
	float y = vectorData[1].GetDouble();
	float z = vectorData[2].GetDouble();

	return Vec3f(x,y,z);

}



} //namespace rt
