#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <opencv.hpp>
#include <highgui.hpp>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};

QImage  Mat2QImage(cv::Mat& cvImg);
std::vector<cv::Mat> ROI_strcat(cv::Mat& ROIbin);

#endif // MAINWINDOW_H
