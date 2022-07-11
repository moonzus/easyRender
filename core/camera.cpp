#include "camera.h"

camera::camera()
{
	position = Vector3D(0, 3, 12);
	gazeAt = Vector3D(0, 0, 0);
	upView = Vector3D(0, 1, 0);
	fov = 45;
	aspect = 1280.0f / 880;
	near = 0.1f;
	far = 50.f;
}


void camera::rotateY(float angle)
{
	Vector4D tmp, tmp2;
	tmp = position;
	tmp2 = upView;
	Matrix4D rotation;
	rotation.rotationY(angle);
	tmp = rotation * tmp;
	tmp2 = rotation * tmp2;
	position.x = tmp.x;
	position.y = tmp.y;
	position.z = tmp.z;
}
