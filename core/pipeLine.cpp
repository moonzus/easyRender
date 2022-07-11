#include "pipeLine.h"

pipeLine::~pipeLine()
{
	if (m_shader) delete m_shader;
	if (m_frontBuffer) delete m_frontBuffer;
	if (m_backBuffer) delete m_backBuffer;
	if (m_shadowMap) delete m_shadowMap;
	m_shader = nullptr;
	m_frontBuffer = nullptr;
	m_backBuffer = nullptr;
	m_shadowMap = nullptr;
}

void pipeLine::initialize()
{
	if (m_shader) delete m_shader;
	if (m_frontBuffer) delete m_frontBuffer;
	if (m_backBuffer) delete m_backBuffer;
	if (m_shadowMap) delete m_shadowMap;
	if (cam) delete cam;
	m_frontBuffer = new FrameBuffer(width, height);
	m_backBuffer = new FrameBuffer(width, height);
	m_shadowMap = new FrameBuffer(width, height);
	//m_shader = new simpleShader();
	m_shader = new PhongShader();
	cam = new camera();
}

void pipeLine::clearBuffer(const Vector4D& color, bool depth)
{
	m_frontBuffer->fillBuffer(color);
	if (depth) m_frontBuffer->fillDepthBuffer();
}

/*
void pipeLine::setShaderMode(ShaderMode mode)
{
	if (m_shader) delete m_shader;
	if (mode == simple) m_shader = new simpleShader();
	else if (mode == phong) m_shader = new PhongShader();
	else if (mode == blinPhong);
}*/

void pipeLine::SetViewport(int left, int top, int width, int height)
{
	viewPortMatrix.normalize();
	viewPortMatrix.ele[0][0] = static_cast<float>(width) / 2.0f;
	viewPortMatrix.ele[1][1] = -static_cast<float>(height) / 2.0f;
	viewPortMatrix.ele[0][3] = static_cast<float>(left) + static_cast<float>(width) / 2.0f;
	viewPortMatrix.ele[1][3] = static_cast<float>(top) + static_cast<float>(height) / 2.0f;
}

void pipeLine::setCamera(const camera *c)
{
	cam->position = c->position;
	cam->gazeAt = c->gazeAt;
	cam->upView = c->upView;
	cam->fov = c->fov;
	cam->aspect = c->aspect;
	cam->near = c->near;
	cam->far = c->far;
}

void pipeLine::drawIndex(RenderMode mode)
{
	if (m_vertices.empty()) return;
	Matrix4D modelM(5.f, 0.f, 0.f, 0.f, 
					0.f, 5.f, 0.f, 0.f, 
					0.f, 0.f, 5.f, 0.f, 
					0.f, 0.f, 0.f, 1.f);
	//modelM.scale(scal);
	m_shader->setViewposition(cam->position);
	modelM *= m_shader->getRotationY();
	m_shader->setModelMatrix(modelM);
	m_shader->setViewMatrix(cam->position, cam->gazeAt, cam->upView);
	m_shader->setProjectionMatrix(cam->fov, cam->aspect, cam->near, cam->far);\
	for (int i = 0; i < m_indices.size() / 3; ++i) {
		Vertex v1, v2, v3;
		v1 = m_vertices[m_indices[3 * i + 0]];
		v2 = m_vertices[m_indices[3 * i + 1]];
		v3 = m_vertices[m_indices[3 * i + 2]];

		VertexOut vv1, vv2, vv3;
		vv1 = m_shader->vertexShader(v1);
		vv2 = m_shader->vertexShader(v2);
		vv3 = m_shader->vertexShader(v3);

		if(!backfaceculling(vv1, vv2, vv3)) continue;

		perspectiveDivision(vv1);
		perspectiveDivision(vv2);
		perspectiveDivision(vv3);

	/*	vv1.color = m_shader->fragmentShader(vv1);
		vv2.color = m_shader->fragmentShader(vv2);
		vv3.color = m_shader->fragmentShader(vv3);*/

		vv1.posViewToProjection = viewPortMatrix * vv1.posViewToProjection;
		vv2.posViewToProjection = viewPortMatrix * vv2.posViewToProjection;
		vv3.posViewToProjection = viewPortMatrix * vv3.posViewToProjection;

		if (mode == wire) {
			bresenham(vv1, vv2);
			bresenham(vv2, vv3);
			bresenham(vv3, vv1);
		}
		else if (mode == fill) {
			edgeWalkingRasterization(vv1, vv2, vv3);
		}
		else return;
	}
}

void pipeLine::swapBuffer()
{
	FrameBuffer* tmp = m_frontBuffer;
	m_frontBuffer = m_backBuffer;
	m_backBuffer = tmp;
}


VertexOut pipeLine::lerp(const VertexOut& v1, const VertexOut& v2, double weight)
{
	VertexOut res;
	res.posWorld = v1.posWorld.lerp(v2.posWorld, weight);
	res.posViewToProjection = v1.posViewToProjection.lerp(v2.posViewToProjection, weight);
	res.normal = v1.normal.lerp(v2.normal, weight);
	res.color = v1.color.lerp(v2.color, weight);
	res.textureID = v1.textureID;
	res.oneDivZ = (1 - weight) * v1.oneDivZ + weight * v2.oneDivZ;
	
	/*Vector2D tmp1 = v1.texcoord * v1.oneDivZ;
	Vector2D tmp2 = v2.texcoord * v2.oneDivZ;
	res.texcoord = tmp1.lerp(tmp2, weight);*/
	//res.texcoord /= res.oneDivZ;

	res.texcoord = v1.texcoord.lerp(v2.texcoord, weight);
	return res;
}

void pipeLine::bresenham(const VertexOut& from, const VertexOut& to)
{
	int dx = to.posViewToProjection.x - from.posViewToProjection.x;
	int dy = to.posViewToProjection.y - from.posViewToProjection.y;
	int stepx = 1;
	int stepy = 1;

	if (dx < 0) {
		stepx = -1;
		dx = -dx;
	}
	if (dy < 0) {
		stepy = -1;
		dy = -dy;
	}

	int dx2 = 2 * dx;
	int dy2 = 2 * dy;
	int dx2_minus_dy2 = dx2 - dy2;
	int sx = from.posViewToProjection.x;
	int sy = from.posViewToProjection.y;
	VertexOut tmp;

	if (dy <= dx) {
		int d = dx - dy2;
		for (int i = 0; i <= dx; ++i) {
			tmp = lerp(from, to, static_cast<double>(i) / dx);
			m_backBuffer->drawPixel(sx, sy, tmp.color);
			sx += stepx;

			if (d < 0) {
				sy += stepy;
				d += dx2_minus_dy2;
			}
			else d -= dy2;
		}
	}
	else {
		int d = dy - dx2;
		for (int i = 0; i <= dy; ++i) {
			tmp = lerp(from, to, static_cast<double>(i) / dy);
			m_backBuffer->drawPixel(sx, sy, tmp.color);
			sy += stepy;

			if (d < 0) {
				sx += stepx;
				d -= dx2_minus_dy2;
			}
			else d -= dx2;
		}
	}
}

void pipeLine::fillLinePerRow(const VertexOut& left, const VertexOut& right)
{
	VertexOut cur;
	int length = right.posViewToProjection.x - left.posViewToProjection.x + 1;
	for (int i = 0; i <= length; ++i) {
		double weight = static_cast<double>(i) / length;
		cur = lerp(left, right, weight);
		cur.posViewToProjection.x = left.posViewToProjection.x + i;
		cur.posViewToProjection.y = left.posViewToProjection.y;

		double depth = m_backBuffer->getDepth(cur.posViewToProjection.x, cur.posViewToProjection.y);
	    if (depth < cur.posViewToProjection.z) continue;
		m_backBuffer->drawDepth(cur.posViewToProjection.x, cur.posViewToProjection.y, cur.posViewToProjection.z);
		//double d = m_backBuffer->getDepth(cur.posViewToProjection.x, cur.posViewToProjection.y);

		/*Vector4D tmp = cur.posWorld / cur.oneDivZ;
		tmp = lightProjectionM * tmp;
		tmp /= tmp.w;
		tmp.z = (tmp.z + 1.0f) * 0.5f;
		tmp = viewPortMatrix * tmp;
		bool m_shadow = tmp.z < (m_shadowMap->getDepth(tmp.x, tmp.y) - 0.0f);*/

		m_backBuffer->drawPixel(cur.posViewToProjection.x, cur.posViewToProjection.y, m_shader->fragmentShader(cur, false));
		//m_backBuffer->drawPixel(cur.posViewToProjection.x, cur.posViewToProjection.y, cur.color);
	}
}

void pipeLine::rasterTopTrangle(const VertexOut& v1, const VertexOut& v2, const VertexOut& v3)
{
	VertexOut mid = v1;
	VertexOut left = v2;
	VertexOut right = v3;
	VertexOut tmp, newleft, newright;
	if (left.posViewToProjection.x > right.posViewToProjection.x) {
		tmp = left;
		left = right;
		right = tmp;
	}

	int dy = left.posViewToProjection.y - mid.posViewToProjection.y + 1;
	for (int i = 0; i < dy; ++i) {
		double weight = 0;
		if (dy != 0) weight = static_cast<double>(i) / dy;
		newleft = lerp(left, mid, weight);
		newright = lerp(right, mid, weight);
		newleft.posViewToProjection.y = newright.posViewToProjection.y = left.posViewToProjection.y - i;
		fillLinePerRow(newleft, newright);
	}

}

void pipeLine::rasterBottomTrangle(const VertexOut& v1, const VertexOut& v2, const VertexOut& v3)
{
	VertexOut mid = v1;
	VertexOut left = v2;
	VertexOut right = v3;
	VertexOut tmp, newleft, newright;
	if (left.posViewToProjection.x > right.posViewToProjection.x) {
		tmp = left;
		left = right;
		right = tmp;
	}

	int dy = mid.posViewToProjection.y - left.posViewToProjection.y + 1;
	for (int i = 0; i < dy; ++i) {
		double weight = 0;
		if (dy != 0) weight = static_cast<double>(i) / dy;
		newleft = lerp(left, mid, weight);
		newright = lerp(right, mid, weight);
		newleft.posViewToProjection.y = newright.posViewToProjection.y = left.posViewToProjection.y + i;
		fillLinePerRow(newleft, newright);
	}
}

void pipeLine::edgeWalkingRasterization(const VertexOut& v1, const VertexOut& v2, const VertexOut& v3)
{
	VertexOut tmp;
	VertexOut trangle[3] = {v1, v2, v3};

	if (trangle[0].posViewToProjection.y > trangle[1].posViewToProjection.y) {
		tmp = trangle[1];
		trangle[1] = trangle[0];
		trangle[0] = tmp;
	}
	if (trangle[0].posViewToProjection.y > trangle[2].posViewToProjection.y) {
		tmp = trangle[2];
		trangle[2] = trangle[0];
		trangle[0] = tmp;
	}
	if (trangle[1].posViewToProjection.y > trangle[2].posViewToProjection.y) {
		tmp = trangle[2];
		trangle[2] = trangle[1];
		trangle[1] = tmp;
	}

	float y0 = trangle[0].posViewToProjection.y;
	float y1 = trangle[1].posViewToProjection.y;
	float y2 = trangle[2].posViewToProjection.y;

	if (y0 == y1) rasterBottomTrangle(trangle[2], trangle[1], trangle[0]);
	else if (y1 == y2) rasterTopTrangle(trangle[0], trangle[1], trangle[2]);
	else {
		double weight = static_cast<double>(y1 - y0) / (y2 - y0);
		VertexOut newpoint = lerp(trangle[0], trangle[2], weight);
		
		newpoint.posViewToProjection.y = y1;
		rasterBottomTrangle(trangle[2], trangle[1], newpoint);
		rasterTopTrangle(trangle[0], trangle[1], newpoint);
	}
}

void pipeLine::perspectiveDivision(VertexOut& target)
{
	target.posViewToProjection /= target.posViewToProjection.w;
	target.posViewToProjection.z = (target.posViewToProjection.z + 1.0f) * 0.5f;
}

bool pipeLine::backfaceculling(const VertexOut& v1, const VertexOut& v2, const VertexOut& v3)
{
	Vector4D vv1 = v1.posWorld;
	Vector4D vv2 = v2.posWorld;
	Vector4D vv3 = v3.posWorld;
	Vector4D tmp1 = v2.posWorld - v1.posWorld;
	Vector4D tmp2 = v3.posWorld - v1.posWorld;
	Vector3D n1(tmp1.x, tmp1.y, tmp1.z);
	Vector3D n2(tmp2.x, tmp2.y, tmp2.z);
	Vector3D n = n1.product(n2);
	Vector3D view(cam->position.x - v1.posWorld.x, cam->position.y - v1.posWorld.y, cam->position.z - v1.posWorld.z);
	int a = n.dot(view);
	return n.dot(view) > 0;
}
