/*
 * PlanarQuad.cpp
 *
 *
 */
#include "PlanarQuad.h"



namespace rt{


	PlanarQuad::~PlanarQuad()
	{

	}
	
	Vec3f PlanarQuad::getNormalAt(Vec3f point)
	{
		Vec3f u = v1-v0;
		Vec3f v = v2-v0;

		return -(u.crossProduct(v)).normalize();
	}


	Hit PlanarQuad::intersect(Ray ray){

		Hit h;
		//-----------to be implemented -------------
		h.intersected = false;
		// // computing normal of the plane
		float denom;
		float t;
		Vec3f P;
		Vec3f N;

		Vec3f u = v1-v0;
		Vec3f v = v2-v0;

		// checks if ray paralell to the plane
		N = (u.crossProduct(v)).normalize();

		if(ray.dir.dotProduct(N) == 0.0f)
		{
			return h;
		}
		
		// if it is not calculates point on the plane
		t = (v0 -ray.origin).dotProduct(N)/(ray.dir.dotProduct(N));

		if(t<-0.0001f)
		{
			return h;
		}

		P = ray.origin + (ray.dir * t);

		//check if P inside the PlanarQuad using the trianle methode

		float l0,l1, l2;
		float s;
		float area, area0, area1, area2, area3;
		
		//original area
		area = (v1- v0).length()*(v0 - v3).length();



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

		l0 = (v3- v2).length();
		l1 = (P - v3).length();
		l2 = (v2 - P).length();
		s = (l0 +l1+ l2)/2;

		area2 = sqrt(s*(s-l0)*(s-l1)*(s-l2));

		l0 = (v0- v3).length();
		l1 = (P - v0).length();
		l2 = (v3 - P).length();
		s = (l0 +l1+ l2)/2;

		area3 = sqrt(s*(s-l0)*(s-l1)*(s-l2));

		if(abs(area-(area0 + area1 + area2 + area3)) < 0.01f)
		{
        	h.intersected = true;
        	h.point = P;
        	h.u = (float)area3/(area/2);
        	h.v = (float)area0/(area/2);
        	h.distance = (P-ray.origin).length();
        	h.shape = this;
        	return h;
		}

	}

	std::vector<Vec3f> PlanarQuad::generatePoints(int samplesize)
	{

		std::vector<Vec3f> points;
		Vec3f u = v1-v0;
		Vec3f v = v3 -v0;
		float x,y;

		for(int i = 0; i< samplesize; i++)
		{
			x = drand48();
			y = drand48();

			u = u * x;
			v = v * y;

			points.push_back(v0 + u + v);
		}

		return points;
	}


} //namespace rt
