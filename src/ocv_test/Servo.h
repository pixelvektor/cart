//
// Created by Tom Quinders on 30/06/2017.
//

#ifndef CART_MOVE_TEST_H
#define CART_MOVE_TEST_H


#include <iostream>
#include <pigpio.h>

using namespace std;

int main();

class Servo
{
private:
    void moveServo(int servo, int pw);
public:
    int initialiseServo();
    int degreeToPw(int degreeX, int degreeY);
};

#endif //CART_MOVE_TEST_H