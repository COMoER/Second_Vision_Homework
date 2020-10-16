#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include "position_transform.h"
using namespace std;
using namespace cv;
/*
//for post homework
int main()
{
    Pos_Trans c(17,41,6,9,1280,720);
    cout<<"Error is "<<c.getCoef()<<endl;
    cout<<"CameraMatrix:\n"<<c.cameraMatrix<<endl;
    cout<<"DistMatrix:"<<c.DistMatrix;
    vector<Point3f> p;
    p.push_back(Point3f(17,17,0));
    cout<<"\n(17,17,0) real->"<<c.getimgposition(p)[0]<<"image(in 0.jpg)\n";
    cout<<"Error(computed by myself) is "<<c.error();//I compute it myself.It is equal to the return value of the function.
    return 0;
}
*/
int main()
{
    Pos_Trans c(17,41,6,9,1280,720);
    c.getCoef();
    c.pnp();
    c.output_pnp(-1);
    c.triangle_evalation();
    return 0;
}