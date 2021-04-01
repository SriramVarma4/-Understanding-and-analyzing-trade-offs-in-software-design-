#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>
#include <opencv2/opencv.hpp>
#include "pthread.h"
#include <bits/stdc++.h>
using namespace std;
using namespace cv;

//make all the required variables as global variables
Mat imgdiff;
Mat h;
Mat back_crop;
Mat frame;
Mat warp_frame;

Mat back_image;

int fm_count=1;

bool doing = true;
ofstream table("one.txt");

int max_offset;

bool tfree=true;

void* subtractor(void* dat);
int qd, dd;

int main(int argc,char* argv[]){

    VideoCapture cap("trafficvideo.mp4");
    if (!cap.isOpened()){
        cout<<"\nerror reading the video\n";
        return 0;
    }
    back_image = imread("empty.png");
    if ( back_image.empty() ) 
    { 
        cout << "Error loading the image" << endl;
        return -1; 
    }
    vector<Point2f> pts_src;
    pts_src.push_back(Point2f(925, 220));//left up
    pts_src.push_back(Point2f(225, 1004));//left bottom
    pts_src.push_back(Point2f(1552, 1004));//right bottom
    pts_src.push_back(Point2f(1295, 220));//right up

    vector<Point2f> pts_dst;
    pts_dst.push_back(Point2f(0, 0));//left up
    pts_dst.push_back(Point2f(0, 800));//left bottom
    pts_dst.push_back(Point2f(400, 800));//right bottom
    pts_dst.push_back(Point2f(400, 0));//right up

    h = findHomography(pts_src, pts_dst);
    //warped image
    Mat warp_back;

    warpPerspective(back_image, warp_back, h, back_image.size());
    
    back_crop = warp_back(Rect(0, 0, 400, 800));
    
    table<< "time , queue density , dynamic density\n";

    cout << "running\n";

    pthread_t th1;
    int args=1;
    if(0!=pthread_create(&th1, NULL, subtractor, &args))
        {cout<<"error creating thread"<<'\n';}

    while (true){
        if(fm_count%5!=0 || tfree) {
            bool next = cap.read(frame);
            if (next==false){
                cout<<"end of video\n";
                doing=false;
                break;
            }
            if(fm_count%5==1){
                warpPerspective(frame, warp_frame, h, back_image.size());
            }
            if(fm_count%5==0){
                table << fm_count-4<< ',' <<qd/320000.0<<','<<dd/320000.0<<'\n';
                qd=0;dd=0;
            }
            fm_count++;
        }
    }
    
    pthread_join(th1,NULL);
    table.close();
    cout<<"done\n";
    
}   

//common resources - fm_count, doing, warp_frame
void* subtractor(void* dat){
    Mat f_crop;
    Mat fgmask;
    //Mat warp_frame;
    Ptr<BackgroundSubtractor> pBackSub;
    pBackSub = createBackgroundSubtractorMOG2();
    //pthread_mutex_lock(mutex1);
    while(doing){
        if (fm_count%5==2){
            tfree = false;

            f_crop = warp_frame(Rect(0, 0, 400, 800));
            pBackSub->apply(f_crop, fgmask, .04);

            for(int y=0; y<800; y++){
            for(int x=0; x<400; x++){

                Vec3b & fc = f_crop.at<Vec3b>(Point(x,y));
                Vec3b & bc = back_crop.at<Vec3b>(Point(x,y));
                if( abs(fc[2]-bc[2])> 60 || abs(fc[1]-bc[1]) > 60 || abs(fc[0]-bc[0]) > 60)
                {
                    qd++;
                }
                Vec3b & dc = fgmask.at<Vec3b>(Point(x,y));
                if (dc[0] > 0){
                    dd++;
                }
            }
            }

            tfree=true;
        }
       //pthread_mutex_unlock(mutex1);
    }
   pthread_exit(NULL);
}
