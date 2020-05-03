/*
 * Camera.h
 *
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include "rapidjson/document.h"
#include "math/geometry.h"
#include "core/RayHitStructs.h"
#include <vector>


using namespace rapidjson;

namespace rt{

class Camera{
public:

	//
	// Constructors
	//
	Camera(){};
	//Pinhole camera
	Camera(int height, int width, int fov, std::string type, Vec3f position, Vec3f look_at, Vec3f rotation):height(height), width(width), fov(fov), type(type), position(position), look_at(look_at), rotation(rotation){};
	//Thin lens camera
	Camera(int height, int width, int fov, std::string type, Vec3f position, Vec3f look_at, Vec3f rotation, float aperture, float focus_dist, float sample_size):height(height), width(width), fov(fov), type(type), position(position), look_at(look_at), rotation(rotation){};

	//
	// Destructor
	//
	virtual ~Camera();


	//
	// factory function : returns camera instance dynamically based on camera specifications
	//
	static Camera* createCamera(Value& cameraSpecs);


	//
	// print function (to be implemented by the subclasses )
	//
	virtual void printCamera()=0;


	
	virtual std::vector<Ray> getRay(float, float)=0;



	//
	// other camera functions (to complete)
	//














	//
	// Getters and Setters
	//
	int getHeight() const {
		return height;
	}

	void setHeight(int height) {
		this->height = height;
	}

	int getWidth() const {
		return width;
	}

	void setWidth(int width) {
		this->width = width;
	}

	int getFOV() const {
		return fov;
	}

	void setFOV(int fov) {
		this->fov = fov;
	}


	Vec3f getPosition() const {
		return position;
	}

	void setPosition(Vec3f position) {
		this ->position = position;
	}

	Vec3f getLookAt() const {
		return look_at;
	}

	void setLookAt(Vec3f look_at) {
		this -> look_at = look_at;
	}

	Vec3f getRotation() const {
		return rotation;
	}

	void setRotation(Vec3f look_at) {
		this -> rotation = rotation;
	}


	Vec3f getDirection() const {
		return direction;
	}

	Vec3f getRight() const {
		return right;
	}
	
	Vec3f getDown() const {
		return down;
	}

	std::string getType() const {
		return type;
	}

private:

	static Vec3f extractVector(Value& vectorData);

protected:

	//
	//camera members
	//
	int height;
	int width;
	int fov;
	std::string type;
	Vec3f position;
	Vec3f look_at;
	Vec3f rotation; // up
	Vec3f diff_btw;
	Vec3f direction;
	Vec3f right;
	Vec3f down;

};

} //namespace rt



#endif /* CAMERA_H_ */
