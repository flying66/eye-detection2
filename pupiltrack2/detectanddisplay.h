#ifndef DETECTANDDISPLAY_H
#define DETECTANDDISPLAY_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
#include <vector>
#include "opencv2/objdetect/objdetect.hpp"
#include "mat2qimage.h"
#include "iostream"

using namespace std;
using namespace cv;

//vector<pair<Point,Point>> G_SRight;

void  detectAndDisplay(  Mat &frame, CvRect &box0,CvRect &box1 )//0左眼，1右眼
{
    //载入训练集

    //string eye_cascade_name="My_haarcascade_eyecascade.xml";//两个框的
    //string eye_cascade_name="haarcascade_eye_tree_eyeglasses588.xml";
    string eye_cascade_name="haarcascade_eye_tree_eyeglasses1070.xml";

    CascadeClassifier eye_cascade;
    if(!eye_cascade.load(eye_cascade_name)){
        printf("[error] no cascade\n");
    }


    std::vector<Rect> faces;

    Mat frame_gray;
    cvtColor( frame, frame_gray, CV_BGR2GRAY );//将图像转换为灰度图方便函数的后续处理。

    equalizeHist( frame_gray, frame_gray );//直方图均衡化，为了增强图像的对比度

    //face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30) );//检测眼睛的函数
    eye_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30,30) );//检测眼睛的函数,faces是检测得到的矩形的数量

    vector<pair<Point,Point>> Right;
    //vector<pair<Point,Point>> RightL;

    //画矩形
    //cvRectangle函数参数： 图片， 左上角， 右下角， 颜色， 线条粗细， 线条类型，点类型
    //cvRectangle( img, cvPoint(100, 100), cvPoint(200, 200), cvScalar(0, 0, 255), 3, 4, 0 );


    for( int i = 0; i < faces.size(); i++ )
    {
         if(faces.size()==2)
         {
             if(faces[1].x>faces[0].x)//1是右眼
             {
                 Point centera( faces[0].x,faces[0].y);
                 Point centerb( faces[0].x+faces[0].width,faces[0].y+faces[0].height );
                 Right.push_back(std::make_pair(centera,centerb));
                 rectangle(frame,centera,centerb,Scalar(0,255,0));//左眼
                 box0=faces[0];
                 Point centerc( faces[1].x,faces[1].y);
                 Point centerd( faces[1].x+faces[1].width,faces[1].y+faces[1].height );
                 Right.push_back(std::make_pair(centerc,centerd));
                 rectangle(frame,centerc,centerd,Scalar(255,0,0));//画右眼

                 box1=faces[1];//画右眼
             }
             else//否则0是右眼
             {
                 Point centera( faces[1].x,faces[1].y);
                 Point centerb( faces[1].x+faces[1].width,faces[1].y+faces[1].height );
                 Right.push_back(std::make_pair(centera,centerb));
                 rectangle(frame,centera,centerb,Scalar(0,255,0));
                 box0=faces[1];
                 Point centerc( faces[0].x,faces[0].y);
                 Point centerd( faces[0].x+faces[0].width,faces[0].y+faces[0].height );
                 Right.push_back(std::make_pair(centerc,centerd));
                 rectangle(frame,centerc,centerd,Scalar(255,0,0));

                 box1=faces[0];
             }
         }

         //当检测到第三个矩形时（一般是嘴），还是能保证只显示两个眼睛
         if(faces.size()==3)
         {
             if(faces[2].y-faces[1].y>faces[2].height)
             {
                 if(faces[2].y-faces[0].y>faces[2].height)//2不是眼睛
                 {
                     if(faces[1].x>faces[0].x)//1是右眼，0是左眼
                     {
                         Point centera( faces[0].x,faces[0].y);
                         Point centerb( faces[0].x+faces[0].width,faces[0].y+faces[0].height );
                         Right.push_back(std::make_pair(centera,centerb));
                         rectangle(frame,centera,centerb,Scalar(0,255,0));//左眼
                         box0=faces[0];
                         Point centerc( faces[1].x,faces[1].y);
                         Point centerd( faces[1].x+faces[1].width,faces[1].y+faces[1].height );
                         Right.push_back(std::make_pair(centerc,centerd));
                         rectangle(frame,centerc,centerd,Scalar(255,0,0));//右眼

                         box1=faces[1];
                     }
                     else//否则0是右眼
                     {
                         Point centera( faces[1].x,faces[1].y);
                         Point centerb( faces[1].x+faces[1].width,faces[1].y+faces[1].height );
                         Right.push_back(std::make_pair(centera,centerb));
                         rectangle(frame,centera,centerb,Scalar(0,255,0));
                         box0=faces[1];
                         Point centerc( faces[0].x,faces[0].y);
                         Point centerd( faces[0].x+faces[0].width,faces[0].y+faces[0].height );
                         Right.push_back(std::make_pair(centerc,centerd));
                         rectangle(frame,centerc,centerd,Scalar(255,0,0));

                         box1=faces[0];
                     }
                 }
             }
             else if(faces[0].y-faces[1].y>faces[0].height)
             {
                 if(faces[0].y-faces[2].y>faces[0].height)
                 {
                     if(faces[2].x>faces[1].x)//2是右眼，1是左眼
                     {
                         Point centera( faces[1].x,faces[1].y);
                         Point centerb( faces[1].x+faces[1].width,faces[1].y+faces[1].height );
                         Right.push_back(std::make_pair(centera,centerb));
                         rectangle(frame,centera,centerb,Scalar(0,255,0));//左眼
                         box0=faces[1];
                         Point centerc( faces[2].x,faces[2].y);
                         Point centerd( faces[2].x+faces[2].width,faces[2].y+faces[2].height );
                         Right.push_back(std::make_pair(centerc,centerd));
                         rectangle(frame,centerc,centerd,Scalar(255,0,0));//右眼

                         box1=faces[2];
                     }
                     else
                     {
                         Point centera( faces[2].x,faces[2].y);
                         Point centerb( faces[2].x+faces[2].width,faces[2].y+faces[2].height );
                         Right.push_back(std::make_pair(centera,centerb));
                         rectangle(frame,centera,centerb,Scalar(255,0,0));
                         box0=faces[2];
                         Point centerc( faces[1].x,faces[1].y);
                         Point centerd( faces[1].x+faces[1].width,faces[1].y+faces[1].height );
                         Right.push_back(std::make_pair(centerc,centerd));
                         rectangle(frame,centerc,centerd,Scalar(0,255,0));

                         box1=faces[1];
                     }
                 }
             }
             else if(faces[1].y-faces[0].y>faces[1].height)
             {
                 if(faces[1].y-faces[2].y>faces[1].height)
                 {
                     if(faces[2].x>faces[0].x)//2是右眼，0是左眼
                     {
                         Point centera( faces[0].x,faces[0].y);
                         Point centerb( faces[0].x+faces[0].width,faces[0].y+faces[0].height );
                         Right.push_back(std::make_pair(centera,centerb));
                         rectangle(frame,centera,centerb,Scalar(0,255,0));//左眼
                         box0=faces[0];
                         Point centerc( faces[2].x,faces[2].y);
                         Point centerd( faces[2].x+faces[2].width,faces[2].y+faces[2].height );
                         Right.push_back(std::make_pair(centerc,centerd));
                         rectangle(frame,centerc,centerd,Scalar(255,0,0));//右眼

                         box1=faces[2];
                     }
                     else
                     {
                         Point centera( faces[2].x,faces[2].y);
                         Point centerb( faces[2].x+faces[2].width,faces[2].y+faces[2].height );
                         Right.push_back(std::make_pair(centera,centerb));
                         rectangle(frame,centera,centerb,Scalar(255,0,0));
                         box0=faces[2];
                         Point centerc( faces[0].x,faces[0].y);
                         Point centerd( faces[0].x+faces[0].width,faces[0].y+faces[0].height );
                         Right.push_back(std::make_pair(centerc,centerd));
                         rectangle(frame,centerc,centerd,Scalar(0,255,0));

                         box1=faces[0];
                     }
                 }
             }
        }

////////////////////////////////////////当检测个数大于3时，保持只显示两个眼睛

        if(faces.size()>3)
        {
            int t1=0,t2=1;
            double min1=faces[0].y;
            for(int j=0;j<faces.size();j++)
            {
                if(faces[j].y<min1)
                {
                    min1=faces[j].y;
                    t1=j;
                }
            }
            double min2=faces[1].y;
            for(int k=0;k<faces.size();k++)
            {
                if(faces[k].y<min2 && k!=t1)
                {
                    min2=faces[k].y;
                    t2=k;
                }
            }
            if(faces[t1].x<faces[t2].x)//1是左眼，2是右眼
            {
                Point centera( faces[t1].x,faces[t1].y);
                Point centerb( faces[t1].x+faces[t1].width,faces[t1].y+faces[t1].height );
                Right.push_back(std::make_pair(centera,centerb));
                rectangle(frame,centera,centerb,Scalar(0,255,0));//左眼
                box0=faces[t1];
                Point centerc( faces[t2].x,faces[t2].y);
                Point centerd( faces[t2].x+faces[t2].width,faces[t2].y+faces[t2].height );
                Right.push_back(std::make_pair(centerc,centerd));
                rectangle(frame,centerc,centerd,Scalar(255,0,0));//画右眼
                box1=faces[t2];//画右眼
            }
        }

////////////////////////////////////////////////////
    }
}
#endif // DETECTANDDISPLAY_H
