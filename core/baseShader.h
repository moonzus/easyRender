#pragma once
#include "polygon.h"
#include "textures.h"
#include "Light.h"

class baseShader
{
public:
	baseShader() = default;
	virtual ~baseShader() = default;

	virtual VertexOut vertexShader(const Vertex& in) = 0;
	virtual Vector4D fragmentShader(VertexOut& in, bool shadow) = 0;
	virtual void setModelMatrix(const Matrix4D& model) = 0;
	virtual void setViewMatrix(const Matrix4D& view) = 0;
	virtual void setProjectionMatrix(const Matrix4D& projection) = 0;
};

class simpleShader : public baseShader
{
private:
	Matrix4D modelMatrix;
	Matrix4D viewMatrix;
	Matrix4D projectionMatrix;
	Matrix4D rotationY;
	textures *texture01;
	textures *texture02;
	textures *texture03;
	textures *texture04;

public: 
	simpleShader();
	~simpleShader();

	virtual VertexOut vertexShader(const Vertex & in);
	virtual Vector4D fragmentShader(VertexOut & in);
	virtual void setModelMatrix(const Matrix4D & model);
	virtual void setViewMatrix(const Matrix4D & view);
	void setViewMatrix(const Vector3D &camPos, const Vector3D &gaze, const Vector3D &up);
	virtual void setProjectionMatrix(const Matrix4D & projection);
	void setProjectionMatrix(const float &fov, const float &asp, const float &near, const float &far);
	void setRotationY(const float angle);
	Matrix4D getRotationY();
};

class PhongShader : public baseShader 
{
private:
	Vector3D viewposition;
	Matrix4D modelMatrix;
	Matrix4D viewMatrix;
	Matrix4D projectionMatrix;
	Matrix4D rotationY;

public:
	Light* P_light;
	textures* texture01;
	textures* texture02;
	textures* textureNm;
	textures* textureNmT;

public:
	PhongShader();
	~PhongShader();

	void setViewposition(const Vector3D pos) { viewposition = pos; };
	Matrix4D getProjection() { return projectionMatrix; };
	Matrix4D getView() { return viewMatrix; };
	virtual VertexOut vertexShader(const Vertex& in);
	virtual Vector4D fragmentShader(VertexOut& in, bool shadow);
	virtual void setModelMatrix(const Matrix4D& model) { modelMatrix = model; };
	virtual void setViewMatrix(const Matrix4D& view) { viewMatrix = view; };
	void setViewMatrix(const Vector3D& camPos, const Vector3D& gaze, const Vector3D& up);
	virtual void setProjectionMatrix(const Matrix4D& projection) { projectionMatrix = projection; };
	void setProjectionMatrix(const float& fov, const float& asp, const float& near, const float& far);
	void setRotationY(const float angle) { rotationY.rotationY(angle); };
	Matrix4D getRotationY() { return rotationY; };
};