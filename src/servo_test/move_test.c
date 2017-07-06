//
// Created by Adrian on 24.06.2017.
//

#include "move_test.h"

int maxPwX=1000;
int minPwX=2500;
int maxPwY=1000;
int minPwY=2500;

int main(int argc, char *argv[])
{
   if(initialise()){
       degreeToPw(90,60);
   }else{
       printf("ERROR test!");
   }
}

/* Initialising pigpio and sets servos zo zero position. */
int initialise(){
    if (gpioInitialise()<0){
        gpioServo(0, minPwX);
        gpioServo(1, (maxPwY-minPwY)/2);
        time_sleep(10);
        return 1;
    } else{
        printf("ERROR initializing!");
        return 0;
    }
}

/* Converts degree to pulsewidth. */
int degreeToPw(int degreeX, int degreeY){
    int rangeX=maxPwX-minPwX;
    int oneDegX=rangeX/180;
    int rangeY=maxPwY-minPwY;
    int oneDegY=rangeY/60;
    int resultX=minPwX+(oneDegX*degreeX);
    int resultY=minPwY+(oneDegY*degreeY);
    //Stops the servo from going too far.
    if(resultX>=minPwX&&resultX<=maxPwX&&resultY>=minPwY&&resultY<=maxPwY){
        moveServo(0, resultX);
        moveServo(1, resultY);
        return 1;
    }else{
        return 0;
    }
}

/* Moves the servo to given pulsewidth. */
void moveServo(int servo, int pw){
    /* position servo */
    gpioServo(servo, pw);
}
