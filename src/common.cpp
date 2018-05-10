#include<stdio.h>
#include <opencv2/opencv.hpp>

static const int INPUT_W = 500;
static const int INPUT_H = 375;

using namespace cv;

int preprocessFrame(Mat frame, Mat& frame_scaled){
    
    Size size(INPUT_W,INPUT_H);

    if(frame.empty()) return -1;

    if(frame.channels() == 4)
        cvtColor(frame, frame, COLOR_BGRA2BGR);
    resize(frame, frame_scaled, size);
    
    return 0;
}

int main(int argc, char **argv){
    if (argc!=2){
        printf("You need to provide an argument: video\n");
    }
    VideoCapture capture(argv[1]);
    if(!capture.isOpened()){
        printf("Video doesn't exists\n");
    }
    namedWindow("frame",CV_WINDOW_AUTOSIZE);
    Mat frame;
    Mat frame_scaled;
    for(;;){
        capture>>frame;
        if (preprocessFrame(frame, frame_scaled)!=0) break;
        imshow("frame",frame_scaled);
        if(waitKey(0) == 27) break;
    }
    capture.release();
    destroyAllWindows();
    return 0;
}
