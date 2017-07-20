//
// Created by Fabian on 02.07.17.
//

#include "main.h"

int main() {
    SearchCART search;
    Servo servo;

    int resolutionX = search.getSize()[0];
    int resolutionY = search.getSize()[1];
    int sectorX = resolutionX / 5;
    int sectorY = resolutionY / 5;
    int innerLeftUpX = sectorX * 2;
    int innerLeftUpY = sectorY * 2;
    int innerLeftDownY = sectorY * 3;
    int innerRightUpX = sectorX * 3;
    int outerLeftUpX = sectorX;
    int outerLeftUpY = sectorY;
    int outerLeftDownY = sectorY * 4;
    int outerRightUpX = sectorX * 4;
    int currentDegreeX;
    int moveDegreeX;
    int currentDegreeY;
    int moveDegreeY;

    // Ausgabe der Größe des Videos
    cout << "width:  "
         << resolutionX << endl
         << "height: "
         << resolutionY << endl
         << "fps: "
         << search.getFPS() << endl;

    //Initialisiert die Servos auf die Anfangsposition
    if (servo.initialiseServo()) {
        currentDegreeX = 0;
        currentDegreeY = 30;
    }

    // schrittweise das Video durchlaufen und die Servos korrigieren.
    int i = 0;
    while (i < 5) {
        if (search.isConnected()) {
            vector<int> position = search.loader(i);

//        cout << "X: "
//             << position[0]
//             << " Y: "
//             << position[1] << endl;

            double tPosX = position[0];
            double tPosY = position[1];

            cout << "target position is " << tPosX << " | " << tPosY << endl;

            //Überprüft die x-Position.
            if (tPosX > innerLeftUpX) {
                if (tPosX < innerRightUpX) {
                    //Servo muss nicht in x-Richtung bewegt werden.
                    moveDegreeX = 0;
                } else {
                    if (tPosX < outerRightUpX) {
                        //xSlowPositive
                        //Servo muss langsam in x-Richtung bewegt werden.
                        moveDegreeX = -3;
                    } else {
                        //xFastPositive
                        //Servo muss schnell in x-Richtung bewegt werden.
                        moveDegreeX = -6;
                    }
                }
            } else {
                if (tPosX > outerLeftUpX) {
                    //xSlowNegative
                    //Servo muss langsam in x-Richtung bewegt werden.
                    moveDegreeX = 3;
                } else {
                    //xFastNegative
                    //Servo muss schnell in x-Richtung bewegt werden.
                    moveDegreeX = 6;
                }
            }

            //checks position of y.
            if (tPosY > innerLeftUpY) {
                if (tPosY < innerLeftDownY) {
                    //YOK
                    moveDegreeY = 0;
                } else {
                    if (tPosY < outerLeftDownY) {
                        //ySlowNegative
                        //Servo muss langsam in y-Richtung bewegt werden.
                        moveDegreeY = 3;
                    } else {
                        //yFastNegative
                        //Servo muss schnell in y-Richtung bewegt werden.
                        moveDegreeY = 6;
                    }
                }
            } else {
                if (tPosY > outerLeftUpY) {
                    //ySlowPositive
                    //Servo muss langsam in y-Richtung bewegt werden.
                    moveDegreeY = -3;
                } else {
                    //yFastPositive
                    //Servo muss schnell in y-Richtung bewegt werden.
                    moveDegreeY = -6;
                }
            }
            //Wenn die Bewegung möglich ist, wird der aktuelle Winkel aktualisiert.
            if (servo.degreeToPw(currentDegreeX + moveDegreeX,
                                 currentDegreeY + moveDegreeY) != 0) {
                currentDegreeX = currentDegreeX + moveDegreeX;
                currentDegreeY = currentDegreeY + moveDegreeY;
            }

            cout << endl;
        }

        i++;
    }
}