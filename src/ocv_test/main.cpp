//
// Created by Tom Quinders on 23/06/2017.
//


#include "main.h"

vector<float> currentPosition;

int main() {
    Testcam testcam;
    vector<int> testCamResolution;
    int innerLeftUpX;
    int innerLeftUpY;
    int innerLeftDownY;
    int innerRightUpX;
    int outerLeftUpX;
    int outerLeftUpY;
    int outerLeftDownY;
    int outerRightUpX;
    int currentDegreeX;
    int moveDegreeX;
    int currentDegreeY;
    int moveDegreeY;

    while (true) {
        //TODO: get position of camera or set it to auto 0/0

        //currentPosition = {0, 0};
        //Initialisation of servos to zero position
        if(initialise()){
            currentPosition = {0, 0};
            currentDegreeX=0;
            currentDegreeY=0;
        }

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

                //checks position of x.
                if(cPosX>innerLeftUpX){
                    if(cPosX<innerRightUpX){
                        //xOk
                        moveDegreeX=0;
                    }else{
                        if(cPosX<outerRightUpX){
                            //xSlowPositive
                            moveDegreeX=3;
                        }else{
                            //xFastPositive
                            moveDegreeX=6;
                        }
                    }
                }else{
                    if(cPosX>outerLeftUpX){
                        //xSlowNegative
                        moveDegreeX=-3;
                    }else{
                        //xFastNegative
                        moveDegreeX=-6;
                    }
                }

                //checks position of y.
                if(cPosY>innerLeftUpY){
                    if(cPosY<innerLeftDownY){
                        //YOK
                        moveDegreeY=0;
                    }else{
                        if(cPosY<outerLeftDownY){
                            //ySlowNegative
                            moveDegreeY=-3;
                        }else{
                            //yFastNegative
                            moveDegreeY=-6;
                        }
                    }
                }else{
                    if(cPosY>outerLeftUpY){
                        //ySlowPositive
                        moveDegreeY=3;
                    }else{
                        //yFastPositive
                        moveDegreeY=6;
                    }
                }

                //TODO: Gradzahlen übergeben
                degreeToPw(currentDegreeX+moveDegreeX,currentDegreeY+moveDegreeY);
                //}
            }
        }
    }
}