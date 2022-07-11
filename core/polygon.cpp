#include "polygon.h"

Mesh& Mesh::operator=(const Mesh& me)
{
	vertices = me.vertices;
	indices = me.indices;
	return *this;
}

void Mesh::setTriangle(const Vector3D& p1, const Vector3D& p2, const Vector3D& p3)
{
	vertices.resize(3);
	indices.resize(3);
	vertices[0].position = p1;
	vertices[0].normal = Vector3D(0.f, 0.f, 1.f);
	vertices[0].color = Vector4D(1.f, 0.f, 0.f, 1.f);
	vertices[0].texcoord = Vector2D(0.f, 0.f);
	vertices[1].position = p2;
	vertices[1].normal = Vector3D(0.f, 0.f, 1.f);
	vertices[1].color = Vector4D(0.f, 1.f, 0.f, 1.f);
	vertices[1].texcoord = Vector2D(1.f, 0.f);
	vertices[2].position = p3;
	vertices[2].normal = Vector3D(0.f, 0.f, 1.f);
	vertices[2].color = Vector4D(0.f, 0.f, 1.f, 1.f);
	vertices[2].texcoord = Vector2D(0.5f, 1.f);
	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
}

void Mesh::setGround() {
	int iSizeV = vertices.size();
	int iSizeI = indices.size();
	vertices.resize(iSizeV + 4);
	indices.resize(iSizeI + 6);

	vertices[iSizeV].textureID = 2;
	vertices[iSizeV].position = Vector3D(1.2f, -1.0f, -1.2f);
	vertices[iSizeV].normal = Vector3D(0.f, 1.f, 0.0f);
	vertices[iSizeV].color = Vector4D(1.f, 0.f, 0.f, 1.f);
	vertices[iSizeV].texcoord = Vector2D(0.f, 0.f);
	vertices[iSizeV + 1].textureID = 2;
	vertices[iSizeV + 1].position = Vector3D(1.2f, -1.0f, 1.2f);
	vertices[iSizeV + 1].normal = Vector3D(0.f, 1.f, 0.0f);
	vertices[iSizeV + 1].color = Vector4D(1.f, 0.f, 0.f, 1.f);
	vertices[iSizeV + 1].texcoord = Vector2D(0.f, 1.f);
	vertices[iSizeV + 2].textureID = 2;
	vertices[iSizeV + 2].position = Vector3D(-1.2f, -1.0f, 1.2f);
	vertices[iSizeV + 2].normal = Vector3D(0.f, 1.f, 0.0f);
	vertices[iSizeV + 2].color = Vector4D(1.f, 0.f, 0.f, 1.f);
	vertices[iSizeV + 2].texcoord = Vector2D(1.f, 1.f);
	vertices[iSizeV + 3].textureID = 2;
	vertices[iSizeV + 3].position = Vector3D(-1.2f, -1.0f, -1.2f);
	vertices[iSizeV + 3].normal = Vector3D(0.f, 1.f, 0.0f);
	vertices[iSizeV + 3].color = Vector4D(1.f, 0.f, 0.f, 1.f);
	vertices[iSizeV + 3].texcoord = Vector2D(1.f, 0.f);

	indices[iSizeI + 0] = iSizeV + 15066 + 0;
	indices[iSizeI + 1] = iSizeV + 15066 + 3;
	indices[iSizeI + 2] = iSizeV + 15066 + 2;
	indices[iSizeI + 3] = iSizeV + 15066 + 0;
	indices[iSizeI + 4] = iSizeV + 15066 + 2;
	indices[iSizeI + 5] = iSizeV + 15066 + 1;
}

void Mesh::setBox(float width, float height, float depth)
{
	vertices.resize(24);
	indices.resize(36);

	float halfW = width * 0.5f;
	float halfH = height * 0.5f;
	float halfD = depth * 0.5f;
	//front
	vertices[0].textureID = 1;
	vertices[0].position = Vector3D(halfW, halfH, halfD);
	vertices[0].normal = Vector3D(0.f, 0.f, 1.f);
	vertices[0].color = Vector4D(1.f, 0.f, 0.f, 1.f);
	vertices[0].texcoord = Vector2D(1.f, 1.f);
	vertices[1].textureID = 1;
	vertices[1].position = Vector3D(-halfW, halfH, halfD);
	vertices[1].normal = Vector3D(0.f, 0.f, 1.f);
	vertices[1].color = Vector4D(0.f, 1.f, 0.f, 1.f);
	vertices[1].texcoord = Vector2D(0.f, 1.f);
	vertices[2].textureID = 1;
	vertices[2].position = Vector3D(-halfW, -halfH, halfD);
	vertices[2].normal = Vector3D(0.f, 0.f, 1.f);
	vertices[2].color = Vector4D(0.f, 0.f, 1.f, 1.f);
	vertices[2].texcoord = Vector2D(0.f, 0.f);
	vertices[3].textureID = 1;
	vertices[3].position = Vector3D(halfW, -halfH, halfD);
	vertices[3].normal = Vector3D(0.f, 0.f, 1.f);
	vertices[3].color = Vector4D(0.f, 1.f, 1.f, 1.f);
	vertices[3].texcoord = Vector2D(1.f, 0.f);
	//left
	vertices[4].textureID = 1;
	vertices[4].position = Vector3D(-halfW, +halfH, halfD);
	vertices[4].normal = Vector3D(-1.f, 0.f, 0.f);
	vertices[4].color = Vector4D(0.f, 0.f, 1.f, 1.f);
	vertices[4].texcoord = Vector2D(1.f, 1.f);
	vertices[5].textureID = 1;
	vertices[5].position = Vector3D(-halfW, +halfH, -halfD);
	vertices[5].normal = Vector3D(-1.f, 0.f, 0.f);
	vertices[5].color = Vector4D(1.f, 1.f, 0.f, 1.f);
	vertices[5].texcoord = Vector2D(0.f, 1.f);
	vertices[6].textureID = 1;
	vertices[6].position = Vector3D(-halfW, -halfH, -halfD);
	vertices[6].normal = Vector3D(-1.f, 0.f, 0.f);
	vertices[6].color = Vector4D(0.f, 1.f, 0.f, 1.f);
	vertices[6].texcoord = Vector2D(0.f, 0.f);
	vertices[7].textureID = 1;
	vertices[7].position = Vector3D(-halfW, -halfH, halfD);
	vertices[7].normal = Vector3D(-1.f, 0.f, 0.f);
	vertices[7].color = Vector4D(1.f, 1.f, 1.f, 1.f);
	vertices[7].texcoord = Vector2D(1.f, 0.f);
	//back
	vertices[8].textureID = 1;
	vertices[8].position = Vector3D(-halfW, +halfH, -halfD);
	vertices[8].normal = Vector3D(0.f, 0.f, -1.f);
	vertices[8].color = Vector4D(1.f, 0.f, 1.f, 1.f);
	vertices[8].texcoord = Vector2D(0.f, 0.f);
	vertices[9].textureID = 1;
	vertices[9].position = Vector3D(+halfW, +halfH, -halfD);
	vertices[9].normal = Vector3D(0.f, 0.f, -1.f);
	vertices[9].color = Vector4D(0.f, 1.f, 1.f, 1.f);
	vertices[9].texcoord = Vector2D(1.f, 0.f);
	vertices[10].textureID = 1;
	vertices[10].position = Vector3D(+halfW, -halfH, -halfD);
	vertices[10].normal = Vector3D(0.f, 0.f, -1.f);
	vertices[10].color = Vector4D(1.f, 1.f, 0.f, 1.f);
	vertices[10].texcoord = Vector2D(1.f, 1.f);
	vertices[11].textureID = 1;
	vertices[11].position = Vector3D(-halfW, -halfH, -halfD);
	vertices[11].normal = Vector3D(0.f, 0.f, -1.f);
	vertices[11].color = Vector4D(0.f, 0.f, 1.f, 1.f);
	vertices[11].texcoord = Vector2D(0.f, 1.f);
	//right
	vertices[12].textureID = 1;
	vertices[12].position = Vector3D(halfW, +halfH, -halfD);
	vertices[12].normal = Vector3D(1.f, 0.f, 0.f);
	vertices[12].color = Vector4D(0.f, 1.f, 0.f, 1.f);
	vertices[12].texcoord = Vector2D(0.f, 0.f);
	vertices[13].textureID = 1;
	vertices[13].position = Vector3D(halfW, +halfH, +halfD);
	vertices[13].normal = Vector3D(1.f, 0.f, 0.f);
	vertices[13].color = Vector4D(1.f, 0.f, 0.f, 1.f);
	vertices[13].texcoord = Vector2D(1.f, 0.f);
	vertices[14].textureID = 1;
	vertices[14].position = Vector3D(halfW, -halfH, +halfD);
	vertices[14].normal = Vector3D(1.f, 0.f, 0.f);
	vertices[14].color = Vector4D(0.f, 1.f, 1.f, 1.f);
	vertices[14].texcoord = Vector2D(1.f, 1.f);
	vertices[15].textureID = 1;
	vertices[15].position = Vector3D(halfW, -halfH, -halfD);
	vertices[15].normal = Vector3D(1.f, 0.f, 0.f);
	vertices[15].color = Vector4D(1.f, 0.f, 1.f, 1.f);
	vertices[15].texcoord = Vector2D(0.f, 1.f);
	//top
	vertices[16].textureID = 1;
	vertices[16].position = Vector3D(+halfW, halfH, -halfD);
	vertices[16].normal = Vector3D(0.f, 1.f, 0.f);
	vertices[16].color = Vector4D(0.f, 0.f, 0.f, 1.f);
	vertices[16].texcoord = Vector2D(0.f, 0.f);
	vertices[17].textureID = 1;
	vertices[17].position = Vector3D(-halfW, halfH, -halfD);
	vertices[17].normal = Vector3D(0.f, 1.f, 0.f);
	vertices[17].color = Vector4D(1.f, 1.f, 0.f, 1.f);
	vertices[17].texcoord = Vector2D(1.f, 0.f);
	vertices[18].textureID = 1;
	vertices[18].position = Vector3D(-halfW, halfH, halfD);
	vertices[18].normal = Vector3D(0.f, 1.f, 0.f);
	vertices[18].color = Vector4D(0.f, 1.f, 1.f, 1.f);
	vertices[18].texcoord = Vector2D(1.f, 1.f);
	vertices[19].textureID = 1;
	vertices[19].position = Vector3D(+halfW, halfH, halfD);
	vertices[19].normal = Vector3D(0.f, 1.f, 0.f);
	vertices[19].color = Vector4D(1.f, 0.f, 0.f, 1.f);
	vertices[19].texcoord = Vector2D(0.f, 1.f);
	//down
	vertices[20].textureID = 1;
	vertices[20].position = Vector3D(+halfW, -halfH, -halfD);
	vertices[20].normal = Vector3D(0.f, -1.f, 0.f);
	vertices[20].color = Vector4D(0.f, 0.f, 1.f, 1.f);
	vertices[20].texcoord = Vector2D(0.f, 0.f);
	vertices[21].textureID = 1;
	vertices[21].position = Vector3D(+halfW, -halfH, +halfD);
	vertices[21].normal = Vector3D(0.f, -1.f, 0.f);
	vertices[21].color = Vector4D(1.f, 1.f, 1.f, 1.f);
	vertices[21].texcoord = Vector2D(1.f, 0.f);
	vertices[22].textureID = 1;
	vertices[22].position = Vector3D(-halfW, -halfH, +halfD);
	vertices[22].normal = Vector3D(0.f, -1.f, 0.f);
	vertices[22].color = Vector4D(0.f, 1.f, 0.f, 1.f);
	vertices[22].texcoord = Vector2D(1.f, 1.f);
	vertices[23].textureID = 1;
	vertices[23].position = Vector3D(-halfW, -halfH, -halfD);
	vertices[23].normal = Vector3D(0.f, -1.f, 0.f);
	vertices[23].color = Vector4D(1.f, 0.f, 1.f, 1.f);
	vertices[23].texcoord = Vector2D(0.f, 1.f);

	//front
	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	indices[3] = 0;
	indices[4] = 2;
	indices[5] = 3;
	//left
	indices[6] = 4;
	indices[7] = 5;
	indices[8] = 6;
	indices[9] = 4;
	indices[10] = 6;
	indices[11] = 7;
	//back
	indices[12] = 8;
	indices[13] = 9;
	indices[14] = 10;
	indices[15] = 8;
	indices[16] = 10;
	indices[17] = 11;
	//right
	indices[18] = 12;
	indices[19] = 13;
	indices[20] = 14;
	indices[21] = 12;
	indices[22] = 14;
	indices[23] = 15;
	//top
	indices[24] = 16;
	indices[25] = 17;
	indices[26] = 18;
	indices[27] = 16;
	indices[28] = 18;
	indices[29] = 19;
	//down
	indices[30] = 20;
	indices[31] = 21;
	indices[32] = 22;
	indices[33] = 20;
	indices[34] = 22;
	indices[35] = 23;
}

ObjModel::ObjModel(const std::string& path, int texID)
{
	loadObjFile(path, texID);
}

void ObjModel::loadObjFile(const std::string& path, int texID)
{
	// obj loader.
	ifstream in;
	in.open(path, ifstream::in);
	if (in.fail())
	{
		std::cout << "Fail to load obj->" << path << std::endl;
	}
	string line;
	minPoint = Vector3D(+10000000000, +10000000000, +10000000000);
	maxPoint = Vector3D(-10000000000, -10000000000, -10000000000);
	vector<Vector3D> overtices;
	vector<Vector3D> onormals;
	vector<Vector2D> otexcoords;
	while (!in.eof())
	{
		getline(in, line);
		istringstream iss(line.c_str());
		char trash;
		//vertex
		if (!line.compare(0, 2, "v "))
		{
			iss >> trash;
			Vector3D vertex;
			iss >> vertex.x;
			iss >> vertex.y;
			iss >> vertex.z;
			overtices.push_back(vertex);
			if (minPoint.x > vertex.x)minPoint.x = vertex.x;
			if (minPoint.y > vertex.y)minPoint.y = vertex.y;
			if (minPoint.z > vertex.z)minPoint.z = vertex.z;
			if (maxPoint.x < vertex.x)maxPoint.x = vertex.x;
			if (maxPoint.y < vertex.y)maxPoint.y = vertex.y;
			if (maxPoint.z < vertex.z)maxPoint.z = vertex.z;
		}
		// normal
		else if (!line.compare(0, 3, "vn "))
		{
			iss >> trash >> trash;
			Vector3D normal;
			iss >> normal.x;
			iss >> normal.y;
			iss >> normal.z;
			normal.normalize();
			onormals.push_back(normal);
		}
		// texcoord
		else if (!line.compare(0, 3, "vt "))
		{
			iss >> trash >> trash;
			Vector2D texcoord;
			iss >> texcoord.x;
			iss >> texcoord.y;
			otexcoords.push_back(texcoord);
		}
		// face
		else if (!line.compare(0, 2, "f "))
		{
			iss >> trash;
			int index[3];
			while (iss >> index[0] >> trash >> index[1] >> trash >> index[2])
			{
				Vertex data;
				data.position = overtices[index[0] - 1];
				data.texcoord = otexcoords[index[1] - 1];
				data.normal = onormals[index[2] - 1];
				data.color = Vector4D(1.0, 1.0, 1.0, 1.0);
				data.textureID = texID;
				indices.push_back(vertices.size());
				vertices.push_back(data);
			}
		}
	}
	in.close();
}