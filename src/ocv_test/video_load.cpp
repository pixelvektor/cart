// Source: https://stackoverflow.com/questions/13709274/reading-video-from-file-opencv
// http://docs.opencv.org/3.1.0/d8/dfe/classcv_1_1VideoCapture.html
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/videoio/videoio.hpp>
#include <opencv2/opencv.hpp>
//#include <iostream>

using namespace cv;
//using namespace std;

int main(int, char**)
{
    String path = "../../res/testvideo/";
    String filename = "test_v0.mov";
    String fullFilename = path + filename;

    VideoCapture capture(fullFilename);
    Mat frame;

    if ( !capture.isOpened() )
        throw "Fehler beim Lesen der Datei" + fullFilename;

//    Mat edges;
//    namedWindow("edges",1);
//    for(;;)
//    {
//        Mat frame;
//        capture >> frame;
//        cvtColor(frame, edges, COLOR_BGR2GRAY);
//        GaussianBlur(edges, edges, Size(7,7),1.5,1.5);
//        Canny(edges, edges, 0, 30, 3);
//        imshow("edges", edges);
//        if(waitKey(30) >= 0) break;
//    }
//    return 0;


    namedWindow( "w", 1 );
    for ( ; ; )
    {
        capture >> frame;
        if (frame.empty())
            break;
        imshow("w", frame);
        waitKey(20);
    }
    waitKey(0);
}