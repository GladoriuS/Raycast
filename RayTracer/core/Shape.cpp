/*
 * Shape.cpp
 *
 */
#include "Shape.h"
#include "shapes/Sphere.h"
#include "shapes/PlanarQuad.h"
#include "shapes/Triangle.h"
#include "shapes/BVH.h"
#include "materials/BlinnPhong.h"
#include "materials/ImageTexture.h"



namespace rt{


	Shape::~Shape()
	{}


	Shape* Shape::createShape(Value& shapeSpecs){
		
		if (!shapeSpecs.HasMember("type")){
			std::cerr<<"Shape type not specified"<<std::endl;
			exit(-1);
		}

		std::string shapeType = shapeSpecs["type"].GetString();

		float ks, kd, reflection;
		int specularexponent;
		Vec3f diffusecolor;
		int texWidth, texHeight;
		const char* path;

		// Extracting the material params
		if(shapeSpecs.HasMember("material"))
		{
			ks = shapeSpecs["material"]["ks"].GetDouble();
			kd = shapeSpecs["material"]["kd"].GetDouble();
			specularexponent = shapeSpecs["material"]["specularexponent"].GetInt();
			if(shapeSpecs["material"].HasMember("diffusecolor"))
			{
				diffusecolor = Vec3f(shapeSpecs["material"]["diffusecolor"][0].GetDouble(),shapeSpecs["material"]["diffusecolor"][1].GetDouble(),shapeSpecs["material"]["diffusecolor"][2].GetDouble());
			}
			reflection = shapeSpecs["material"]["reflection"].GetDouble();
		}

		// extracting the texture params
		bool textured = shapeSpecs.HasMember("texture");
		if(textured)
		{

			path = shapeSpecs["texture"]["path"].GetString();
			texWidth = shapeSpecs["texture"]["width"].GetInt();
			texHeight = shapeSpecs["texture"]["height"].GetInt();

		}

		//Creating a Sphere
		if (shapeType.compare("sphere")==0){

			float centerX =  shapeSpecs["center"][0].GetDouble();
			float centerY =  shapeSpecs["center"][1].GetDouble();
			float centerZ =  shapeSpecs["center"][2].GetDouble();

			float radius = shapeSpecs["radius"].GetDouble();

			Sphere* sphere = new Sphere(Vec3f(centerX,centerY,centerZ),radius);
			if(textured)
			{
				sphere -> setMaterial(new ImageTexture(ks, kd, specularexponent, diffusecolor, reflection, path, texWidth, texHeight));
			}
			else
			{
				sphere -> setMaterial(new BlinnPhong(ks, kd, specularexponent, diffusecolor, reflection));
			}
			return sphere;
		}

		//Creating a PlanarQuad
		if (shapeType.compare("planarquad")==0){

			float v0X =  shapeSpecs["v0"][0].GetDouble();
			float v0Y =  shapeSpecs["v0"][1].GetDouble();
			float v0Z =  shapeSpecs["v0"][2].GetDouble();

			float v1X =  shapeSpecs["v1"][0].GetDouble();
			float v1Y =  shapeSpecs["v1"][1].GetDouble();
			float v1Z =  shapeSpecs["v1"][2].GetDouble();

			float v2X =  shapeSpecs["v2"][0].GetDouble();
			float v2Y =  shapeSpecs["v2"][1].GetDouble();
			float v2Z =  shapeSpecs["v2"][2].GetDouble();

			float v3X =  shapeSpecs["v3"][0].GetDouble();
			float v3Y =  shapeSpecs["v3"][1].GetDouble();
			float v3Z =  shapeSpecs["v3"][2].GetDouble();


			PlanarQuad* plane = new PlanarQuad(Vec3f(v0X,v0Y,v0Z), Vec3f(v1X,v1Y,v1Z), Vec3f(v2X,v2Y,v2Z), Vec3f(v3X,v3Y,v3Z));
			if(textured)
			{
				plane -> setMaterial(new ImageTexture(ks, kd, specularexponent, diffusecolor, reflection, path, texWidth, texHeight));
			}
			else
			{
				plane -> setMaterial(new BlinnPhong(ks, kd, specularexponent, diffusecolor, reflection));
			}
			return plane;
		}

		// Creating a Triangle
		if (shapeType.compare("triangle")==0){

			float v0X =  shapeSpecs["v0"][0].GetDouble();
			float v0Y =  shapeSpecs["v0"][1].GetDouble();
			float v0Z =  shapeSpecs["v0"][2].GetDouble();

			float v1X =  shapeSpecs["v1"][0].GetDouble();
			float v1Y =  shapeSpecs["v1"][1].GetDouble();
			float v1Z =  shapeSpecs["v1"][2].GetDouble();

			float v2X =  shapeSpecs["v2"][0].GetDouble();
			float v2Y =  shapeSpecs["v2"][1].GetDouble();
			float v2Z =  shapeSpecs["v2"][2].GetDouble();



			Triangle* triangle = new Triangle(Vec3f(v0X,v0Y,v0Z), Vec3f(v1X,v1Y,v1Z), Vec3f(v2X,v2Y,v2Z));

			if(textured)
			{
				triangle -> setMaterial(new ImageTexture(ks, kd, specularexponent, diffusecolor, reflection, path, texWidth, texHeight));
			}
			else
			{
				triangle -> setMaterial(new BlinnPhong(ks, kd, specularexponent, diffusecolor, reflection));
			}
			return triangle;
		}

		return 0;
	}

	// Createing the BVH
	Shape* Shape::createBVH(std::vector<Shape*> shapes)
	{
		BVH* bvh = new BVH(shapes);
		return bvh;

		return 0;
	}

} //namespace rt

