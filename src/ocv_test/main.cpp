//
// Created by Tom Quinders on 23/06/2017.
//


#include "main.h"

vector<float> currentPosition;

int main() {
    Testcam testcam;
    while (true) {
        //TODO: get position of camera or set it to auto 0/0
        currentPosition = {0, 0};

        while (testcam.isConnected()) {
            if (testcam.targetFound()) {
                vector<float> v = testcam.getTargetPosition();
                float tPosX = v[0];
                float tPosY = v[1];

                cout << "target position is " << tPosX << "/" << tPosY << endl;

                //if(!currentPosition.empty())
                //{
                float cPosX = currentPosition[0];
                float cPosY = currentPosition[1];
                cout << "current position is " << cPosX << "/" << cPosY << endl;

                float deltaPosX = tPosX - cPosX;
                float deltaPosY = tPosY - cPosY;

                vector<float> deltaVector = {deltaPosX, deltaPosY};
                //}
            }
        }
    }
}