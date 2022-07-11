#pragma once
#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#define MY_PI 3.1415926

class Vector2D
{
public:
	float x, y;
public:
	Vector2D() : x(0.0f), y(0.0f) {}
	Vector2D(float a, float b) : x(a), y(b) {}
	Vector2D(const Vector2D& vec) : x(vec.x), y(vec.y) {}
	~Vector2D() {}

	float get_length();
	Vector2D get_normalize();
	void normalize();

	Vector2D operator+(const Vector2D& vec) const;
	Vector2D operator-(const Vector2D& vec) const;
	Vector2D operator*(const float k) const;
	Vector2D operator/(const float k) const;
	void operator=(const Vector2D& vec) { x = vec.x; y = vec.y; };
	void operator+=(const Vector2D& vec);
	void operator-=(const Vector2D& vec);
	void operator*=(const double k);
	void operator/=(const float k);
	Vector2D operator+() const;
	Vector2D operator-() const;

	Vector2D lerp(const Vector2D& v2, const float factor) const
	{
		return (*this) * (1.0f - factor) + v2 * factor;
	};
	Vector2D quadraticInterpolate(const Vector2D& v2, const Vector2D& v3, const float factor) const
	{
		return (*this) * (1.0f - factor) * (1.0f - factor) + v2 * 2.0f * factor * (1.0f - factor) +  
			v3 * factor * factor;
	};
};


class Vector3D
{
public:
	float x, y, z;
public:
	Vector3D() : x(0.0f), y(0.0f), z(0.0f) {}
	Vector3D(float a, float b, float c) : x(a), y(b), z(c) {}
	Vector3D(const Vector3D& vec) : x(vec.x), y(vec.y), z(vec.z) {};
	~Vector3D() {}

	float get_length();
	Vector3D get_normalize();
	void normalize();

	Vector3D operator+(const Vector3D& vec) const;
	Vector3D operator-(const Vector3D& vec) const;
	Vector3D operator*(const float k) const;
	Vector3D operator/(const float k) const;
	void operator+=(const Vector3D& vec);
	void operator-=(const Vector3D& vec);
	void operator*=(const float k);
	void operator/=(const float k);
	Vector3D operator+() const;
	Vector3D operator-() const;

	Vector3D cwiseDot(const Vector3D& vec) const;
	float dot(const Vector3D& vec) const;
	Vector3D product(const Vector3D& vec) const;
	Vector3D lerp(const Vector3D& v2, float factor) const
	{
		return (*this) * (1.0f - factor) + v2 * factor;
	};
	Vector3D QuadraticInterpolate(const Vector3D& v2, const Vector3D& v3, float factor) const
	{
		return (*this) * (1.0f - factor) * (1.0f - factor) + v2 * 2.0f * factor * (1.0f - factor) + 
			v3 * factor * factor;
	};
};


class Vector4D
{
public:
	float x, y, z, w;
public:
	Vector4D() :x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
	Vector4D(float a, float b, float c, float d) :x(a), y(b), z(c), w(d) {}
	Vector4D(const Vector4D& vec) :x(vec.x), y(vec.y), z(vec.z), w(vec.w) {}
	~Vector4D() {}

	float get_length();
	Vector4D get_normalize();
	void normalize();

	void operator=(const Vector3D& vec);
	Vector4D operator+(const Vector4D& vec) const;
	Vector4D operator-(const Vector4D& vec) const;
	Vector4D operator-(float k) const;
	Vector4D operator*(float k) const;
	Vector4D operator/(float k) const;
	void operator+=(const Vector4D& vec);
	void operator-=(const Vector4D& vec);
	void operator/=(const float k);
	void operator*=(const float k);
	Vector4D operator+() const;
	Vector4D operator-() const;

	float dot(const Vector4D& vec) const;
	Vector4D lerp(const Vector4D& v2, float factor) const
	{
		return (*this) * (1.0f - factor) + v2 * factor;
	};
	Vector4D QuadraticInterpolate(const Vector4D& v2, const Vector4D& v3, float factor) const
	{
		return (*this) * (1.0f - factor) * (1.0f - factor) + v2 * 2.0f * factor * (1.0f - factor) +
			v3 * factor * factor;
	};
};

class Matrix4D
{
public:
	float ele[4][4];
public:
	Matrix4D() : ele{ 0.0f } {}
	Matrix4D(float a00, float a01, float a02, float a03,
		float a10, float a11, float a12, float a13,
		float a20, float a21, float a22, float a23,
		float a30, float a31, float a32, float a33)
		: ele{ a00, a01, a02, a03, a10, a11, a12, a13, a20, a21, a22, a23, a30, a31, a32, a33 } {}

	Matrix4D(const Matrix4D& mat)
		: ele{ mat.ele[0][0], mat.ele[0][1], mat.ele[0][2], mat.ele[0][3],
			 mat.ele[1][0], mat.ele[1][1], mat.ele[1][2], mat.ele[1][3],
			 mat.ele[2][0], mat.ele[2][1], mat.ele[2][2], mat.ele[2][3],
			 mat.ele[3][0], mat.ele[3][1], mat.ele[3][2], mat.ele[3][3] } {}

	~Matrix4D() {}

	void set(float e, int x, int y);

	Matrix4D operator+(const Matrix4D& mat) const;
	Matrix4D operator-(const Matrix4D& mat) const;
	Matrix4D operator*(const float k) const;
	Matrix4D operator*(const Matrix4D& mat) const;
	Vector4D operator*(const Vector4D& vec) const;
	Matrix4D operator/(const float k) const;
	void operator+=(const Matrix4D& mat);
	void operator-=(const Matrix4D& mat);
	void operator*=(const float k);
	void operator*=(const Matrix4D& mat);
	void operator/=(const float k);
	void operator=(const Matrix4D& mat);
	Matrix4D operator+() const;
	Matrix4D operator-() const;

	void normalize();
	void setZero();
	void transposition();
	Matrix4D get_transposition();
	void translation(const Vector3D& trans);
	void scale(const Vector3D& sca);
	void rotationX(const double angle);
	void rotationY(const double angle);
	void rotationZ(const double angle);
	void cameraTransformation(Vector3D position, Vector3D gaze, Vector3D viewUp);
	void perspectiveTransformation(float fov, float aspect, float near, float far);

};