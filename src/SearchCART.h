//
// Created by Fabian on 02.07.17.
//

#ifndef _CART_SEARCH_
#define _CART_SEARCH_

#include <iostream>
#include <opencv2/opencv.hpp>
#include <sstream>

using namespace cv;
using namespace std;

class SearchCART
{
private:
    bool connected = false;
    int initVideo();
    VideoCapture capture;
public:
    SearchCART();
    ~SearchCART();
    vector<int> loader(int i);
    vector<int> getSize();
    double getFPS();
    bool isConnected();
};

#endif  // _CART_SEARCH_