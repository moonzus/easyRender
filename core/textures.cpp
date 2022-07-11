#include "textures.h"
#include "QDebug"

textures::~textures()
{
	if (pixelBuffer) delete pixelBuffer;
	pixelBuffer = nullptr;
}

void textures::loadImage(QString& path)
{
	pixelBuffer = new QImage();
	pixelBuffer->load(path);
	width = pixelBuffer->width();
	height = pixelBuffer->height();
	channel = 3;
}

Vector4D textures::sample(const Vector2D& texture)
{
	Vector4D res(0.0, 0.0, 0.0, 1.0);
	if (pixelBuffer == nullptr) return res;
	unsigned int x = 0, y = 0;
	float factorU = 0.0, factorV = 0.0;

	if (texture.x >= 0.0f && texture.x <= 1.0f && texture.y >= 0.0f && texture.y <= 1.0f) {
		float trueU = texture.x * (width - 1);
		float trueV = texture.y * (height - 1);
		x = static_cast<unsigned int>(trueU);
		y = static_cast<unsigned int>(trueV);
		factorU = trueU - x;
		factorV = trueV - y;
	}
	else {
		float u = texture.x, v = texture.y;
		if (texture.x > 1.0f) u -= static_cast<unsigned int>(texture.x);
		if (texture.x < 0.0f) u = 1.0f - (static_cast<unsigned int>(texture.x) - texture.x);
		if (texture.y > 1.0f) v -= static_cast<unsigned int>(texture.y);
		if (texture.y < 0.0f) u = 1.0f - (static_cast<unsigned int>(texture.y) - texture.y);
		float trueU = u * (width - 1);
		float trueV = v * (height - 1);
		x = static_cast<unsigned int>(trueU);
		y = static_cast<unsigned int>(trueV);
		factorU = trueU - x;
		factorV = trueV - y;
	}

	res.x = static_cast<float>(pixelBuffer->pixelColor(x, y).red()) / 255;
	res.y = static_cast<float>(pixelBuffer->pixelColor(x, y).green()) / 255;
	res.z = static_cast<float>(pixelBuffer->pixelColor(x, y).blue()) / 255;
	return res;
}
