#pragma once
#include "baseShader.h"
#include "FrameBuffer.h"
#include "camera.h"

class pipeLine
{
private:
	int width, height;
	//simpleShader* m_shader;
	PhongShader* m_shader;
	FrameBuffer* m_frontBuffer;
	FrameBuffer* m_backBuffer;
	FrameBuffer* m_shadowMap;
	std::vector<Vertex> m_vertices;
	std::vector<unsigned int> m_indices;
	Matrix4D viewPortMatrix;
	Matrix4D lightProjectionM;
	camera *cam;

public:
	//enum ShaderMode{simple, phong, blinPhong};
	enum RenderMode{fill, wire};

public:
	pipeLine(int w, int h) : width(w), height(h), m_shader(nullptr), m_frontBuffer(nullptr),
		m_backBuffer(nullptr), m_shadowMap(nullptr), cam(nullptr) {};
	~pipeLine();

	void initialize();
	void clearBuffer(const Vector4D& color, bool depth);
	void setShadowAtri() { m_shadowMap = m_backBuffer; 
						   lightProjectionM = m_shader->getProjection() * m_shader->getView(); };
	void setVertexBuffer(const std::vector<Vertex>& vertices) { this->m_vertices.insert(m_vertices.end(), vertices.begin(), vertices.end()); };
	void setIndexBuffer(const std::vector<unsigned int>& indices) { this->m_indices.insert(m_indices.end(), indices.begin(), indices.end()); };
	//void setShaderMode(ShaderMode mode);
	void SetViewport(int left, int top, int width, int height);
	void setCamera(const camera *c);
	void setRotation(const float &angle) { m_shader->setRotationY(angle); };
	void drawIndex(RenderMode mode);
	void swapBuffer();
	VertexOut lerp(const VertexOut& v1, const VertexOut& v2, double weight);
	void bresenham(const VertexOut& from, const VertexOut& to);

	void fillLinePerRow(const VertexOut& left, const VertexOut& right);
	void rasterTopTrangle(const VertexOut& v1, const VertexOut& v2, const VertexOut& v3);
	void rasterBottomTrangle(const VertexOut& v1, const VertexOut& v2, const VertexOut& v3);
	void edgeWalkingRasterization(const VertexOut& v1, const VertexOut& v2, const VertexOut& v3);

	void perspectiveDivision(VertexOut& target);
	bool backfaceculling(const VertexOut& v1, const VertexOut& v2, const VertexOut& v3);
	
	unsigned char* output() { return m_frontBuffer->getBufferData(); };
};


