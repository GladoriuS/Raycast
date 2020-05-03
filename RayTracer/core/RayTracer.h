/*
 * RayTracer.h
 *
 */
#ifndef RAYTRACER_H_
#define RAYTRACER_H_

#include "math/geometry.h"
#include "core/Camera.h"
#include "core/Scene.h"

namespace rt{



/*
 * Raytracer class declaration
 */
class RayTracer {
public:

	RayTracer();

	static Vec3f* render(Camera* camera, Scene* scene, int nbounces);
	static Vec3f* tonemap(Vec3f* pixelbuffer);


private:

	//gets the color of a pixel
	static Vec3f shade(Ray ray, Scene* scene, int nbounces);
	//ray trecing without BVH
	static Hit trace(Ray ray, Scene*scene);
	//ray tracing with BVH
	static Hit traceBVH(Ray ray, Scene*scene);
	// functions for arealight sampling using the first approach
	static Vec3f random_on_semisphere(Vec3f from, Vec3f normal);
	static std::vector<Ray> getShadowRays(Vec3f from, Vec3f);

};




} //namespace rt



#endif /* RAYTRACER_H_ */

