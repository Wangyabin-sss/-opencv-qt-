#include "mainwindow.h"
#include "ui_mainwindow.h"

int cannynum=80;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    cv::Mat src = cv::imread("/root/car0.jpg");   //读取图像
    if (!src.data) {
            std::cout<<"could not load image...\n"<<std::endl;
            delete ui;
    }
    //cv::imshow("原图像",src);
    /* BGR转换为HSV,方便后续操作 */
    cv::Mat hsv,hsvchannels[3],Threshold;
    cv::cvtColor(src,hsv,cv::COLOR_BGR2HSV);
    //cv::imshow("cvtcolor",hsv);

    cv::split(hsv, hsvchannels); //HSV颜色通道分离
    cv::threshold(hsvchannels[1],Threshold,150, 255, cv::THRESH_BINARY);  //颜色通道1阈值化
    //cv::imshow("阈值化",Threshold);

    /* 形态学处理 */
    cv::Mat erode,dilate;
    cv::Mat structureElement = cv::getStructuringElement(cv::MORPH_RECT,cv::Size(2,2)); //创造用于腐蚀膨胀的内核形状
    cv::erode(Threshold,erode,structureElement,cv::Point(-1,-1),2);   //腐蚀
    cv::dilate(erode, dilate, structureElement,cv::Point(-1,-1),3);    //膨胀
    //cv::imshow("腐蚀",erode);
    //cv::imshow("膨胀",dilate);
    //QImage temp= Mat2QImage(src);
    //ui->label->setPixmap(QPixmap::fromImage(temp).scaled(ui->label->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation)); //将图片显到qt界面

    //取出蓝色部分
    cv::Mat dust,srcrange;
    hsv.copyTo(dust,dilate);
    cv::inRange(dust,cv::Scalar(100,43,46),cv::Scalar(124,255,255),srcrange);
    //cv::imshow("蓝色部分",srcrange);

    //查找轮廓
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(srcrange,contours,hierarchy,cv::RETR_EXTERNAL,cv::CHAIN_APPROX_SIMPLE,cv::Point(0,0));
/*  //绘制所有点组成的轮廓
    for(size_t i=0;i<contours.size();i++)
    {
        //绘制轮廓
        cv::drawContours(src,contours,i,cv::Scalar(0,0,255),1,8,hierarchy);
    }
    std::cout<<contours.size()<<std::endl;
    cv::imshow("轮廓",src);
*/  //拟合最外围矩形
    std::vector<std::vector<cv::Point>> contours_ploy(contours.size());
    std::vector<cv::Rect> ploy_rects(contours.size());
    for (size_t i = 0; i < contours.size(); i++)
    {
        cv::approxPolyDP(cv::Mat(contours[i]), contours_ploy[i], 4, true);  //简化点
        ploy_rects[i] = cv::boundingRect(contours_ploy[i]);   //拟合最外围矩形
        std::cout<<ploy_rects[i].area()<<std::endl;
    }
    cv::Mat rectROI;  //车牌ROI感兴趣区域
    for (size_t t = 0; t < contours.size(); t++)
    {
        if(ploy_rects[t].width>100&&ploy_rects[t].width<200)
        {
            rectangle(src, ploy_rects[t], cv::Scalar(0,0,255), 2, 8);   //在车牌处用矩形框出来
            cv::Mat rectroi(src,ploy_rects[t]);
            rectROI = rectroi.clone();
        }
    }
    //cv::imshow("矩形轮廓",src);
    //cv::imshow("轮廓",rectROI);

    cv::Mat ROIgray,ROIbin;
    cv::cvtColor(rectROI,ROIgray,cv::COLOR_BGR2GRAY);
    //cv::imshow("车牌灰度图",ROIgray);
    cv::threshold(ROIgray,ROIbin,150, 255, cv::THRESH_BINARY);  //二值化
    //cv::imshow("车牌二值化",ROIbin);
    QImage temp= Mat2QImage(src);
    ui->label->setPixmap(QPixmap::fromImage(temp).scaled(ui->label->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation)); //将图片显到qt界面
}

MainWindow::~MainWindow()
{
    delete ui;
}

//mat转QImage格式（直接调用即可）
QImage  Mat2QImage(cv::Mat& cvImg)
{
    QImage qImg;
    if(cvImg.channels()==3)                        //3 channels color image
    {

        cv::cvtColor(cvImg,cvImg,cv::COLOR_BGR2RGB);
        qImg =QImage((const unsigned char*)(cvImg.data),
                    cvImg.cols, cvImg.rows,
                    cvImg.cols*cvImg.channels(),
                    QImage::Format_RGB888);
    }
    else if(cvImg.channels()==1)                    //grayscale image
    {
        qImg =QImage((const unsigned char*)(cvImg.data),
                    cvImg.cols,cvImg.rows,
                    cvImg.cols*cvImg.channels(),
                    QImage::Format_Indexed8);
    }
    else
    {
        qImg =QImage((const unsigned char*)(cvImg.data),
                    cvImg.cols,cvImg.rows,
                    cvImg.cols*cvImg.channels(),
                    QImage::Format_RGB888);
    }

    return qImg;

}




