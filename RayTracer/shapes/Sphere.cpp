/*
 * Sphere.cpp
 *
 *
 */
#include "Sphere.h"


namespace rt{
	/**
	 * Computes whether a ray hit the specific instance of a sphere shape and returns the hit data
	 *
	 * @param ray cast ray to check for intersection with shape
	 *
	 * @return hit struct containing intersection information
	 *
	 */

	// reference to: https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-sphere-intersection

	Sphere::~Sphere()
	{

	}

	Vec3f Sphere::getNormalAt(Vec3f point)
	{
		return (-(center - point)).normalize();
	}

	// reference to: https://gamedev.stackexchange.com/questions/114412/how-to-get-uv-coordinates-for-sphere-cylindrical-projection
	std::vector<float> Sphere::getUV(Vec3f p)
	{

		std::vector<float> uvs;

		Vec3f n = (p - center).normalize();
		float u = atan2(n[0], n[2]) / (2*M_PI) + 0.5;
		float v = n[1] * 0.5 + 0.5;

		uvs.push_back(u);
		uvs.push_back(v);

		return uvs;
	}



	//reference to : http://viclw17.github.io/2018/07/16/raytracing-ray-sphere-intersection/
	Hit Sphere::intersect(Ray ray){

		Hit h;
		//-----------to be implemented -------------


		h.intersected =false;
		float t0, t1;

		Vec3f oc = ray.origin - center;
		float a = ray.dir.dotProduct(ray.dir);
    	float b = 2.0 * oc.dotProduct(ray.dir);
    	float c = oc.dotProduct(oc) - radius*radius;
    	float discriminant = b*b - 4*a*c;
    	if(discriminant < 0){
        	return h;//not intersection;
    	}
    	else{
    		//distance to first intersection (t0)
        	t0 = (-b - sqrt(discriminant)) / (2.0*a);
        	t1 = (-b + sqrt(discriminant)) / (2.0*a);

        	t0 = std::min(t0,t1);
        	// checks if the intesection is behind the camera
        	if(t0 > 0)
        	{

        		// point of intersection
        		Vec3f P1 = ray.origin+(ray.dir*t0);

        		std::vector<float> uvs = getUV(P1);
        		h.u = uvs[0];
        		h.v = uvs[1];
        		h.intersected = true;
        		h.point = P1;
        		h.distance = t0;
        		h.shape = this;
        		return h;

        	}
    	}

		return h;

	}

	std::vector<Vec3f> Sphere::generatePoints(int samplesize)
	{

		std::vector<Vec3f> points;

		for(int i = 0; i< samplesize; i++)
		{
			float rdx = (center[0]-radius) + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/((center[0]+radius)-(center[0]-radius))));
			float rdy = (center[1]-radius) + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/((center[1]+radius)-(center[1]-radius))));
			float rdz = (center[2]-radius) + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/((center[2]+radius)-(center[2]-radius))));

			points.push_back(Vec3f(rdx,rdy,rdz));
		}

		return points;
	}



} //namespace rt


