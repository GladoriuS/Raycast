/*
 * ThinLens.cpp
 *
 *
 */
#include <iostream>


#include "ThinLens.h"


namespace rt{

	//
	// ThinLens constructor (example)
	//
	// reference to : https://www.realtimerendering.com/raytracing/Ray%20Tracing%20in%20a%20Weekend.pdf?fbclid=IwAR2D_Nyn-ALFxsdRsuWOqomjNeBtST-8mNGQjtFKJ_crz5NXhXxCG4e7J-Q

	ThinLens::ThinLens(int width, int height, int fov, std::string type, Vec3f position, Vec3f look_at, Vec3f rotation, float aperture, float focus_dist, float sample_size):Camera(height, width, fov, type, position, look_at, rotation){

		//to fill
		this -> aperture = aperture;
		this -> focus_dist = focus_dist;
		this -> aspect = width/height;
		this -> lens_radius = aperture/2;
		this -> sample_size = sample_size;

		float theta = (float)fov*M_PI/180.0;
		float half_height = std::tan(theta/2);
		float half_width = aspect * half_height;

		// Calculating the direction, right and down unit vectors
		direction = (position-look_at).normalize();
		right = -(Vec3f(0.0,1.0,0.0).crossProduct(direction)).normalize();
		down = -direction.crossProduct(right);

		// creating the pixel map
		lower_left_corner = position - half_width*focus_dist*down - half_height*focus_dist*right -focus_dist*direction;
		horizontal = 2* half_width*focus_dist*right;
		vertical = 2*half_height*focus_dist*down;
	}


	Vec3f ThinLens::random_in_unit_disk()
	{
		Vec3f p;
		do
		{
			
			p = 2.0 *Vec3f(drand48(),drand48(),0) - Vec3f(1.0,1.0,0.0);

		}while(p.dotProduct(p) >= 1.0 );
		return p;
	}

	// generates k(k = samplesize) point on the lens and shoots a ray through each of them
	std::vector<Ray> ThinLens::getRay(float i, float j)
	{
		Ray r;
		Vec3f rd;
		std::vector<Ray> rays;
		for(int k =0; k < sample_size; k++)
		{
			//point on lens
			rd = lens_radius * random_in_unit_disk();

			// Generating camera ray
			Vec3f offset = right* rd[0] + down* rd[1];
			r.origin = position+offset;
			r.dir = lower_left_corner + i*horizontal + j*vertical - position - offset;
			rays.push_back(r);
		}
		return rays;
	}

	/**
	 * Prints camera data
	 * this function implements the abstract function of the base Camera class
	 */
	void ThinLens::printCamera(){
		printf("I am a thin lens camera! \n");
		printf("width: %dpx, height: %dpx, fov:%d, position:(%f,%f,%f), look_at:(%f,%f,%f)\n", width, height, fov, position[0], position[1], position[2], look_at[0], look_at[1], look_at[2]);
	}

} //namespace rt
