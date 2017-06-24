//
// Created by Adrian on 24.06.2017.
//

#include <stdio.h>
#include <pigpio.h>

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

void degreeToPw(int degreeX, int degreeY){
    int rangeX=maxPwX-minPwX;
    int oneDegX=rangeX/180;
    int rangeY=maxPwY-minPwY;
    int oneDegY=rangeY/60;
    moveServo(0, oneDegX*degreeX);
    moveServo(1, oneDegY*degreeY);
}

void moveServo(int servo, int pw){
    /* position servo */
    gpioServo(servo, pw);
}