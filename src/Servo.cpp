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

/** Initialisiert pigpio und setzt die Servos auf die Ausgangsposition.
 * @return int mit dem Erfolg.
 */
int Servo::initialiseServo() {
    if (gpioInitialise() < 0) {
        cout << "ERROR initializing!" << endl;
        return 0;
    } else {
        this->reset();
        return 1;
    }
}

void Servo::reset() {
    gpioServo(SERVO_X, minPwX);
    gpioServo(SERVO_Y, minPwY + (maxPwY - minPwY) / 2);
    time_sleep(3);
}

/** Wandelt die Gradzahlen in Pulsweite um.
 * @param degreeX Grad der Veränderung in x-Richtung.
 * @param degreeY Grad der Veränderung in y-Richtung.
 * @return ob die Bewegung möglich ist.
 */
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
    //Verhindert dass der Servo außerhalb seiner Grenzen fährt.
    if (resultX >= minPwX && resultX <= maxPwX && resultY >= minPwY && resultY <= maxPwY){
        moveServo(SERVO_X, resultX);

    //if (resultY >= minPwY && resultY <= maxPwY)
        moveServo(SERVO_Y, resultY);
        return 1;
    } else {
        return 0;
    }
}

/** Bewegt den Servo auf die gegebene Pulsweite.
 * @param servo Der Servo der angesteuert wird.
 * @param pw Die Pulsweite die angelegt wird.
 */
void Servo::moveServo(int servo, int pw) {
    gpioServo(servo, pw);
    cout << "Servo: "
         << servo
         << " at PW: "
         << pw << endl;
}
