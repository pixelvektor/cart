//
// Created by Fabian on 02.07.17.
//

#include "SearchCART.h"

SearchCART::SearchCART() {
    cout << "con" << endl;
    initVideo();
}

SearchCART::~SearchCART() {
    cout << "des" << endl;
    capture.release();
}

/**
 * Initialisiert den Stream.
 * @return 0 wenn ok, -1 wenn Stream nicht offen ist.
 */
int SearchCART::initVideo() {
    // Pfad zum Testvideo (build wird nicht im src-Verzeichnis abgelegt)
    string path = "../res/testvideo/";
    string filename = "test_v1.mov";
    string fullFilename = path + filename;

    cout << fullFilename << endl;

    // Öffnen des Streams
    capture.open(0);
    if ( !capture.isOpened())
        return -1;
    else
        cout << "STREAM IS OPEN" << endl;
    return 0;
}

/**
 * Getter für die Dimension des Streams in Pixeln.
 * @return double Array {Breite, Höhe}.
 */
vector<double> SearchCART::getSize() {
    double width = capture.get(CAP_PROP_FRAME_WIDTH);
    double height = capture.get(CAP_PROP_FRAME_HEIGHT);
    vector<double> rV = {width, height};
    return rV;
}

/**
 * Getter für die Bilder pro Sekunde.
 * @return double Bilder pro Sekunde.
 */
double SearchCART::getFPS() {
    return capture.get(CAP_PROP_FPS);
}

bool SearchCART::isConnected() {
    return true;
}

double SearchCART::getFC() {
    return capture.get(CAP_PROP_FRAME_COUNT);
}

/**
 * Lädt die Koordinaten des Punktes aus dem aktuellen Bild.
 * @param index Der Index der Schleife für die Speicherung der Sequenz.
 * @return x und y des Punktes.
 */
vector<int> SearchCART::loader(int index) {
    // Das aktuelle Frame laden
    Mat captureRGB;
    capture >> captureRGB;

    // In Graustufen konvertieren
    Mat captureGray;
    cvtColor(captureRGB, captureGray, CV_RGB2GRAY);

    // Schwellwert für Graustufen (alles unter dem Schwellwert soll schwarz werden)
    int threshold_value = 200;

    Mat captureThres;
    threshold(captureGray, captureThres, threshold_value, 255, 0);

    // Auslesen der weißen Pixel
    Mat whitePixelCoord;
    findNonZero(captureThres, whitePixelCoord);

    // Berechnen des Mittelpunktes der Ansammlung von weißen Pixeln
    int startX = whitePixelCoord.row(0).at<int>(0,0);
    int startY = whitePixelCoord.row(0).at<int>(0,1);

    int stopX = whitePixelCoord.row(whitePixelCoord.rows-1).at<int>(0,0);
    int stopY = whitePixelCoord.row(whitePixelCoord.rows-1).at<int>(0,1);

    int midX = startX + ((stopX - startX) / 2);
    int midY = startY + ((stopY - startY) / 2);

    vector<int> ballPosition = {midX, midY};

    vector<Vec3f> possibleLights;

    GaussianBlur(captureGray, captureGray, Size(9, 9), 2, 2);
    HoughCircles(captureGray, possibleLights, CV_HOUGH_GRADIENT, 1, captureThres.rows, 180, 20, 2, 50);

    for( size_t i = 0; i < possibleLights.size(); i++ )
    {
        Point center(cvRound(possibleLights[i][0]), cvRound(possibleLights[i][1]));
        int radius = cvRound(possibleLights[i][2]);
        // circle center
        circle( captureRGB, center, 3, Scalar(0,255,0), -1, 8, 0 );
        // circle outline
        circle( captureRGB, center, radius, Scalar(0,0,255), 3, 8, 0 );
    }

    if (true) {
        cout << "#############" << endl;
        cout << possibleLights.size() << endl;
        for (auto i = possibleLights.begin(); i != possibleLights.end(); ++i) {
            cout << *i << ' ';
        }
        cout << "#############" << endl;
    }

    // print white pixel positions
    if (index == 0) {
        //cout << "white pixels at = "<< endl << " "  << whitePixelCoord << endl << endl;
    }

    // schreibe die Einzelbilder auf die Platte
    ostringstream oss;
    oss << index;
    string savepath = "img/image.";
    savepath += oss.str();
    savepath += ".jpg";
    imwrite(savepath, captureRGB);

    return ballPosition;
}