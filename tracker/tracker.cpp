//
// Created by sjtu on 2020/10/17.
//
#include "tracker.h"
void tracker_KCF::reset(Mat& frame,Rect2d &rec,const string &windowname)
{

    rec = selectROI(windowname,frame,false);
    tck=TrackerKCF::create();//recreate
    tck->init(frame,rec);

}
bool tracker_KCF::update(Mat& frame,Rect2d &rec)
{
    return tck->update(frame,rec);
}
void tracker_MOSSE::reset(Mat& frame,Rect2d &rec,const string &windowname)
{

    rec = selectROI(windowname,frame,false);
    tck=TrackerMOSSE::create();//recreate
    tck->init(frame,rec);

}
bool tracker_MOSSE::update(Mat& frame,Rect2d &rec)
{
    return tck->update(frame,rec);
}
void tracker_CSRT::reset(Mat& frame,Rect2d &rec,const string &windowname)
{

    rec = selectROI(windowname,frame,false);
    tck=TrackerCSRT::create();//recreate
    tck->init(frame,rec);

}
bool tracker_CSRT::update(Mat& frame,Rect2d &rec)
{
    return tck->update(frame,rec);
}