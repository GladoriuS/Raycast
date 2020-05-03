/*
 * AreaLight.h
 *
 *
 */

#ifndef AREALIGHT_H_
#define AREALIGHT_H_

#include "core/LightSource.h"
#include "math/geometry.h"
#include "core/Shape.h"

namespace rt{

class AreaLight:public LightSource{
	public:

		//
		// Constructors
		//
		AreaLight(){};
		AreaLight(std::string type, Shape* shape, Vec3f intensity, Vec3f specular, Vec3f diffuse, float samplesize);

		//
		//Destructor
		//
		~AreaLight(){};

		//Generates sample point on the surfuce of the light
		std::vector<Vec3f> getSamples();

	private:
		Shape* shape;
		int samplesize;

};

} //namespace rt




#endif /* AREALIGHT_H_ */
