#pragma once
#include "QObject"
#include "pipeLine.h"

class renderRoute : public QObject
{
	Q_OBJECT
public:
	explicit renderRoute(int w, int h, QObject* parent = nullptr);
	~renderRoute() {}
	void stopIt() { stopped = true; }
	void setFpsZero() { fps = 0; }
	int getFps() { return fps; }

signals:
	void frameOut(unsigned char* image);

public slots:
	void loop();

private:
	bool stopped;
	int width, height, channel;
	pipeLine* pipeline;
	int fps;
};

