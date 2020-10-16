#ifndef _HEADER_H_TRANSFORM_
#define _HEADER_H_TRANSFORM_
//This header document provides some function for position_transform to finish the homework.
#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include <fstream>
using namespace std;
using namespace cv;
class Pos_Trans {
private:
    vector<vector<Point2f>> cornersvec;
    vector<vector<Point3f>> objectpoints;
    double width;
    int numofphoto;
    Size boardsize;
    Size wholesize;


    vector<Mat> pnp_rmatrics;
    vector<Mat> pnp_tvecs;
    Mat tri_objectpoints;
    double getDistance(const vector<Point2f> &p1,const vector<Point2f> &p2);
    vector<Point2f> I2C(const vector<Point2f>&);

public:
    Mat cameraMatrix;//camera inner coef
    Mat DistCoeffs;//jibian
    vector<Mat> rvecs;//R
    vector<Mat> tvecs;//T

    vector<double> out_coef, in_coef, err;

    Pos_Trans(double w= 17, int n= 41,int r=6,int c=9,int pw=1280,int ph=720) :
            width(w),numofphoto(n),boardsize(c,r),wholesize(pw,ph){}
    double getCoef();
    vector<Point2f> getimgposition(const vector<Point3f> &real,int i=0);//'i' is the number of the Transposion Matrix.
    double error();
    void pnp();
    void output_pnp(int flag=1);//if flag = -1,then output all the vecs.
    void triangle_evalation();
};

#endif