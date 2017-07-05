//
// Created by Fabian on 02.07.17.
//

#include "SearchCART.h"

SearchCART::SearchCART() {
    initVideo();
}

SearchCART::~SearchCART() {
    capture.release();
}

int SearchCART::initVideo() {
    // Pfad zum Testvideo (build wird nicht im src-Verzeichnis abgelegt)
    string path = "../res/testvideo/";
    string filename = "test_v0.mov";
    string fullFilename = path + filename;

    cout << fullFilename << endl;

    // Öffnen des Streams
    capture.open(fullFilename);
    if ( !capture.isOpened())
        return -1;
    else
        cout << "STREAM IS OPEN" << endl;
    return 0;
}

int* SearchCART::getSize() {
    int captureSize[2] = {300, 200};
    return captureSize;
}

int SearchCART::loader() {


    return 0;
}