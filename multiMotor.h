#ifndef multiMotor_h
#define multiMotor_h

#include "Arduino.h"

class multiMotor
{
    public:
        multiMotor(float voltage);
        int initSingle(int ctr1, int ctr2, int id, int pwm);
        int initDual(int ctr1, int ctr2, int ctr3, int ctr4, int pwmA, int pwmB, float ocMaxWattage);
        int driveSingle(int id, float power);
        int driveDual(float power, float ocWattage);  
    private:
        int in1;
        int in2;
        int in3;
        int in4;
        int id;
        int enA;
        int enB;

        float nom_voltage;
        float ocLimit;
};

#endif