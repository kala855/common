#include<stdio.h>
#include <opencv2/opencv.hpp>

static const int INPUT_W = 500;
static const int INPUT_H = 375;
static const int INPUT_C = 3;
static const int N = 1;

using namespace cv;

int preprocessFrame(Mat frame, Mat& frame_scaled, float* data){

    Size size(INPUT_W,INPUT_H);

   //Pixel mean used by FasterRCNN authors. Also in BGR order
    float pixelMean[3] = { 102.9801f, 115.9465f, 122.7717f };

    if(frame.empty()) return -1;

    if(frame.channels() == 4)
        cvtColor(frame, frame, COLOR_BGRA2BGR);
    resize(frame, frame_scaled, size);
    Mat_<Vec3f>::iterator it;
    unsigned int volChl = INPUT_H*INPUT_W;
    for (int c = 0; c < INPUT_C; ++c)
    {
        //Vec3f not working - reason still unknown...
        Mat_<Vec3b>::iterator it = frame_scaled.begin<Vec3b>();
        // the color image to input should be in BGR order
        for (unsigned j = 0; j < volChl; ++j)
        {
            //OpenCV read in frame as BGR format, by default,
            //thus need only deduct the mean value
            data[c*volChl + j] = float((*it)[c]) - pixelMean[c];
            it++;
        }
    }
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

    //In this pointer we are going to put the info of each frame
    //in order to process it and feed the FasterRCNN example
    float* data = new float[N*INPUT_C*INPUT_H*INPUT_W];

    for(;;){
        capture>>frame;
        if (preprocessFrame(frame, frame_scaled, data)!=0) break;
        imshow("frame",frame_scaled);
        if(waitKey(0) == 27) break;
    }
    delete [] data;
    capture.release();
    destroyAllWindows();
    return 0;
}
