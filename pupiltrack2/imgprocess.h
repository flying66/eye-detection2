#ifndef IMGPROCESS_H
#define IMGPROCESS_H


//建立imgProcess类
class ImgProcess
{
    private:
        Mat inimg;
        Mat outimg;

        Mat Leye;
        Mat Reye;
        Mat L2eye;
        Mat R2eye;
        Mat Leye_G;
        Mat Reye_G;
        Mat L2eye_G;
        Mat R2eye_G;

        CvRect drawing_box0;
        CvRect drawing_box1;
        vector<pair<Point,Point>> Right;

    public:
        vector<Vec3f> Lcircles;
        vector<Vec3f> Rcircles;
        vector<Vec3f> L2circles;
        vector<Vec3f> R2circles;
        ImgProcess(Mat image):inimg(image),drawing_box0(cvRect(0, 0, 50, 20)),drawing_box1(cvRect(0, 0, 50, 20)){} //(0,0,50,20)
        //ImgProcess(Mat image):inimg(image),drawing_box2(cvRect(0, 0, 50, 20)){} //(0,0,50,20)
        void EyeDetect();
        Mat Outputimg();
        void DisplayEye();
        Mat OutLeye();
        Mat OutReye();
        Mat OutL2eye();
        Mat OutR2eye();
        Mat LEdgeDetect(Mat &edgeimg);
        Mat REdgeDetect(Mat &edgeimg);
        Mat L2EdgeDetect(Mat &edgeimg);
        Mat R2EdgeDetect(Mat &edgeimg);

        void EyeEdge();
        vector<Vec3f> LHough(Mat &midImage);
        vector<Vec3f> RHough(Mat &midImage);
        void FindCenter();
        Mat PlotC(vector<Vec3f> circles,Mat &midImage);
};

#endif // IMGPROCESS_H
