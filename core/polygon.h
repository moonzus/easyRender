#pragma once
#include "maths.h"
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

class Vertex
{
public:
	Vector4D position;
	Vector4D color;
	Vector2D texcoord;
	Vector3D normal;
	int textureID = 1;

public:
	Vertex() = default;
	Vertex(Vector4D pos, Vector4D colo, Vector2D tex, Vector3D nor, int texID) :
		position(pos), color(colo), texcoord(tex), normal(nor), textureID(texID) {};
	Vertex(const Vertex& ver) : position(ver.position), color(ver.color), texcoord(ver.texcoord),
		normal(ver.normal), textureID(ver.textureID) {};
	~Vertex() = default;
};

class VertexOut
{
public:
	Vector4D posWorld;
	Vector4D posViewToProjection;
	Vector4D color;
	Vector2D texcoord;
	Vector3D normal;
	double oneDivZ = 1.0;
	int textureID = 1;

public:
	VertexOut() = default;
	VertexOut(Vector4D posW, Vector4D posVtP, Vector4D colo, Vector2D tex, Vector3D nor, double onedz, int texID) :
		posWorld(posW), posViewToProjection(posVtP), color(colo), texcoord(tex), 
		normal(nor), oneDivZ(onedz), textureID(texID) {};
	VertexOut(const VertexOut& verout) :
		posWorld(verout.posWorld), posViewToProjection(verout.posViewToProjection),
		color(verout.color), texcoord(verout.texcoord), normal(verout.normal), oneDivZ(verout.oneDivZ),
		textureID(verout.textureID) {};
	~VertexOut() = default;
};

class Mesh
{
public:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

public:
	Mesh() = default;
	Mesh(const Mesh& mes) : vertices(mes.vertices), indices(mes.indices) {};
	~Mesh() = default;

	Mesh& operator=(const Mesh& me);
	 
	void setVertices(Vertex* ve, int count){
		vertices.resize(count);
		new(&vertices[0]) std::vector<Vertex>(ve, ve + count);
	}
	void setIndices(int* i, int count) {
		indices.resize(count);        
		new(&indices) std::vector<unsigned int>(i, i + count);
	}

	void setTriangle(const Vector3D& p1, const Vector3D& p2, const Vector3D& p3);
	void setBox(float width, float height, float depth);
	void setGround();
};

class ObjModel : public Mesh
{
private:
	Vector3D minPoint, maxPoint;        // Bounding box.

public:
	// ctor/dtor.
	ObjModel() = default;
	ObjModel(const std::string& path, int texID);
	~ObjModel() = default;

	// Size setting.
	//Vector3D setSizeToVector(float sx, float sy, float sz) const;
	//Matrix4x4 setSizeToMatrix(float sx, float sy, float sz) const;

public:
	// Obj file loader.
	void loadObjFile(const std::string& path, int texID);
};


