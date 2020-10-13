//
// Created by zj on 2020/10/13.
//
#include "position_transform.h"
double Pos_Trans::getDistance(const vector<Point2f> &p1,const vector<Point2f> &p2)
{
    if(p1.size()!=p2.size())return -1;

    double sum=0;
    for(int i=0;i<p1.size();++i)
        sum+=powf((p1[i].x-p2[i].x),2)+powf((p1[i].y-p2[i].y),2);
    return sum/p1.size();
}

double Pos_Trans::error()//RMS
{
    double sum=0;
    for(int i=0;i<objectpoints.size();++i)
        sum+=getDistance(getimgposition(objectpoints[i],i),cornersvec[i]);
    return sqrt(sum/objectpoints.size());
}

double Pos_Trans::getCoef() {
    for (int no = 0;no < numofphoto; ++no) {
        Mat chess;
        vector<Point2f> corners;
        //document's path
        char r[30];
        sprintf(r,"../chess/%d.jpg",no);

        chess = imread(r);
        if (chess.empty())return -1;
        Mat chess_Gray;//single 8-bit Gray Image as the input image will improve the precision
        cvtColor(chess, chess_Gray, COLOR_BGR2GRAY);

        findChessboardCorners(chess_Gray, boardsize, corners);
        find4QuadCornerSubpix(chess_Gray, corners,
                              Size(5, 5));//Region Size is the size of the region to optimize the subpix
        cornersvec.push_back(corners);
        /*
        drawChessboardCorners(chess, Size(9, 6), corners, 1);
        imshow("1", chess);//But mark on the origin photo
        waitKey(0);
        */
        objectpoints.push_back(vector<Point3f>());

        //give the real world position

        for (int i = 1; i <= boardsize.height; ++i)
            for (int j = 1; j <= boardsize.width; ++j)
                objectpoints[no].push_back(Point3f(width * j, width * i, 0));
    }
    return calibrateCamera(objectpoints, cornersvec, wholesize, cameraMatrix, DistMatrix, rvecs,
                           tvecs, in_coef, out_coef, err,CALIB_FIX_PRINCIPAL_POINT);
}

vector<Point2f> Pos_Trans::getimgposition(const vector<Point3f> &real,int i)
{
    vector<Point2f> img;
    projectPoints(real,rvecs[i],tvecs[i],cameraMatrix,DistMatrix,img);
    return img;
}
void Pos_Trans::pnp() {

    for (int i = 0; i < numofphoto; ++i) {
        pnp_rmatrics.push_back(Mat());
        pnp_tvecs.push_back(Mat());
        //r_{w->c} t_{w->c}
        solvePnP(objectpoints[i], cornersvec[i], cameraMatrix, DistMatrix,
                 pnp_rmatrics[i], pnp_tvecs[i]);
        Rodrigues(pnp_rmatrics[i],pnp_rmatrics[i]); //Rvec2Rmatrix
    }
}
void Pos_Trans::output_pnp(int flag) {
    char text1[50], text2[50];
    //output
    ofstream file;
    file.open("output.txt");
    if(flag==-1)
    for(int i=0;i < numofphoto;++i){
        sprintf(text1,"The R in %d.jpg is\n",i);
        sprintf(text2,"\nThe tvec in %d.jpg is\n",i);
        file<<text1<<pnp_rmatrics[i]<<text2<<pnp_tvecs[i]<<endl;

    }
    else if(flag>=0&&flag<numofphoto) {
        sprintf(text1, "The R in %d.jpg is\n", flag);
        sprintf(text2, "\nThe tvec in %d.jpg is\n", flag);
        cout << text1 << pnp_rmatrics[0] << text2 << pnp_tvecs[flag] << endl;
    }
    else cerr<<"Over the range!";
    file.close();
}
vector<Point2f> Pos_Trans::I2C(const vector<Point2f>&ip)
{
    vector<Point2f> cp;
    for(int i=0;i<ip.size();++i) {
        Point3d A(ip[i].x,ip[i].y,1.0);

        Mat B=cameraMatrix.inv()*Mat(A);//K^(-1)*A
        Point3f C(B);
        cp.push_back(Point2f(C.x,C.y));
    }

    return cp;
}
void Pos_Trans::triangle_evalation()
{
    //according to the first and the second photo as a double-perspective camera
    Mat r_1(3,4,5),r_2(3,4,5);//enum{CV_32F:5}
    //3*4 [R,t]
    hconcat(pnp_rmatrics[0],pnp_tvecs[0],r_1);
    hconcat(pnp_rmatrics[1],pnp_tvecs[1],r_2);
    I2C(cornersvec[0]);
    triangulatePoints(r_1,r_2,I2C(cornersvec[0]),I2C(cornersvec[1]),tri_objectpoints);
    for(int i=0;i<tri_objectpoints.cols;++i)
        tri_objectpoints.col(i)/=tri_objectpoints.at<float>(3,i);//w to 1
    ofstream file;
    file.open("tri_output.txt");

    file<<"The Point Matrix(4*N) is\n"<<tri_objectpoints<<endl;
    file<<"Suppose:\n"<<objectpoints[0]<<endl;
    file.close();

}