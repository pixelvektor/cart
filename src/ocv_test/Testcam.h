//
// Created by Tom Quinders on 23/06/2017.
//

#ifndef CART_TESTCAM_H
#define CART_TESTCAM_H


//#include <rpcndr.h>
#include <vector>

class Testcam {
public:
    bool isConnected();
    bool targetFound();
    std::vector<float> getTargetPosition();
};

#endif //CART_TESTCAM_H
