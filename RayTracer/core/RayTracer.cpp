/*
 * RayTracer.cpp
 *
 */
#include "RayTracer.h"
#include "math.h"


namespace rt{

/**
 * Performs ray tracing to render a photorealistic scene
 *
 * @param camera the camera viewing the scene
 * @param scene the scene to render, including objects and lightsources
 * @param nbounces the number of bounces to consider for raytracing
 *
 * @return a pixel buffer containing pixel values in linear RGB format
 */


	
int sizeOfPixelBuffer =0;

//finds closest hit, if there is any
Hit RayTracer::trace(Ray ray, Scene* scene)
{
	Hit hit;
	Hit curHit;
	std::vector<Shape*> shapes = scene -> getShapes();

	for (std::vector<Shape*>::iterator iter = shapes.begin(); iter != shapes.end(); ++iter)
	{			
		Shape* shape = *iter;
			
		curHit = shape -> intersect(ray);
		if(curHit.intersected == true && curHit.distance < hit.distance)
		{
			hit = curHit;
		}

	}

	return hit;
	
}

Hit RayTracer::traceBVH(Ray ray, Scene* scene)
{
	Hit hit;

	Shape* bvh = scene -> getBVH();

	hit = bvh -> intersect(ray);

	return hit;
}

//returns a random point on the hemisphere around a pixel
Vec3f RayTracer::random_on_semisphere(Vec3f from, Vec3f normal)
{
	Vec3f p;
	do
	{
		
		p = Vec3f( drand48(), drand48(), drand48());

	}while(p.dotProduct(normal) < 0.0 );
	return p;
}

//returns the shadow rays of a pixel
std::vector<Ray> RayTracer::getShadowRays(Vec3f from, Vec3f normal)
{
	std::vector<Ray> rays;
	Ray ray;

	for(int i =0; i < 5; i++)
	{
		ray.origin = from;
		ray.dir = (random_on_semisphere(from, normal)).normalize();

		rays.push_back(ray);
	}

	return rays;

}

//returns the shaded color of a pixel
// reference to https://www.scratchapixel.com/code.php?id=8&origin=%2Flessons%2F3d-basic-rendering%2Fray-tracing-overview&fbclid=IwAR2hViI8hOwwCG5LPLIqqxVfy25DsZoXaxiAgoBK1AioYQc5us1i85O3wow
Vec3f RayTracer::shade(Ray ray, Scene* scene, int nbounces)
{
	Vec3f color = scene -> getBackgroundColor();
	//Vec3f areaLightColor = scene -> getBackgroundColor();
	Hit hit;

	//hit = trace(ray, scene);
	hit = traceBVH(ray, scene);
	if(hit. intersected == false)
	{
		return color;
	}

	//Material
	float reflection  = hit.shape -> getMaterial() -> getReflection();


	//diffuse
	Vec3f L;
	Vec3f N;
	float LdotN;

	//specular
	Vec3f R;
	Vec3f V;
	float RdotV;
	float VdotN;

	//brightness
	Vec3f lightAmpt = Vec3f (0.0,0.0,0.0);
	// Vec3f lightAmptTemp = Vec3f (0.0,0.0,0.0);
	// Vec3f areaLightAmpt = Vec3f (0.0,0.0,0.0);
	Vec3f specularColor = Vec3f (0.0,0.0,0.0); 

	//shadow
	bool inShadow = false;
	Ray shadowRay;
	Hit shadowHit;

	//reflection
	Ray reflectRay;
	Vec3f reflectionColor = Vec3f(0.0,0.0,0.0);

	//vectors
	N = hit.shape -> getNormalAt(hit.point);
	V = -(ray.dir).normalize();

	//scalars
	VdotN = V.dotProduct(N);
	if(VdotN <0)
	{
		N=-N;
		VdotN =0;
	}



	R = (2 * (VdotN) * N - V).normalize();

	//reflection
	if(reflection > 0.0 && nbounces > 0)
	{
		if(R.dotProduct(N)>0)
		{
			reflectRay.origin = hit.point - 0.01f;
		}
		else
		{
			reflectRay.origin = hit.point + 0.0001f;
		}

		reflectRay.dir = R;
		reflectionColor = shade(reflectRay,scene,nbounces -1);
	}

	shadowRay.origin = V.dotProduct(N) < 0 ? hit.point - N*0.001f : hit.point + N*0.001f;

	//counter for sampling
	float counter = 0.0;

	std::vector<LightSource*> lightSources = scene -> getLightSources();
	for (std::vector<LightSource*>::iterator iter = lightSources.begin(); iter != lightSources.end(); ++iter)
	{
			
		LightSource* light = *iter;

		//Extracting the light params
		Vec3f lightDiff = light -> getDiffuse();
		Vec3f lightSpec = light -> getSpecular();
		Vec3f lightIntensity = light -> getIntensity();
		std::string lightType = light -> getType();

		if(lightType == "pointlight")
		{
			Vec3f lightPos = light -> getPosition();

			L = lightPos - hit.point;
			L = L.normalize();
			LdotN = std::max(0.0f,L.dotProduct(N));

			//getting shadows
			shadowRay.dir = L;
			//shadowHit = trace(shadowRay, scene);
			shadowHit = traceBVH(shadowRay, scene);
			bool inShadow = shadowHit.intersected == true && (shadowHit.point - shadowRay.origin).length() < (lightPos-shadowRay.origin).length(); 
			lightAmpt = lightAmpt + (1-inShadow) * lightIntensity * LdotN;

			R = (2 * (LdotN) * N - L).normalize();
			RdotV = R.dotProduct(V);

			// Getting the phong color
			Vec3f phong = hit.shape -> getMaterial() -> getColor(RdotV, lightSpec, lightIntensity, LdotN, lightDiff, lightAmpt, hit.u, hit.v);
			color = color + (reflectionColor*reflection + phong*(1-reflection));
		}
		else if(lightType == "arealight")
		{
			std::vector<Vec3f> tartgets = light -> getSamples();
			Vec3f areaLightColor = scene -> getBackgroundColor();

			//temp values for shadow intensity
			Vec3f lightAmptTemp = Vec3f (0.0,0.0,0.0);
			Vec3f areaLightAmpt = Vec3f (0.0,0.0,0.0);

			for (std::vector<Vec3f>::iterator iter = tartgets.begin(); iter != tartgets.end(); ++iter)
			{			
				Vec3f target = *iter;

				L = target - hit.point;
				L = L.normalize();
				LdotN = std::max(0.0f,L.dotProduct(N));

				shadowRay.dir = L;
				shadowHit = traceBVH(shadowRay, scene);

				bool inShadow = shadowHit.intersected == true && (shadowHit.point - shadowRay.origin).length() < (target-shadowRay.origin).length(); 
				areaLightAmpt = lightAmpt + (1-inShadow) * lightIntensity * LdotN;
				lightAmptTemp = lightAmptTemp + (1-inShadow) * lightIntensity * LdotN;

				R = (2 * (LdotN) * N - L).normalize();
				RdotV = std::max(0.0f,R.dotProduct(V));

				Vec3f phong = hit.shape -> getMaterial() -> getColor(RdotV, lightSpec, lightIntensity, LdotN, lightDiff, areaLightAmpt, hit.u, hit.v);
				areaLightColor = areaLightColor + (reflectionColor*reflection + phong*(1-reflection));

				counter++;
			}

			//averaging the color values after area light sampleing
			lightAmpt = lightAmpt + lightAmptTemp*(1/counter);
			color = color + areaLightColor*(1/counter);
		}
	}

	return color;

}

// reference to https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-generating-camera-rays/generating-camera-rays
// reference to https://www.youtube.com/watch?v=k_aRiYSXcyo&list=PLHm_I0tE5kKPPWXkTTtOn8fkcwEGZNETh
Vec3f* RayTracer::render(Camera* camera, Scene* scene, int nbounces){

 	float const pi = 3.14159265358979323846264338327950288419716939937510582097494459230781640628620899862803482534211706798214808651328230664709384460955;

	int height = camera->getHeight();
	int width = camera->getWidth();
	float aspectRatio = (float)width/(float)height;
	float fov = camera->getFOV();
	fov = fov*(pi/180.0);// fov converted in radians 

	sizeOfPixelBuffer = width*height;
	Vec3f* pixelbuffer=new Vec3f[camera->getWidth()*camera->getHeight()];

	//----------main rendering function to be filled------

	int index =0;

	Ray ray;
	std::vector<Ray> rays;

	float ndcx, ndcy; //normalized device coardinates for pixels
	float pixelScreenX, pixelScreenY; // mapping them into the range[-1,1] 

	if(camera -> getType() =="pinhole")
	{
		for(int x =0; x <  width; x++)
		{
			for(int y = 0; y < height ; y++)
			{
				//index for the pixels
				index = y*camera->getWidth() + x;

				ndcx = (x+0.5)/width;
				ndcy = (y+0.5)/height;

				pixelScreenX = 2 * ndcx -1;
				pixelScreenY = 1 - 2 * ndcy;

				if(width > height)
				{
					pixelScreenX = pixelScreenX * aspectRatio;
				}
				if(height > width)
				{
					pixelScreenY = pixelScreenY/aspectRatio;
				}

				// ray.origin = camera -> getPosition();
				// ray.dir = ((camera -> getDirection() + ((camera -> getRight() * pixelScreenX)*fov+ (camera -> getDown() * pixelScreenY)*fov))).normalize();

				rays = camera -> getRay(pixelScreenX,pixelScreenY);
				ray = rays[0];

				pixelbuffer[index] = shade(ray, scene, nbounces);

			}
		}
	}
	else if(camera -> getType() =="thinlens")
	{
		for(int y = height-1; y >=0 ; y--)
		{
			for(int x = 0; x< width; x++)
			{
				//printf("here \n", fov);
				index = y*camera->getWidth() + x;

				ndcx = (x+0.5)/width;
				ndcy = (y+0.5)/height; 

				pixelScreenX = 2 * ndcx - 0.5;
				pixelScreenY = 1.5 - 2 * ndcy;

				rays = camera -> getRay(pixelScreenX,pixelScreenY);

				int counter = 0.0;
				Vec3f color;
				for (std::vector<Ray>::iterator iter = rays.begin(); iter != rays.end(); ++iter)
				{			
					ray = *iter;
					color = color + shade(ray, scene, nbounces);
					counter++;
				}
				color = color * (1.0/counter);
				pixelbuffer[index] = color;
			}
		}
	}

	return pixelbuffer;

}



/**
 * Tonemaps the rendered image (conversion of linear RGB values [0-1] to low dynamic range [0-255]
 *
 * @param pixelbuffer the array of size width*height containing linear RGB pixel values
 *
 * @return the tonemapped image
 */
Vec3f* RayTracer::tonemap(Vec3f* pixelbuffer){

	//---------tonemapping function to be filled--------

	printf("Tonemap starts \n");
	for(SizeType i = 0; i< sizeOfPixelBuffer; i++)
	{
		if((pixelbuffer[i][0] * 255) > 255.0)
		{
			pixelbuffer[i][0] = 255;
		}
		else
		{
			pixelbuffer[i][0] *= 255;
		}

		if((pixelbuffer[i][1] * 255) > 255.0)
		{
			pixelbuffer[i][1] = 255;
		}
		else
		{
			pixelbuffer[i][1] *= 255;
		}

		if((pixelbuffer[i][2] * 255) > 255.0)
		{
			pixelbuffer[i][2] = 255;
		}
		else
		{
			pixelbuffer[i][2] *= 255;
		}
	}
	printf("Tonemap finishes \n");
	return pixelbuffer;

}





} //namespace rt


