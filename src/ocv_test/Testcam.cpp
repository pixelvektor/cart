//
// Created by Tom Quinders on 23/06/2017.
//

#include "Testcam.h"

bool Testcam::isConnected() {
    return true;
}

bool Testcam::targetFound() {
    return true;
}

std::vector<float> Testcam::getTargetPosition() {

    float x = 1.0f;
    float y = 2.0f;

    std::vector<float> v = {x,y};

    return v;
}