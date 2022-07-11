#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindowClass)
{
    ui->setupUi(this);
	this->resize(1280, 880);
	loop = new renderRoute(width(), height(), nullptr);
	loopThread = new QThread(this);
	
	timer = new QTimer;
	connect(timer, &QTimer::timeout, this, &MainWindow::fpsTimeOut);
	
	loop->moveToThread(loopThread);
	connect(loopThread, &QThread::finished, loop, &renderRoute::deleteLater);
	connect(loopThread, &QThread::started, loop, &renderRoute::loop);
	connect(loop, &renderRoute::frameOut, this, &MainWindow::receiveFrame);
	
	loopThread->start();
	timer->start(1000);
}

void MainWindow::paintEvent(QPaintEvent* event)
{
	if (canvas)
	{
		QPainter painter(this);
		painter.drawImage(0, 0, *canvas);
	}
	QWidget::paintEvent(event);
}

void MainWindow::receiveFrame(unsigned char* buffer)
{
	if (canvas) delete canvas;
	canvas = new QImage(buffer, width(), height(), QImage::Format_RGBA8888);
	update();
}

void MainWindow::fpsTimeOut()
{
	int fps = loop->getFps();
	loop->setFpsZero();
	this->setWindowTitle(QString(" fps: %1").arg(fps));
}

MainWindow::~MainWindow()
{
	delete ui;
	loop->stopIt();
	loopThread->quit();
	loopThread->wait();
	if (canvas) delete canvas;
	if (loopThread) delete loopThread;
	loop = nullptr;
	canvas = nullptr;
	loopThread = nullptr;
}