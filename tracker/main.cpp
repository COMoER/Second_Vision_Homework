#include <iostream>
#include <opencv2/core/ocl.hpp>
#include <opencv2/tracking.hpp>
#include <opencv2/opencv.hpp>
#include <string>
#include "tracker.h"
using namespace std;
using namespace cv;
enum{
    TRACKER_KCF=1,
    TRACKER_MOSSE=2,
    TRACKER_CSRT=3
};
int main() {
    Mat frame;
    VideoCapture cap;
    cap.open("../1.mp4");
    if(!cap.isOpened())
    {
        cerr<<"Video is not opened!";
        return -1;
    }
    cap.read(frame);
    Ptr<VideoWriter> writer;
    int type;
    cout<<"which tracker to select?(1:KCF,2:MOSSE,3:CSRT)";
    cin>>type;

    Ptr<tracker> tck;

    Rect2d rec;
    switch(type){
        case TRACKER_KCF:{tck=new tracker_KCF(frame,rec,"tracker");
        writer=new VideoWriter("../KCF.mp4",VideoWriter::fourcc('m', 'p', '4', 'v'),30.0,Size(frame.cols,frame.rows));
        break;}
        case TRACKER_MOSSE:{tck=new tracker_MOSSE(frame,rec,"tracker");
            writer=new VideoWriter("../MOSSE.mp4",VideoWriter::fourcc('m', 'p', '4', 'v'),30.0,Size(frame.cols,frame.rows));
            break;}
        case TRACKER_CSRT:{tck=new tracker_CSRT(frame,rec,"tracker");
            writer=new VideoWriter("../CSRT.mp4",VideoWriter::fourcc('m', 'p', '4', 'v'),30.0,Size(frame.cols,frame.rows));
            break;}

    };
    rectangle(frame,rec,Scalar(0,255,0));
    imshow("tracker",frame);
    int counter=1;
    while(cap.read(frame))
    {
        if(tck->update(frame,rec))
        {
            //re_select
            if(counter%700==0)
            {
                cout<<"It's time to re_select!"<<endl;
                tck->reset(frame,rec,"tracker");
            }
            rectangle(frame,rec,Scalar(0,255,0));
        }
        else//avoid invalid
        {
            cout<<"Oh no!It's invalid! Please reset."<<endl;
            tck->reset(frame,rec,"tracker");
        }
        imshow("tracker",frame);
        *writer<<frame;
        waitKey(20);
        ++counter;
    }
    cap.release();
    destroyAllWindows();
    return 0;
}
