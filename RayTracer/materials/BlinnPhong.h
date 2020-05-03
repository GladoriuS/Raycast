/*
 * BlinnPhong.h
 *
 *
 */

#ifndef BLINNPHONG_H_
#define BLINNPHONG_H_

#include "core/Material.h"


namespace rt{

class BlinnPhong: public Material{
public:

	BlinnPhong(float ks, float kd, int specularExponent, Vec3f diffuseColor, float reflection);

	Vec3f getColor(float RdotV, Vec3f lightSpec, Vec3f lightInt, float LdotN, Vec3f lightDiff, Vec3f lightAmpt, float u, float v);


};



} //namespace rt



#endif /* BLINNPHONG_H_ */
