/*
 * LightSource.cpp
 *
 */
#include "LightSource.h"
#include "lights/PointLight.h"
#include "lights/AreaLight.h"

namespace rt{

	LightSource::~LightSource(){};

	LightSource* LightSource::createLightSource(Value& lightSourceSpecs){

		//check if cameratype is defined
		if (!lightSourceSpecs.HasMember("type")){
			std::cerr<<"LightSource type not specified"<<std::endl;
			exit(-1);
		}

		std::string lightSourceType = lightSourceSpecs["type"].GetString();

		float intensityR = lightSourceSpecs["intensity"][0].GetDouble();
		float intensityG = lightSourceSpecs["intensity"][1].GetDouble();
		float intensityB = lightSourceSpecs["intensity"][2].GetDouble();

		float specularR = lightSourceSpecs["specular"][0].GetDouble();
		float specularG = lightSourceSpecs["specular"][1].GetDouble();
		float specularB = lightSourceSpecs["specular"][2].GetDouble();

		float diffuseR = lightSourceSpecs["diffuse"][0].GetDouble();
		float diffuseG = lightSourceSpecs["diffuse"][1].GetDouble();
		float diffuseB = lightSourceSpecs["diffuse"][2].GetDouble();


		//return camera object based on camera specs
		if (lightSourceType.compare("pointlight")==0){

			float posX =  lightSourceSpecs["position"][0].GetDouble();
			float posY =  lightSourceSpecs["position"][1].GetDouble();
			float posZ =  lightSourceSpecs["position"][2].GetDouble();

			return new PointLight(lightSourceType, Vec3f(posX,posY,posZ),Vec3f(intensityR,intensityG,intensityB), Vec3f(specularR,specularG,specularB), Vec3f(diffuseR,diffuseG,diffuseB));

		}else if (lightSourceType.compare("arealight")==0){

			Shape * shape = Shape::createShape(lightSourceSpecs["shape"]);
			int samplesize = lightSourceSpecs["samplesize"].GetInt();
			return new AreaLight(lightSourceType, shape, Vec3f(intensityR,intensityG,intensityB), Vec3f(specularR,specularG,specularB), Vec3f(diffuseR,diffuseG,diffuseB), samplesize);
		}

		return 0;

	}



} //namespace rt

