#include "renderRoute.h"

renderRoute::renderRoute(int w, int h, QObject* parent)
	: QObject(parent), width(w), height(h), channel(4), fps(0)
{
	stopped = false;
	pipeline = new pipeLine(width, height);
}


void renderRoute::loop()
{
	pipeline->initialize();
	//Vector3D v1(2, -2, 0), v2(-2, -2, 0), v3(0, 1.8, 0);
	camera* myCam = new camera;

	Mesh* msh = new Mesh;
	//msh->setTriangle(v1, v2, v3);	
	//msh->setBox(2.0f, 2.0f, 2.0f);

	ObjModel* obj = new ObjModel();
	//string path01 = "D:/C++project/easySoftRender/easySoftRender/model/african_head.obj";
	//string path02 = "D:/C++project/easySoftRender/easySoftRender/model/african_head_eye_inner.obj";
	string path03 = "D:/C++project/easySoftRender/easySoftRender/model/monster/diablo3_pose.obj";
	//obj->loadObjFile(path01, 3);
	//obj->loadObjFile(path02, 1);
	obj->loadObjFile(path03, 4);

	pipeline->setVertexBuffer(obj->vertices);
	pipeline->setIndexBuffer(obj->indices);

	msh->setGround();
	pipeline->setVertexBuffer(msh->vertices);
	pipeline->setIndexBuffer(msh->indices);
	
	pipeline->SetViewport(0, 0, 1280, 880);
	fps = 0;
	float angle = 0.f;

	camera* lightCam = new camera;
	lightCam->position = Vector3D(18.f, 10.f, 5.f);
	pipeline->setCamera(lightCam);
	pipeline->drawIndex(pipeLine::fill);
	pipeline->setShadowAtri();
	pipeline->swapBuffer();

	pipeline->setCamera(myCam);
	while (!stopped)
	{
		pipeline->clearBuffer(Vector4D(0.502f, 0.698f, 0.800f, 1.0f), true);
		pipeline->drawIndex(pipeLine::fill);
		pipeline->swapBuffer();
		emit frameOut(pipeline->output());
		myCam->rotateY(0.02f);
		pipeline->setCamera(myCam);
		//pipeline->setRotation(angle);  
		angle += 0.02f;
		fps++;
	}
	delete msh;
	delete obj;
	delete myCam;
	msh = nullptr;
	obj = nullptr;
	myCam = nullptr;
}