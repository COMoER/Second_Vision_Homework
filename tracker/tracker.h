//
// Created by sjtu on 2020/10/17.
//

#ifndef TRACKER_TRACKER_H
#define TRACKER_TRACKER_H
#include <iostream>
#include <opencv2/core/ocl.hpp>
#include <opencv2/tracking.hpp>
#include <opencv2/opencv.hpp>
#include <string>
using namespace std;
using namespace cv;

class tracker{
public:
    tracker()=default;
    virtual void reset(Mat& frame,Rect2d &rec,const string &windowname)=0;
    virtual bool update(Mat& frame,Rect2d &rec)=0;
    ~tracker(){}
};

class tracker_KCF:public tracker
{
private:
    Ptr<TrackerKCF> tck;
public:
    tracker_KCF(Mat& frame,Rect2d &rec,const string &windowname){reset(frame,rec,windowname);}
    void reset(Mat& frame,Rect2d &rec,const string &windowname)override;
    bool update(Mat& frame,Rect2d &rec)override;
    ~tracker_KCF()=default;
};
class tracker_MOSSE:public tracker
{
private:
    Ptr<TrackerMOSSE> tck;
public:
    tracker_MOSSE(Mat& frame,Rect2d &rec,const string &windowname){reset(frame,rec,windowname);}
    void reset(Mat& frame,Rect2d &rec,const string &windowname)override;
    bool update(Mat& frame,Rect2d &rec)override;
    ~tracker_MOSSE()=default;
};
class tracker_CSRT:public tracker
{
private:
    Ptr<TrackerCSRT> tck;
public:
    tracker_CSRT(Mat& frame,Rect2d &rec,const string &windowname){reset(frame,rec,windowname);}
    void reset(Mat& frame,Rect2d &rec,const string &windowname)override;
    bool update(Mat& frame,Rect2d &rec)override;
    ~tracker_CSRT()=default;
};
#endif //TRACKER_TRACKER_H
