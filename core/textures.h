#pragma once
#include <QImage>
#include "maths.h"
#include <QString>
#include <QMainWindow>

class textures
{
private:
	int width, height, channel;
	QImage* pixelBuffer;

public:
	textures() : width(0), height(0), channel(0), pixelBuffer(nullptr) {};
	~textures();

	void loadImage(QString &path);
	Vector4D sample(const Vector2D &texture);
};

