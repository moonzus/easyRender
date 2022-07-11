#include "Light.h"

Light::Light()
{
	intensity = Vector3D(300.f, 300.f, 300.f);
	position = Vector3D(18.f, 10.f, 5.f);
	ka = Vector3D(0.005f, 0.005f, 0.005f);
	ks = Vector3D(0.5f, 0.5f, 0.5f);
	ambLight = Vector3D(10.f, 10.f, 10.f);
	p = 150;
}
