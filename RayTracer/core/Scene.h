/*
 * Scene.h
 *
 */

#ifndef SCENE_H_
#define SCENE_H_

#include <vector>

#include "rapidjson/document.h"
#include "math/geometry.h"

#include "core/LightSource.h"
#include "core/Shape.h"


using namespace rapidjson;

namespace rt{

class Scene {
public:

	Scene(){};

	void createScene(Value& scenespecs);

	//Getters and Setters
	std::vector<Shape*> getShapes() const {
		return shapes;
	}

	std::vector<LightSource*> getLightSources() const {
		return lightSources;
	}

	Vec3f getBackgroundColor() const {
		return backgroundColor;
	}

	Shape* getBVH() const {
		return BVH;
	}

	void printScene();

private:

	std::vector<LightSource*> lightSources;
	std::vector<Shape*> shapes;
	Shape* BVH;
	Vec3f backgroundColor;

};

} //namespace rt



#endif /* SCENE_H_ */
