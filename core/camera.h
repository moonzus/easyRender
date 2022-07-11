#pragma once
#include "maths.h"

class camera
{
public:
	Vector3D position, gazeAt, upView;
	float fov, aspect, near, far;

public:
	camera();
	camera(Vector3D pos, Vector3D gaze, Vector3D up, float cfov, float asp, float n, float f) :
		position(pos), gazeAt(gaze), upView(up), fov(cfov), aspect(asp), near(n), far(f) {};

	void rotateY(float angle);
};

