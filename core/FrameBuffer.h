#pragma once
#include "maths.h"

class FrameBuffer
{
private:
	int width, height, channel;
	std::vector<unsigned char> buffer;
	std::vector<double> depthBuffer;

public:
	FrameBuffer(int width, int height);
	~FrameBuffer() = default;

public:
	int getWidth() { return width; };
	int getHeigth() { return height; };
	int geiChannel() { return channel; };
	unsigned char* getBufferData() { return buffer.data(); };

	void fillBuffer(const Vector4D &color);
	void drawPixel(int x, int y, const Vector4D & color);

	void fillDepthBuffer();
	double getDepth(const unsigned int& x, const unsigned int& y) const;
	void drawDepth(const unsigned int& x, const unsigned int& y, const double& value);
};

