/*
 * Scene.cpp
 *
 */
#include "Scene.h"
#include "math/geometry.h"
#include "core/Shape.h"
#include "shapes/BVH.h"




namespace rt{

/**
 * Parses json scene object to generate scene to render
 *
 * @param scenespecs the json scene specificatioon
 */



	void Scene::createScene(Value& scenespecs){

	//----------parse json object to populate scene-----------

		// Getting the background color
		float backR = scenespecs["backgroundcolor"][0].GetDouble();
		float backG = scenespecs["backgroundcolor"][1].GetDouble();
		float backB = scenespecs["backgroundcolor"][2].GetDouble();

		backgroundColor = Vec3f(backR,backG,backB);

		// Getting the lightsources
		for (SizeType i = 0; i < scenespecs["lightsources"].Size(); ++i)
		{
			LightSource* lightSource=new LightSource();
			lightSource = lightSource -> createLightSource(scenespecs["lightsources"][i]);
			lightSources.push_back (lightSource);
		}

		// Getting the shapes in the scene
		for (SizeType i = 0; i < scenespecs["shapes"].Size(); ++i)
		{
			Shape* shape = Shape::createShape(scenespecs["shapes"][i]);
			shapes.push_back (shape);
		}

		//Creating the BVH trees
		Shape* shape = Shape::createBVH(shapes);
		BVH = shape;


}

void Scene::printScene(){
	printf("The scene has been created. \n");
	// printf("backgrounColor:(%f,%f,%f)\n", backgroundColor[0], backgroundColor[1], backgroundColor[2]);
	// printf("Number of lightsources: %d\n",lightSources.size());
	// printf("LightSource 1: position(%f,%f,%f)\n", lightSources.front()->getPosition()[0], lightSources.at(0)->getPosition()[1], lightSources.at(0)->getPosition()[2]);
	// printf("LightSource 1: intensity(%f,%f,%f)\n", lightSources[0] -> getIntensity()[0], lightSources.at(0)->getIntensity()[1], lightSources.at(0)->getIntensity()[2]);
	// printf("Shape material: %d \n", shapes[1]->getMaterial()->getSpecularExponent());
	// printf("Shape material: %d \n", shapes[1]->getMaterial()->getSpecularExponent());


}



} //namespace rt
