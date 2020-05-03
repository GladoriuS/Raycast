/*
 * ImageTexture.cpp
 *
 *
 */

#include "ImageTexture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"



namespace rt{

	// reference to : http://viclw17.github.io/2019/04/12/raytracing-uv-mapping-and-texturing/
	// using helper library to access file: https://github.com/nothings/stb/blob/master/stb_image.h

	ImageTexture::ImageTexture(float ks, float kd, int specularExponent, Vec3f diffuseColor, float reflection,const char* path, int width, int height):Material(ks, kd, specularExponent, diffuseColor,reflection)
	{
		this -> texWidth = width;
		this -> texHeight = height;
		int nn = 0;

		//std::string path2;
		this -> textureData = stbi_load(path, &texWidth, &texHeight, &nn, 0);
	}

	Vec3f ImageTexture::getColor(float RdotV, Vec3f lightSpec, Vec3f lightInt, float LdotN, Vec3f lightDiff, Vec3f lightAmpt, float u, float v)
	{
		this -> diffuseColor = getTextureColor(u,v);

		Vec3f specularColor = this -> ks * (powf(RdotV, this -> specularExponent))*lightSpec*lightInt;

		Vec3f phong = (this -> kd * LdotN * lightDiff * this -> diffuseColor * lightAmpt + specularColor);
		
		return phong;
	}

	Vec3f ImageTexture::getTextureColor(float u, float v)
	{

			int i = (    u)*texWidth;
			int j = (1 - v)*texHeight - 0.001;

			if (i < 0) i = 0;
			if (j < 0) j = 0;

			if (i > texWidth - 1) i = texWidth - 1;
			if (j > texHeight - 1) j = texHeight - 1;

			float r = int(textureData[3 * i + 3 * texWidth*j]  ) / 255.0;
			float g = int(textureData[3 * i + 3 * texWidth*j+1]) / 255.0;
			float b = int(textureData[3 * i + 3 * texWidth*j+2]) / 255.0;

			return Vec3f(r, g, b);
	}



} //namespace rt