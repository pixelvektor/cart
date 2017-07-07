//
// Created by Fabian on 02.07.17.
//

#include "main.h"

int main() {
    SearchCART search;
    Servo servo;

    double resolutionX = search.getSize()[0];
    double resolutionY = search.getSize()[1];
    double sectorX = resolutionX / 5;
    double sectorY = resolutionY / 5;
    double innerLeftUpX = sectorX * 2;
    double innerLeftUpY = sectorY * 2;
    double innerLeftDownY = sectorY * 3;
    double innerRightUpX = sectorX * 3;
    double outerLeftUpX = sectorX;
    double outerLeftUpY = sectorY;
    double outerLeftDownY = sectorY * 4;
    double outerRightUpX = sectorX * 4;
    int currentDegreeX;
    int moveDegreeX;
    int currentDegreeY;
    int moveDegreeY;

    // Ausgabe der Größe des Videos
    cout << "width:  "
         << search.getSize()[0] << endl
         << "height: "
         << search.getSize()[1] << endl
         << "fps: "
         << search.getFPS() << endl;

    //Initialisation of servos to zero position
    if (servo.initialiseServo()) {
        currentDegreeX = 0;
        currentDegreeY = 30;
    }

    // schrittweise das Video durchlaufen und die Servos korrigieren
    int i = 0;
    while (i < 75) {
        vector<int> position = search.loader(i);

        cout << "X: "
             << position[0]
             << " Y: "
             << position[1]
             << " FC: "
             << search.getFC() << endl;
        i++;

        if (true) {
            double tPosX = position[0];
            double tPosY = position[1];

            cout << "target position is " << tPosX << "/" << tPosY << endl;

            //checks position of x.
            if (tPosX > innerLeftUpX) {
                if (tPosX < innerRightUpX) {
                    //xOk
                    moveDegreeX = 0;
                } else {
                    if (tPosX < outerRightUpX) {
                        //xSlowPositive
                        moveDegreeX = 3;
                    } else {
                        //xFastPositive
                        moveDegreeX = 6;
                    }
                }
            } else {
                if (tPosX > outerLeftUpX) {
                    //xSlowNegative
                    moveDegreeX = -3;
                } else {
                    //xFastNegative
                    moveDegreeX = -6;
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
                        moveDegreeY = -3;
                    } else {
                        //yFastNegative
                        moveDegreeY = -6;
                    }
                }
            } else {
                if (tPosY > outerLeftUpY) {
                    //ySlowPositive
                    moveDegreeY = 3;
                } else {
                    //yFastPositive
                    moveDegreeY = 6;
                }
            }

            if (servo.degreeToPw(currentDegreeX + moveDegreeX,
                                 currentDegreeY + moveDegreeY) != 0) {
                currentDegreeX = currentDegreeX + moveDegreeX;
                currentDegreeY = currentDegreeY + moveDegreeY;
            }

            cout << endl;
        }
    }
}