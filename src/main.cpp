//
// Created by Fabian on 02.07.17.
//

#include "main.h"

int main() {
    SearchCART search;
    Servo servo;

    vector<double> currentPosition;
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

    // schrittweise das Video durchlaufen und die Servos korrigieren
    int i = 0;
    while (i < 75) {
        vector<int> ballPos = search.loader(i);

        cout << "X: "
             << ballPos[0]
             << " Y: "
             << ballPos[1]
             << " FC: "
             << search.getFC() << endl;
        i++;


     // merging



        //TODO: get position of camera or set it to auto 0/0

        currentPosition = {0, 0};

        //Initialisation of servos to zero position
        if (servo.initialiseServo()) {
            currentDegreeX = 0;
            currentDegreeY = 0;
        }

        while (search.isConnected()) {
            if (true) { //old: testcam.targetfound
                vector<int> position = search.loader(i);
                double tPosX = position[0];
                double tPosY = position[1];

                cout << "target position is " << tPosX << "/" << tPosY << endl;

                //if(!currentPosition.empty())
                //{
                double cPosX = currentPosition[0];
                double cPosY = currentPosition[1];
                cout << "current position is " << cPosX << "/" << cPosY << endl;

                double deltaPosX = tPosX - cPosX;
                double deltaPosY = tPosY - cPosY;

                vector<double> deltaVector = {deltaPosX, deltaPosY};

                //checks position of x.
                if (cPosX > innerLeftUpX) {
                    if (cPosX < innerRightUpX) {
                        //xOk
                        moveDegreeX = 0;
                    } else {
                        if (cPosX < outerRightUpX) {
                            //xSlowPositive
                            moveDegreeX = 3;
                        } else {
                            //xFastPositive
                            moveDegreeX = 6;
                        }
                    }
                } else {
                    if (cPosX > outerLeftUpX) {
                        //xSlowNegative
                        moveDegreeX = -3;
                    } else {
                        //xFastNegative
                        moveDegreeX = -6;
                    }
                }

                //checks position of y.
                if (cPosY > innerLeftUpY) {
                    if (cPosY < innerLeftDownY) {
                        //YOK
                        moveDegreeY = 0;
                    } else {
                        if (cPosY < outerLeftDownY) {
                            //ySlowNegative
                            moveDegreeY = -3;
                        } else {
                            //yFastNegative
                            moveDegreeY = -6;
                        }
                    }
                } else {
                    if (cPosY > outerLeftUpY) {
                        //ySlowPositive
                        moveDegreeY = 3;
                    } else {
                        //yFastPositive
                        moveDegreeY = 6;
                    }
                }

                //TODO: Gradzahlen übergeben
                if (servo.degreeToPw(currentDegreeX + moveDegreeX,
                                     currentDegreeY + moveDegreeY) != 0) {
                    currentDegreeX = currentDegreeX + moveDegreeX;
                    currentDegreeY = currentDegreeY + moveDegreeY;
                }
                //}
            }
        }
    }
}