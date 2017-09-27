#include "widget.h"
#include "ui_widget.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <vector>
#include <QSettings>
#include <QTextCodec>
#include <QDebug>
#include "opencv2/objdetect/objdetect.hpp"
#include "detectanddisplay.h"
#include "mat2qimage.h"
#include "iostream"
#include "imgprocess.h"
#include <QFileDialog>
#include "QString"
///////////////////////用于打开文件路径
#include <QFileDialog>
#include <QMessageBox>
///////////////////////
using namespace std;
using namespace cv;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

int Lthreshold=50;
int Rthreshold=50;

/*
int setLIniFile()
{
    QString strPath = QCoreApplication::applicationDirPath();
    if(strPath.right(1) != "/" && strPath.right(1) != "\\")
    {
        strPath = strPath + "/";
    }
    //m_sTmp = strPath.toStdString();
    //g_szCurModule = m_sTmp.c_str();
    //m_strCFGPath.sprintf("%s%s", g_szCurModule, PATHOFQUSTION);
    strPath += "Lthreshold.ini";
    QSettings *readCFG = new QSettings(strPath, QSettings::IniFormat);
    QString g_strAnYes;
    readCFG->setIniCodec(QTextCodec::codecForName("GBK"));
    QString strLini = "Lthreshold";
    QString strvalue ="/value";
    g_strAnYes = readCFG->value(strLini+strvalue).toByteArray();


    //QSettings *settings = new QSettings ("Lthreshold",QSettings::IniFormat);
    //int Lthreshold=settings->value("Lthreshold",50).toInt();
    //qDebug() <<g_strAnYes<<strLini;

    return g_strAnYes.toInt();
    //delete settings;
}

int setRIniFile()
{
    QString strPath = QCoreApplication::applicationDirPath();
    if(strPath.right(1) != "/" && strPath.right(1) != "\\")
    {
        strPath = strPath + "/";
    }
    strPath += "Rthreshold.ini";
    QSettings *readCFG = new QSettings(strPath, QSettings::IniFormat);
    QString g_strAnYes;
    readCFG->setIniCodec(QTextCodec::codecForName("GBK"));
    QString strLini = "Rthreshold";
    QString strvalue ="/value";
    g_strAnYes = readCFG->value(strLini+strvalue).toByteArray();
    //qDebug() <<g_strAnYes<<strLini;
    return g_strAnYes.toInt();
    //delete settings;
}
*/
void ImgProcess::DisplayEye()//将两个眼睛分开
{
    detectAndDisplay(inimg, drawing_box0,drawing_box1);
    //outimg=inimg;
    if(drawing_box0.width>0&&drawing_box1.width>0)
    {
         Leye=inimg(drawing_box0);
         Reye=inimg(drawing_box1);
         L2eye=inimg(drawing_box0);
         R2eye=inimg(drawing_box1);
    }
}

void ImgProcess::EyeDetect()//检测眼睛,调用检测函数
{
    detectAndDisplay( inimg, drawing_box0,drawing_box1 );//0左眼，1右眼
    outimg=inimg;
}


/////////////////////////////////////////////检测眼睛的边缘
Mat ImgProcess::LEdgeDetect(Mat &edgeimg)//边缘检测
{
    Mat edgeout;
    cvtColor(edgeimg,edgeimg,CV_BGR2GRAY);//图像灰度化
    GaussianBlur( edgeimg,edgeimg, Size(9, 9), 2, 2 );//Size(9,9),2,2,高斯平滑，减小噪声误差
/////////////////////////将图像进行二值化处理
    //threshold(edgeimg,edgeimg,75,255,CV_THRESH_BINARY);
/////////////////////////
    equalizeHist( edgeimg, edgeimg );//直方图均衡化，为了增加图像的对比度
    Canny(edgeimg,edgeout,100,150,3);//原来是50,150,3
    return edgeout;
}

Mat ImgProcess::REdgeDetect(Mat &edgeimg)//边缘检测
{
    Mat edgeout;
    cvtColor(edgeimg,edgeimg,CV_BGR2GRAY);//图像灰度化
    GaussianBlur( edgeimg,edgeimg, Size(9, 9), 2, 2 );//Size(9,9),2,2,高斯平滑，减小噪声误差
/////////////////////////将图像进行二值化处理

    //threshold(edgeimg,edgeimg,50,255,CV_THRESH_BINARY);//50好些

/////////////////////////

    equalizeHist( edgeimg, edgeimg );//直方图均衡化，为了增加图像的对比度
    Canny(edgeimg,edgeout,50,150,3);//原来是50,150,3
    return edgeout;
}

Mat ImgProcess::L2EdgeDetect(Mat &edgeimg)//边缘检测, 进行二值化处理
{
    Mat edgeout;
    cvtColor(edgeimg,edgeimg,CV_BGR2GRAY);//图像灰度化
    GaussianBlur( edgeimg,edgeimg, Size(9, 9), 2, 2 );//Size(9,9),2,2,高斯平滑，减小噪声误差

/////////////////////////将图像进行二值化处理

    //threshold(edgeimg,edgeimg,85,255,CV_THRESH_BINARY);

/////////////////////////

    equalizeHist( edgeimg, edgeimg );//直方图均衡化，为了增加图像的对比度

    threshold(edgeimg,edgeimg,Lthreshold,255,CV_THRESH_BINARY);

    Canny(edgeimg,edgeout,50,150,3);//原来是50,150,3
    return edgeout;
}
Mat ImgProcess::R2EdgeDetect(Mat &edgeimg)//边缘检测,进行二值化处理
{
    Mat edgeout;
    cvtColor(edgeimg,edgeimg,CV_BGR2GRAY);//图像灰度化
    GaussianBlur( edgeimg,edgeimg, Size(9, 9), 2, 2 );//Size(9,9),2,2,高斯平滑，减小噪声误差
/////////////////////////将图像进行二值化处理

    //threshold(edgeimg,edgeimg,50,255,CV_THRESH_BINARY);//50好些

/////////////////////////
    equalizeHist( edgeimg, edgeimg );//直方图均衡化，为了增加图像的对比度

    threshold(edgeimg,edgeimg,Rthreshold,255,CV_THRESH_BINARY);//50好些

    Canny(edgeimg,edgeout,50,150,3);//原来是50,150,3
    return edgeout;
}


void ImgProcess::EyeEdge()//检测眼睛的边缘
{
    Leye_G=LEdgeDetect(Leye);
    Reye_G=REdgeDetect(Reye);
    L2eye_G=L2EdgeDetect(L2eye);
    R2eye_G=R2EdgeDetect(R2eye);
}
//////////////////////////////////////////////

vector<Vec3f> ImgProcess::LHough(Mat &midImage)//利用Hough变换画圆
{
    vector<Vec3f> circles;
    //霍夫变换的第五个参数是不同圆之间的最小距离。
    //当设置最小的圆的半径是drawing_box.height/5时，左眼瞳孔定位较好;/8也较好
    HoughCircles( midImage, circles, CV_HOUGH_GRADIENT,1.5, 50, 100,20, 6,12 );//1.5,5,100,20,drawing_box.height/6, drawing_box.height/4
    return circles;
}
vector<Vec3f> ImgProcess::RHough(Mat &midImage)//利用Hough变换画圆
{
    vector<Vec3f> circles;
    //霍夫变换的第五个参数是不同圆之间的最小距离。
    HoughCircles( midImage, circles, CV_HOUGH_GRADIENT,1.5, 50, 100,20, 7,12 );//1.5,5,100,20,drawing_box.height/6, drawing_box.height/4
    return circles;
}

///////////////////////////////////////////////
Mat ImgProcess::PlotC(vector<Vec3f> circles,Mat &midImage)//求圆心
 {
     for( size_t i = 0; i < circles.size(); i++ )
       {
         Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
         int radius = cvRound(circles[i][2]);
         circle( midImage, center, 1, Scalar(255,0,0), -1,8);
         circle( midImage, center, radius, Scalar(255,0,0), 1,8 );
       }
     return midImage;
 }

void ImgProcess::FindCenter()
{
    //Lcircles=LHough(Leye_G);
    //Rcircles=RHough(Reye_G);
    L2circles=LHough(L2eye_G);
    R2circles=RHough(R2eye_G);
    //Leye=PlotC(Lcircles,Leye);
    //Reye=PlotC(Rcircles,Reye);
    L2eye=PlotC(L2circles,L2eye);
    R2eye=PlotC(R2circles,R2eye);
}


/////////////////////////////////////////显示眼睛


Mat ImgProcess::OutLeye()
{
    return Leye;
}
Mat ImgProcess::OutReye()
{
    return Reye;
}
Mat ImgProcess::OutL2eye()
{
    return L2eye;
}
Mat ImgProcess::OutR2eye()
{
    return R2eye;
}

Mat ImgProcess::Outputimg()
{
    return outimg;
}
//////////////////////////////////////////

void Widget::on_pushButton_clicked()//打开摄像头
{
    VideoCapture cap(0);

    if(!cap.isOpened())
    {
       cout<<"no cap"<<endl;
    }
    Mat frame;
    while(!Lstop)
    {
        cap>>frame;//将摄像头的当前帧输出到frame
        ImgProcess pro(frame);//建立视频处理类
        pro.EyeDetect();//人眼检测
        Mat image=pro.Outputimg();//输出检测图像
        imshow( "camera", image );
        QImage img=Mat2QImage(image);//将mat格式转换为Qimage格式
        ui->label->setPixmap(QPixmap::fromImage(img));//将结果在label上显示

        pro.DisplayEye();
        pro.EyeEdge();//瞳孔边缘检测
        pro.FindCenter();//hough变换求圆心

        Mat mleye=pro.OutLeye();//输出瞳孔定位结果
        QImage qleye=Mat2QImage(mleye);
        ui->label_2->setPixmap(QPixmap::fromImage(qleye));
        ui->label_2->setScaledContents(true);

        Mat mreye=pro.OutReye();
        QImage qreye=Mat2QImage(mreye);
        ui->label_3->setPixmap(QPixmap::fromImage(qreye));
        ui->label_3->setScaledContents(true);

        Mat ml2eye=pro.OutL2eye();//输出瞳孔定位结果,二值化处理过的
        QImage ql2eye=Mat2QImage(ml2eye);
        ui->label_4->setPixmap(QPixmap::fromImage(ql2eye));
        ui->label_4->setScaledContents(true);

        Mat mr2eye=pro.OutR2eye();
        QImage qr2eye=Mat2QImage(mr2eye);
        ui->label_5->setPixmap(QPixmap::fromImage(qr2eye));
        ui->label_5->setScaledContents(true);


        waitKey(5);
    }
    //cvDestroyWindow("camera");
}

void Widget::on_pushButton_2_clicked()//关闭摄像头
{
    Lstop=true;
}

void Widget::on_pushButton_3_clicked()//打开本地图片
{

    Mat image0;
    image0=cv::imread("102.jpg");//图片的路径
    ImgProcess pro(image0);
    pro.EyeDetect();
    Mat image=pro.Outputimg();
    QImage img=Mat2QImage(image);

    ui->label->setPixmap(QPixmap::fromImage(img));
    ui->label->setScaledContents(true);//将图片显示到Label中，并调整到合适的大小

    pro.DisplayEye();
    pro.EyeEdge();
    pro.FindCenter();

    Mat mleye=pro.OutLeye();//输出瞳孔定位结果
    QImage qleye=Mat2QImage(mleye);
    ui->label_2->setPixmap(QPixmap::fromImage(qleye));
    ui->label_2->setScaledContents(true);

    Mat mreye=pro.OutReye();
    QImage qreye=Mat2QImage(mreye);
    ui->label_3->setPixmap(QPixmap::fromImage(qreye));
    ui->label_3->setScaledContents(true);

    Mat ml2eye=pro.OutL2eye();//输出瞳孔定位结果,二值化处理过的
    QImage ql2eye=Mat2QImage(ml2eye);
    ui->label_4->setPixmap(QPixmap::fromImage(ql2eye));
    ui->label_4->setScaledContents(true);

    Mat mr2eye=pro.OutR2eye();
    QImage qr2eye=Mat2QImage(mr2eye);
    ui->label_5->setPixmap(QPixmap::fromImage(qr2eye));
    ui->label_5->setScaledContents(true);

    //QString filename =QFileDialog::getOpenFileName(this,tr("打开文件")," ",tr("Image file(*.bmp *.jpg)"),0);
      /*
    QString path = QFileDialog::getOpenFileName(this, tr("Open Image"), " ", tr("Image Files(*.jpg *.png)"),0);
    if(path.length() == 0)
    {
        QMessageBox::information(NULL, tr("Path"), tr("You didn't select any files."));
    } else
    {
        QMessageBox::information(NULL, tr("Path"), tr("You selected ") + path);
    }

    ui->label->setPixmap(QPixmap::fromImage(path));
    ui->label->setScaledContents(true);//将图片显示到Label中，并调整到合适的大小
      */

    waitKey(1000);
}

void Widget::on_pushButton_5_clicked()//减小左眼睛的阈值
{
    Lthreshold=Lthreshold-2;
    ui->lcdNumber->display(Lthreshold);
}

void Widget::on_pushButton_4_clicked()//增加左眼睛的阈值
{
    Lthreshold=Lthreshold+2;
    ui->lcdNumber->display(Lthreshold);
}

void Widget::on_pushButton_6_clicked()//减小右眼睛的阈值
{
    Rthreshold=Rthreshold-2;
    ui->lcdNumber_2->display(Rthreshold);
}

void Widget::on_pushButton_7_clicked()//增加右眼睛的阈值
{
    Rthreshold=Rthreshold+2;
    ui->lcdNumber_2->display(Rthreshold);
}
