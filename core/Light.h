#pragma once
#include "maths.h"

class Light
{
public:
	Vector3D intensity;
	Vector3D position;
	Vector3D ka;
	Vector3D kd;
	Vector3D ks;
	Vector3D ambLight;
	float p;

public:
	Light();
	~Light() = default;
};

