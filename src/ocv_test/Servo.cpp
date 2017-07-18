//
// Created by Adrian on 24.06.2017.
//

#include "Servo.h"

int maxPwX = 1900;
int minPwX = 1100;
int maxPwY = 1900;
int minPwY = 1100;

int servoX = 20;
int servoY = 26;

int main() {
    Servo s;
    s.initialiseServo();

    bool run = true;
    int angle;

    while (run) {
        cout << "type angle: ";
        cin >> angle;

        if (angle == 666)
            run = false;

        s.degreeToPw(angle, 30);
    }
}

/* Initialising pigpio and sets servos zo zero position. */
int Servo::initialiseServo() {
    if (gpioInitialise() < 0) {
        cout << "ERROR initializing!" << endl;
        return 0;
    } else {
        cout << "init" << endl;
        gpioServo(servoX, minPwX);
        gpioServo(servoY, minPwY + (maxPwY - minPwY) / 2);
        time_sleep(2);
        cout << "final and EXIT" << endl;
        return 1;
    }
}

/* Converts degree to pulsewidth. */
int Servo::degreeToPw(int degreeX, int degreeY) {
    int rangeX = maxPwX - minPwX;
    int oneDegX = rangeX / 180;
    int rangeY = maxPwY - minPwY;
    int oneDegY = rangeY / 60;
    int resultX = minPwX + (oneDegX * degreeX);
    int resultY = minPwY + (oneDegY * degreeY);
    //Stops the servo from going too far.
    if (resultX >= minPwX
        && resultX <= maxPwX
        && resultY >= minPwY
        && resultY <= maxPwY) {
        moveServo(servoX, resultX);
        moveServo(servoY, resultY);
        return 1;
    } else {
        return 0;
    }
}

/* Moves the servo to given pulsewidth. */
void Servo::moveServo(int servo, int pw) {
    /* position servo */
    cout << "moveServo got servo: "
         << servo
         << " and pw: "
         << pw << endl;
    gpioServo(servo, pw);
}