/*
 * ImageTexture.h
 *
 *
 */

#ifndef IMAGETEXTURE_H_
#define IMAGETEXTURE_H_

#include "core/Material.h"


namespace rt{

class ImageTexture: public Material{
public:

	ImageTexture(float ks, float kd, int specularExponent, Vec3f diffuseColor, float reflection, const char* path, int width, int height);

	// Returns shaded color
	Vec3f getColor(float RdotV, Vec3f lightSpec, Vec3f lightInt, float LdotN, Vec3f lightDiff, Vec3f lightAmpt, float u, float v);

	// maps pixel to texture coordinate and returns texture color
	Vec3f getTextureColor(float u, float v);

private:

	unsigned char *textureData;
	int texWidth;
	int texHeight;
};



} //namespace rt



#endif /* IMAGETEXTURE_H_ */