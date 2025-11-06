#ifndef multiMotor_h
#define multiMotor_h

#include "Arduino.h"

class multiMotor
{
    public:
        multiMotor();
        int initSingle(int ctr1, int ctr2, int id, int pwm);
        int initDual(int ctr1, int ctr2, int ctr3, int ctr4, int pwmA, int pwmB, float ocMaxWattage);
        int driveSingle(String dir, int id, float power);
        int driveDual(String dir, float power);
        int overclock(float ocWattage);    
    private:
        int in1;
        int in2;
        int in3;
        int in4;
        int id;
        int enA;
        int enB;

        float ocLimit;
};

#endif