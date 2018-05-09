#include<stdio.h>
#include <opencv2/opencv.hpp>
using namespace cv;


int main(int argc, char **argv){
    if (argc!=2){
        printf("You need to provide an argument: video");
    }
    VideoCapture capture(argv[1]);
    if()
    capture.release();
}
