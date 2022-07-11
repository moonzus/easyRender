#include "maths.h"
#include <math.h>


float Vector2D::get_length() {
	return static_cast<float>
		(sqrt(x * x + y * y));
}

Vector2D Vector2D::get_normalize() {
	float tmp = this->get_length();
	Vector2D res(x / tmp, y / tmp);
	return res;
}

void Vector2D::normalize() {
	float tmp = this->get_length();
	x /= tmp;
	y /= tmp;
}

Vector2D Vector2D::operator+(const Vector2D& vec) const {
	Vector2D res(x + vec.x, y + vec.y);
	return res;
}

Vector2D Vector2D::operator-(const Vector2D& vec) const {
	Vector2D res(x - vec.x, y - vec.y);
	return res;
}

Vector2D Vector2D::operator*(const float k) const{
	Vector2D res(x * k, y * k);
	return res;
}

Vector2D Vector2D::operator/(const float k) const {
	if (k == 0.0f) {
		Vector2D res(0.0f, 0.0f);
		return res;
	}
	Vector2D res(x / k, y / k);
	return res;
}

void Vector2D::operator+=(const Vector2D& vec) {
	x += vec.x;
	y += vec.y;
}

void Vector2D::operator-=(const Vector2D& vec) {
	x -= vec.x;
	y -= vec.y;
}

void Vector2D::operator*=(const double k) {
	x *= k;
	y *= k;
}

void Vector2D::operator/=(const float k) {
	if (k != 0.0f)x /= k;
	else x = 0.0f;
	if (k != 0.0f)y /= k;
	else y = 0.0f;
}

Vector2D Vector2D::operator+() const {
	return *this;
}

Vector2D Vector2D::operator-() const {
	Vector2D res(-x, -y);
	return res;
}

float Vector3D::get_length() {
	return static_cast<float>
		(sqrt(x * x + y * y + z * z));
}

Vector3D Vector3D::get_normalize() {
	float tmp = get_length();
	Vector3D res(x / tmp, y / tmp, z / tmp);
	return res;
}

void Vector3D::normalize() {
	float tmp = this->get_length();
	x /= tmp;
	y /= tmp;
	z /= tmp;
}

Vector3D Vector3D::operator+(const Vector3D& vec) const {
	Vector3D res(x + vec.x, y + vec.y, z + vec.z);
	return res;
}

Vector3D Vector3D::operator-(const Vector3D& vec) const {
	Vector3D res(x - vec.x, y - vec.y, z - vec.z);
	return res;
}


Vector3D Vector3D::cwiseDot(const Vector3D& vec) const
{
	Vector3D res(x * vec.x, y * vec.y, z * vec.z);
	return res;
}

Vector3D Vector3D::operator*(const float k) const {
	Vector3D res(x * k, y * k, z * k);
	return res;
}

Vector3D Vector3D::operator/(const float k) const {
	if (k == 0.0f) {
		Vector3D res(0.0f, 0.0f, 0.0f);
		return res;
	}
	Vector3D res(x / k, y / k, z / k);
	return res;
}

void Vector3D::operator+=(const Vector3D& vec) {
	x += vec.x;
	y += vec.y;
	z += vec.z;
}

void Vector3D::operator-=(const Vector3D& vec) {
	x -= vec.x;
	y -= vec.y;
	z -= vec.z;
}

void Vector3D::operator*=(float k) {
	x *= k;
	y *= k;
	z *= k;
}

void Vector3D::operator/=(const float k) {
	if (k != 0.0f)x /= k;
	else x = 0.0f;
	if (k != 0.0f)y /= k;
	else y = 0.0f;
	if (k != 0.0f)z /= k;
	else z = 0.0f;
}

Vector3D Vector3D::operator+() const {
	return *this;
}

Vector3D Vector3D::operator-() const {
	Vector3D res(-x, -y, -z);
	return res;
}

float Vector3D::dot(const Vector3D& vec) const {
	return x * vec.x + y * vec.y + z * vec.z;
}

Vector3D Vector3D::product(const Vector3D& vec) const {
	Vector3D res(y * vec.z - z * vec.y, z * vec.x - x * vec.z, x * vec.y - y * vec.x);
	return res;
}



float Vector4D::get_length() {
	return static_cast<float>
		(sqrt(x * x + y * y + z * z + w * w));
}

Vector4D Vector4D::get_normalize() {
	float tmp = this->get_length();
	Vector4D res(x / tmp, y / tmp, z / tmp, w / tmp);
	return res;
}

void Vector4D::normalize() {
	float tmp = this->get_length();
	x /= tmp;
	y /= tmp;
	z /= tmp;
}

void Vector4D::operator=(const Vector3D& vec){
	x = vec.x;
	y = vec.y;
	z = vec.z;
	w = 1.f;
}

Vector4D Vector4D::operator+(const Vector4D& vec)const {
	Vector4D res(x + vec.x, y + vec.y, z + vec.z, w + vec.w);
	return res;
}

Vector4D Vector4D::operator-(const Vector4D& vec)const {
	Vector4D res(x - vec.x, y - vec.y, z - vec.z, w - vec.w);
	return res;
}

Vector4D Vector4D::operator-(float k) const
{
	Vector4D res(x - k, y - k, z - k, w - k);
	return res;
}

Vector4D Vector4D::operator*(const float k) const {
	Vector4D res(x * k, y * k, z * k, w * k);
	return res;
}

Vector4D Vector4D::operator/(float k)const {
	if (k == 0) {
		Vector4D res(0.0f, 0.0f, 0.0f, 0.0f);
		return res;
	}
	Vector4D res(x / k, y / k, z / k, w / k);
	return res;
}

void Vector4D::operator+=(const Vector4D& vec){
	x += vec.x;
	y += vec.y;
	z += vec.z;
	w += vec.w;
}

void Vector4D::operator-=(const Vector4D& vec){
	x -= vec.x;
	y -= vec.y;
	z -= vec.z;
	w -= vec.w;
}

void Vector4D::operator*=(const float k){
	x *= k;
	y *= k;
	z *= k;
	w *= k;
}

void Vector4D::operator/=(const float k){
	if (k == 0.0f) return;
	x /= k;
	y /= k;
	z /= k;
	w /= k;
}

Vector4D Vector4D::operator+() const {
	return *this;
}

Vector4D Vector4D::operator-() const {
	Vector4D res(-x, -y, -z, -w);
	return res;
}

float Vector4D::dot(const Vector4D& vec) const {
	return x * vec.x + y * vec.y + z * vec.z + w * vec.w;
}


void Matrix4D::set(float e, int x, int y) {
	ele[x][y] = e;
}

void Matrix4D::operator=(const Matrix4D& mat)
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			ele[i][j] = mat.ele[i][j];
		}
	}
}

Matrix4D Matrix4D::operator+(const Matrix4D& mat) const {
	Matrix4D res(*this);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			res.ele[i][j] += mat.ele[i][j];
		}
	}
	return res;
}

Matrix4D Matrix4D::operator-(const Matrix4D& mat) const {
	Matrix4D res(*this);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			res.ele[i][j] -= mat.ele[i][j];
		}
	}
	return res;
}

Matrix4D Matrix4D::operator*(float k) const {
	Matrix4D res(*this);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			res.ele[i][j] *= k;
		}
	}
	return res;
}

Matrix4D Matrix4D::operator*(const Matrix4D &mat) const {
	Matrix4D res;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			float sum = 0;
			for (int k = 0; k < 4; k++)
				sum += ele[i][k] * mat.ele[k][j];
			res.ele[i][j] = sum;
		}
	}
	return res;
}

Vector4D Matrix4D::operator*(const Vector4D& vec) const {
	Vector4D res;
	res.x = ele[0][0] * vec.x + ele[0][1] * vec.y + ele[0][2] * vec.z + ele[0][3] * vec.w;
	res.y = ele[1][0] * vec.x + ele[1][1] * vec.y + ele[1][2] * vec.z + ele[1][3] * vec.w;
	res.z = ele[2][0] * vec.x + ele[2][1] * vec.y + ele[2][2] * vec.z + ele[2][3] * vec.w;
	res.w = ele[3][0] * vec.x + ele[3][1] * vec.y + ele[3][2] * vec.z + ele[3][3] * vec.w;
	return res;
}

void Matrix4D::operator+=(const Matrix4D& mat){
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			this->ele[i][j] += mat.ele[i][j];
		}
	}
}

void Matrix4D::operator-=(const Matrix4D& mat){
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			this->ele[i][j] -= mat.ele[i][j];
		}
	}
}

void Matrix4D::operator*=(const float k){
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			this->ele[i][j] *= k;
		}
	}
}

void Matrix4D::operator*= (const Matrix4D &mat){
	Matrix4D ass;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			float sum = 0;
			for (int k = 0; k < 4; k++)
				sum += ele[i][k] * mat.ele[k][j];
			ass.ele[i][j] = sum;
		}
	}
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			ele[i][j] = ass.ele[i][j];
		}
	}
}

Matrix4D Matrix4D::operator/(const float k) const {
	Matrix4D res;
	if (k == 0.0f) {
		for (int i = 0; i < 4; i++) for (int j = 0; j < 4; j++) res.ele[i][j] = 0;
	}
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			res.ele[i][j] /= k;
		}
	}
	return res;
}

void Matrix4D::operator/=(const float k){
	if (k == 0.0f) {
		Matrix4D res;
		for (int i = 0; i < 4; i++) for(int j = 0; j < 4; j++) this->ele[i][j] = 0;
	}
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			this->ele[i][j] /= k;
		}
	}
}

Matrix4D Matrix4D::operator+() const {
	return *this;
}

Matrix4D Matrix4D::operator-() const {
	Matrix4D res(*this);
	for (int i = 0; i <4; i++) {
		for (int j = 0; j < 4; j++) {
			res.ele[i][j] = this->ele[i][j] * (-1);
		}
	}
	return res;
}

void Matrix4D::normalize() {
	for (int i = 0; i < 4; i++) for(int j = 0; j < 4; j++) ele[i][j] = 0;
	for (int i = 0; i < 4; i++) ele[i][i] = 1;
}

void Matrix4D::setZero()
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			ele[i][j] = 0;
}

void Matrix4D::transposition() {
	Matrix4D tmp;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			tmp.ele[i][j] = ele[j][i];
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			ele[i][j] = tmp.ele[i][j];
}

Matrix4D Matrix4D::get_transposition() {
	Matrix4D tmp;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			tmp.ele[i][j] = ele[j][i];
	return tmp;
}

void Matrix4D::translation(const Vector3D& trans) {
	normalize();
	ele[0][3] = trans.x;
	ele[1][3] = trans.y;
	ele[2][3] = trans.z;
}

void Matrix4D::scale(const Vector3D& sca) {
	normalize();
	ele[0][0] = sca.x;
	ele[1][1] = sca.y;
	ele[2][2] = sca.z;
}

void Matrix4D::rotationX(const double angle) {
	normalize();
	float a = static_cast<float>(angle);
	ele[1][1] = cosf(a);
	ele[1][2] = -sinf(a);
	ele[2][1] = -ele[1][2];
	ele[2][2] = ele[1][1];
}

void Matrix4D::rotationY(const double angle) {
	normalize();
	float a = static_cast<float>(angle);
	ele[0][0] = cosf(a);
	ele[0][2] = sinf(a);
	ele[2][0] = -ele[0][2];
	ele[2][2] = ele[0][0];
}

void Matrix4D::rotationZ(const double angle) {
	normalize();
	float a = static_cast<float>(angle);
	ele[0][0] = cosf(a);
	ele[0][1] = -sinf(a);
	ele[1][0] = -ele[0][1];
	ele[1][1] = ele[0][0];
}

void Matrix4D::cameraTransformation(Vector3D position, Vector3D gaze, Vector3D viewUp)
{
	normalize();
	Vector3D u, v, w;
	w = position - gaze;
	w.normalize();
	u = viewUp.product(w);
	u.normalize();
	v = w.product(u);
	v.normalize();
	ele[0][0] = u.x;
	ele[0][1] = u.y;
	ele[0][2] = u.z;

	ele[1][0] = v.x;
	ele[1][1] = v.y;
	ele[1][2] = v.z;

	ele[2][0] = w.x;
	ele[2][1] = w.y;
	ele[2][2] = w.z;

	ele[0][3] = -u.dot(position);
	ele[1][3] = -v.dot(position);
	ele[2][3] = -w.dot(position);
}

void Matrix4D::perspectiveTransformation(float fov, float aspect, float near, float far)
{
	this->setZero();
	float rfov = fov * MY_PI / 180.f;
	float tanHalfFov = tan(rfov / 2);
	ele[0][0] = 1 / (aspect * tanHalfFov);
	ele[1][1] = 1 / tanHalfFov;
	ele[2][2] = -(near + far) / (far - near);
	ele[3][2] = -1.0f;
	ele[2][3] = -(2 * near * far) / (far - near);
}
