#include "baseShader.h"

simpleShader::simpleShader()
{
	modelMatrix.normalize();
	viewMatrix.normalize();
	projectionMatrix.normalize();
	rotationY.rotationY(0.05f);
	texture01 = new textures();
	texture02 = new textures();
	texture03 = new textures();
	texture04 = new textures();
	QString path1 = QString("D:/C++project/easySoftRender/easySoftRender/model/african_head_eye_inner_diffuse.jpg");
	QString path2 = QString("D:/C++project/easySoftRender/easySoftRender/model/ground.jpg");
	QString path3 = QString("D:/C++project/easySoftRender/easySoftRender/model/african_head_diffuse512.jpg");
	QString path4 = QString("D:/C++project/easySoftRender/easySoftRender/model/monster/diablo3_pose_diffuse.jpg");
	texture01->loadImage(path1);
	texture02->loadImage(path2);
	texture03->loadImage(path3);
	texture04->loadImage(path4);
}

simpleShader::~simpleShader()
{
	if (texture01) delete texture01;
	if (texture02) delete texture02;
	if (texture03) delete texture03;
	if (texture04) delete texture04;
	texture01 = nullptr;
	texture02 = nullptr;
	texture03 = nullptr;
	texture04 = nullptr;
}

VertexOut simpleShader::vertexShader(const Vertex& in)
{
	VertexOut res;
	res.textureID = in.textureID;
	res.posWorld = modelMatrix * in.position;
	res.posViewToProjection = projectionMatrix * viewMatrix * res.posWorld;
	res.color = in.color;
	res.normal = in.normal;
	res.texcoord = in.texcoord;

	res.oneDivZ = 1.0 / res.posViewToProjection.w;
	res.normal *= res.oneDivZ;
	res.texcoord *= res.oneDivZ;
	res.color *= res.oneDivZ;
	return res;
}

Vector4D simpleShader::fragmentShader(VertexOut& in)
{
	Vector4D res_color;
	Vector2D trueTex = in.texcoord / in.oneDivZ;
	if(in.textureID == 1) res_color = texture01->sample(trueTex);
	if(in.textureID == 2) res_color = texture02->sample(trueTex);
	if(in.textureID == 3) res_color = texture03->sample(trueTex);
	if(in.textureID == 4) res_color = texture04->sample(trueTex);
	return res_color;
}

void simpleShader::setModelMatrix(const Matrix4D& model)
{
	modelMatrix = model;
}

void simpleShader::setViewMatrix(const Matrix4D& view)
{
	viewMatrix = view;
}

void simpleShader::setViewMatrix(const Vector3D &camPos, const Vector3D &gaze, const Vector3D &up)
{
	viewMatrix.cameraTransformation(camPos, gaze, up);
}

void simpleShader::setProjectionMatrix(const Matrix4D& projection)
{
	projectionMatrix = projection;
}

void simpleShader::setProjectionMatrix(const float &fov, const float &asp, const float &near, 
	const float &far)
{
	projectionMatrix.perspectiveTransformation(fov, asp, near, far);
}

void simpleShader::setRotationY(const float angle)
{
	rotationY.rotationY(angle);
}

Matrix4D simpleShader::getRotationY()
{
	return rotationY;
}

PhongShader::PhongShader()
{
	modelMatrix.normalize();
	viewMatrix.normalize();
	projectionMatrix.normalize();
	rotationY.rotationY(0.05f);
	P_light = new Light();
	texture01 = new textures();
	texture02 = new textures();
	textureNm = new textures();
	textureNmT = new textures();
	QString path1 = QString("D:/C++project/easySoftRender/easySoftRender/model/ground.jpg");
	QString path2 = QString("D:/C++project/easySoftRender/easySoftRender/model/monster/diablo3_pose_diffuse.jpg");
	QString path3 = QString("D:/C++project/easySoftRender/easySoftRender/model/monster/diablo3_pose_nm.jpg");
	QString path4 = QString("D:/C++project/easySoftRender/easySoftRender/model/monster/diablo3_pose_nm_tangent.jpg");
	texture01->loadImage(path1);
	texture02->loadImage(path2);
	textureNm->loadImage(path3);
	textureNmT->loadImage(path4);
}

PhongShader::~PhongShader()
{
	if (texture01) delete texture01;
	if (texture02) delete texture02;
	if (textureNm) delete textureNm;
	if (textureNmT) delete textureNmT;
	if (P_light) delete P_light;
	texture01 = nullptr;
	texture02 = nullptr;
	textureNm = nullptr;
	textureNmT = nullptr;
	P_light = nullptr;
}

VertexOut PhongShader::vertexShader(const Vertex& in)
{
	VertexOut res;
	res.textureID = in.textureID;
	res.posWorld = modelMatrix * in.position;
	res.posViewToProjection = projectionMatrix * viewMatrix * res.posWorld;
	res.normal = in.normal;
	res.texcoord = in.texcoord;

	res.oneDivZ = 1.0 / res.posViewToProjection.w;
	res.posWorld *= res.oneDivZ;
	res.normal *= res.oneDivZ;
	res.texcoord *= res.oneDivZ;
	return res;
}

Vector4D PhongShader::fragmentShader(VertexOut& in, bool shadow)
{
	Vector2D trueTex = in.texcoord / in.oneDivZ;
	if (in.textureID == 2) in.color = texture01->sample(trueTex);
	if (in.textureID == 4) in.color = texture02->sample(trueTex);
	if (in.textureID == 4) {
		Vector4D NormalW = textureNm->sample(trueTex);
		NormalW = NormalW * 2.f - 1.f;
		NormalW = modelMatrix * NormalW;
		in.normal = Vector3D(NormalW.x, NormalW.y, NormalW.z);
	}

	P_light->kd = Vector3D(in.color.x, in.color.y, in.color.z);

	Vector3D trueN = in.normal.get_normalize();
	Vector3D posW(in.posWorld.x, in.posWorld.y, in.posWorld.z);
	posW /= in.oneDivZ;

	Vector3D LightMinusPos = P_light->position - posW;
	float r = LightMinusPos.get_length();
	float r2 = r * r;
	Vector3D viewMinusPos = viewposition - posW;
	LightMinusPos.normalize();
	viewMinusPos.normalize();
	Vector3D halfDir = viewMinusPos + LightMinusPos;
	halfDir.normalize();
	Vector3D InDivR2 = P_light->intensity / r2;

	Vector3D La = P_light->ka.cwiseDot(P_light->ambLight);
	Vector3D Ld = P_light->kd.cwiseDot(InDivR2);
	Ld *= std::max(0.0f, cos(trueN.dot(LightMinusPos)));
	Vector3D Ls = P_light->ks.cwiseDot(InDivR2);
	Ls *= pow(std::max(0.0f, cos(trueN.dot(halfDir))), P_light->p);

	Vector4D res;
	if (shadow) res = La;
	else res = (La + Ld + Ls);
	return res;
}

void PhongShader::setViewMatrix(const Vector3D& camPos, const Vector3D& gaze, const Vector3D& up)
{
	viewMatrix.cameraTransformation(camPos, gaze, up);
}

void PhongShader::setProjectionMatrix(const float& fov, const float& asp, const float& near, const float& far)
{
	projectionMatrix.perspectiveTransformation(fov, asp, near, far);
}
