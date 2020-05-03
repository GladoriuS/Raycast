/*
 * Triangle.cpp
 *
 *
 */
#include "Triangle.h"



namespace rt{

	
	Triangle::~Triangle()
	{}

	Vec3f Triangle::getNormalAt(Vec3f point)
	{
		 Vec3f u = v1-v0;
		 Vec3f v = v2-v0;

		 return -(u.crossProduct(v)).normalize();
	}

	std::vector<Vec3f> Triangle::generatePoints(int samplesize)
	{
		std::vector<Vec3f> points;
		
		float x,y;

		for(int i = 0; i< samplesize; i++)
		{
			x = drand48();
			y = drand48();

			Vec3f p = ((1-sqrt(x))*v0 + (sqrt(x)*(1-y))*v1 + (y*sqrt(x))*v2);

			points.push_back(p);
		}

		return points;
	}


	//reference to : https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/barycentric-coordinates
	// math reference to : https://www.mathopenref.com/heronsformula.html
	Hit Triangle::intersect(Ray ray){

		Hit h;
		//-----------to be implemented -------------
		h.intersected = false;

		// computing normal of the plane of the triangle
		float t;
		Vec3f P;
		Vec3f N;
		Vec3f u = v1-v0;
		Vec3f v = v2-v0;

		N = (u.crossProduct(v)).normalize();

		if(ray.dir.dotProduct(N) == 0.0f)
		{
			return h;
		}
		

		t = (v0 -ray.origin).dotProduct(N)/(ray.dir.dotProduct(N));

		if(t<-0.0001f)
		{
			return h;
		}

		P = ray.origin + (ray.dir * t);

		// Checking whether poin lies in the triangle by calculating the 3 separate triangle's area and comparing it with the area of the original one while accounting for the floating point error

		float l0,l1, l2;
		float s;
		float area, area0, area1, area2;

		//original area
		l0 = (v1 - v0).length();
		l1 = (v2 - v1).length();
		l2 = (v0 - v2).length();
		s = (l0 +l1+ l2)/2;

		area = sqrt(s*(s-l0)*(s-l1)*(s-l2));

		//triangle areas
		l0 = (v1- v0).length();
		l1 = (P - v1).length();
		l2 = (v0 - P).length();
		s = (l0 +l1+ l2)/2;

		area0 = sqrt(s*(s-l0)*(s-l1)*(s-l2));

		l0 = (v2- v1).length();
		l1 = (P - v2).length();
		l2 = (v1 - P).length();
		s = (l0 +l1+ l2)/2;

		area1 = sqrt(s*(s-l0)*(s-l1)*(s-l2));

		l0 = (v0- v2).length();
		l1 = (P - v0).length();
		l2 = (v2 - P).length();
		s = (l0 +l1+ l2)/2;

		area2 = sqrt(s*(s-l0)*(s-l1)*(s-l2));

		if(abs(area-(area0 + area1 + area2)) < 0.01f)
		{
        	h.intersected = true;
        	h.point = P;
        	h.u = (float)area0/area;
        	h.v = (float)area2/area;
        	h.distance = (P-ray.origin).length();
        	h.shape = this;
        	return h;
		}
		
		return h;

	}


} //namespace rt
