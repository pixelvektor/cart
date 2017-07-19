//
// Created by Adrian on 24.06.2017.
//

#include "Servo.h"

// Maximale Frequenzen für den Arbeitsbereich der Servos
int maxPwX = 1900;
int minPwX = 1100;
int maxPwY = 1900;
int minPwY = 1100;

// GPIO Adressen der Servos
int SERVO_X = 20;
int SERVO_Y = 26;

/* Initialising pigpio and sets servos zo zero position. */
int Servo::initialiseServo() {
    if (gpioInitialise() < 0) {
        cout << "ERROR initializing!" << endl;
        return 0;
    } else {
        gpioServo(SERVO_X, minPwX);
        gpioServo(SERVO_Y, minPwY + (maxPwY - minPwY) / 2);
        time_sleep(10);
        return 1;
    }
}

/* Converts degree to pulsewidth. */
int Servo::degreeToPw(int degreeX, int degreeY) {
    cout << "degreeX: "
         << degreeX
         << " degreeY: "
         << degreeY << endl;
    int rangeX = maxPwX - minPwX;
    int oneDegX = rangeX / 144;
    int rangeY = maxPwY - minPwY;
    int oneDegY = rangeY / 48;
    int resultX = minPwX + (oneDegX * degreeX);
    int resultY = minPwY + (oneDegY * degreeY);
    //Stops the servo from going too far.
    if (resultX >= minPwX && resultX <= maxPwX)
        moveServo(SERVO_X, resultX);

    if (resultY >= minPwY && resultY <= maxPwY)
        moveServo(SERVO_Y, resultY);
//        return 1;
//    } else {
        return 0;
//    }
}

/* Moves the servo to given pulsewidth. */
void Servo::moveServo(int servo, int pw) {
    /* position servo */
    gpioServo(servo, pw);
    cout << "Servo: "
         << servo
         << " at PW: "
         << pw << endl;
}
