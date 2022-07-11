#include "FrameBuffer.h"

FrameBuffer::FrameBuffer(int w, int h) : width(w), height(h), channel(4)
{
	buffer.resize(width * height * channel, 255);
	depthBuffer.resize(width * height, 1.0);
}

void FrameBuffer::fillBuffer(const Vector4D& color)
{
	unsigned char red = static_cast<unsigned char>(color.x * 255);
	unsigned char green = static_cast<unsigned char>(color.y * 255);
	unsigned char blue = static_cast<unsigned char>(color.z * 255);
	unsigned char alpha = static_cast<unsigned char>(color.w * 255);

	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			buffer[i * width * channel + j * channel + 0] = red;
			buffer[i * width * channel + j * channel + 1] = green;
			buffer[i * width * channel + j * channel + 2] = blue;
			buffer[i * width * channel + j * channel + 3] = alpha;
		}
	}
}

void FrameBuffer::drawPixel(int x, int y, const Vector4D& color)
{
	if (x >= width || y >= height || x < 0 || y < 0) return;

	unsigned char red = static_cast<unsigned char>(color.x * 255);
	unsigned char green = static_cast<unsigned char>(color.y * 255);
	unsigned char blue = static_cast<unsigned char>(color.z * 255);
	unsigned char alpha = static_cast<unsigned char>(color.w * 255);
	int index = y * width * channel + x * channel;

	buffer[index + 0] = red;
	buffer[index + 1] = green;
	buffer[index + 2] = blue;
	buffer[index + 3] = alpha;
}

void FrameBuffer::fillDepthBuffer()
{
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			depthBuffer[i * width  + j] = 1.0;
		}
	}
}

double FrameBuffer::getDepth(const unsigned int& x, const unsigned int& y) const
{
	if (x < 0 || y < 0 || x >= width || y >= height) return 0.0;
	return depthBuffer[y * width + x];
}

void FrameBuffer::drawDepth(const unsigned int& x, const unsigned int& y, const double& value)
{
	if (x < 0 || y < 0 || x >= width || y >= height) return;
	depthBuffer[y * width + x] = value;
}
