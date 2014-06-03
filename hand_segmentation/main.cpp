//
//  main.cpp
//  hand_segmentation
//
//  Created by Uran Oh on 6/3/14.
//  Copyright (c) 2014 Uran Oh. All rights reserved.
//
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

using namespace cv;
using namespace std;

Mat imgOri,imgPaint;
cv::Rect rect;
cv::Point startP, endP;

bool isDrawing = false;

void mouseEvent(int evt, int x, int y, int flags, void* param){
    if(isDrawing){
        if(evt==CV_EVENT_LBUTTONUP){
            isDrawing = false;
            endP.x = x;
            endP.y = y;
            printf("up %d %d\n",x,y);
            //rect = Rect(startP, endP);
            return;
        }else if(evt==CV_EVENT_MOUSEMOVE){
            isDrawing = true;
            endP.x = x;
            endP.y = y;
            return;
        }
    }
    else{
        if(evt==CV_EVENT_LBUTTONDOWN){
           // imgPaint = imgOri.clone();
            isDrawing = true;
            endP.x = x;
            endP.y = y;
            startP.x = x;
            startP.y = y;
            printf("down %d %d\n",x,y);
            return;
        }
    }
}

int main(int argc, const char * argv[])
{

    namedWindow("Original Image");
    cvSetMouseCallback("Original Image", mouseEvent, &imgOri);
    VideoCapture cap;
    cap.open(0);
    if( !cap.isOpened() )
    {
        cout << "***Could not initialize capturing...***\n";
        return -1;
    }
    
    while(1)
    {
        cap >> imgOri;
        resize(imgOri, imgOri, Size(0, 0), 0.5, 0.5);
       
        /*if(startP.x != -1){
            rectangle(imgPaint, startP, endP, cvScalar(0,0,0), 1, 8, 0);
            imshow("Painted image",imgPaint);
        }*/
        rectangle(imgOri, startP, endP, cvScalar(0,0,0), 1, 8, 0);
        imshow("Original Image",imgOri);
        waitKey(30);
        /*char ch = waitKey(30);
        
        if(ch=='r'){
            imgPaint = imgOri.clone();
        }*/
    
    }

    return 0;
}

