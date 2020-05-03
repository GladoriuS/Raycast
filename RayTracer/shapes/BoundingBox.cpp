/*
 * BoundingBox.cpp
 *
 *
 */
#include "BoundingBox.h"
#include "shapes/PlanarQuad.h"


namespace rt{


	//reference to: https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-box-intersection

	BoundingBox::BoundingBox(std::vector<Shape*> shapes):shapes(shapes)
	{

		// if box only contains 1 shape -> it is a leaf
		this -> leaf = (shapes.size() == 1);

		// encloses the shapes into a box by claculating the max and min vertex coordinates
		for (std::vector<Shape*>::iterator iter = shapes.begin(); iter != shapes.end(); ++iter)
		{			
			Shape* shape = *iter;
			
			std::vector<Vec3f> v = shape -> getVertecies();

			for (std::vector<Vec3f>::iterator iter2 = v.begin(); iter2 != v.end(); ++iter2)
			{
				Vec3f p = *iter2;

				if(minExtend[0] > p[0])
					this -> minExtend[0] = p[0];

				if(minExtend[1] > p[1])
					this -> minExtend[1] = p[1];

				if(minExtend[2] > p[2])
					this -> minExtend[2] = p[2];

				if(maxExtend[0] < p[0])
					this -> maxExtend[0] = p[0];

				if(maxExtend[1] < p[1])
					this -> maxExtend[1] = p[1];

				if(maxExtend[2] < p[2])
					this -> maxExtend[2] = p[2];

			}
		}

		this -> center = (maxExtend+minExtend)*(0.5);
	}


	BoundingBox::~BoundingBox()
	{

	}

	// Calculating intersection by observing if the ray outside of the max and min coordinates
	Hit BoundingBox::intersect(Ray ray){

		Hit h;
		h.intersected = false;
		//-----------to be implemented -------------

		float tmin = (minExtend[0] - ray.origin[0]) / ray.dir[0]; 
	    float tmax = (maxExtend[0] - ray.origin[0]) / ray.dir[0]; 
	 
	    if (tmin > tmax)
	    	std::swap(tmin, tmax); 
	 
	    float tymin = (minExtend[1] - ray.origin[1]) / ray.dir[1]; 
	    float tymax = (maxExtend[1] - ray.origin[1]) / ray.dir[1]; 
	 
	    if (tymin > tymax)
	    	std::swap(tymin, tymax); 
	 
	    if ((tmin > tymax) || (tymin > tmax)) 
	        return h; 
	 
	    if (tymin > tmin) 
	        tmin = tymin; 
	 
	    if (tymax < tmax) 
	        tmax = tymax; 
	 
	    float tzmin = (minExtend[2] - ray.origin[2]) / ray.dir[2]; 
	    float tzmax = (maxExtend[2] - ray.origin[2]) / ray.dir[2]; 
	 
	    if (tzmin > tzmax)
	    	std::swap(tzmin, tzmax); 
	 
	    if ((tmin > tzmax) || (tzmin > tmax)) 
	        return h; 
	 
	    if (tzmin > tmin) 
	        tmin = tzmin; 
	 
	    if (tzmax < tmax) 
	        tmax = tzmax; 

	    h.intersected = true;
	    h.shape = this;
		return h;

	}


} //namespace rt