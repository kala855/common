#include<stdio.h>
#include <opencv2/opencv.hpp>
using namespace cv;


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
    for(;;){
	capture>>frame;
	if(frame.empty()) break;
	imshow("frame",frame);
	if(waitKey(0) == 27) break;
    }
    capture.release();
    destroyAllWindows();
    return 0;
}
