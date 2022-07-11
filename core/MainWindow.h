#pragma once
#include "renderRoute.h"
#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include <QPainter>
#include <QTimer>
#include <QThread>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = Q_NULLPTR);
    ~MainWindow();

private:
    void paintEvent(QPaintEvent* event) override;
    void receiveFrame(unsigned char *buffer);
    void fpsTimeOut();

private:
    Ui::MainWindowClass *ui;
    QImage* canvas;
	QTimer* timer;
	QThread* loopThread;
	renderRoute* loop;
};
