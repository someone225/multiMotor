#include "Arduino.h"
#include "multiMotor.h"


multiMotor::multiMotor()
{
    in1 = 0;
    in2 = 0;
    in3 = 0;
    in4 = 0;
    id = 0;
    enA = 0;
    enB = 0;

    ocLimit = 0
}


int multiMotor::initSingle(int ctr1, int ctr2, int id, int pwm)
/*
   initializes a single-channel motor
   args:
    - ctr1: digital pin ID of in1/in3
    - ctr2: digital pin ID of in2/in4
    - pwm: pwm pin ID of enA/enB
    - id: operating channel of the motor (channel 1 uses pins in1/in2/enA, channel 2 uses pins in3/in4/enB)
   returns:
    - 1, if initialization is successful unto channel 1
    - 2, if initialization is successful unto channel 2
    - 0, if initialization is unsuccessful
*/
{
    switch id
    {
        case 1:
        this->in1 = ctr1;
        this->in2 = ctr2;
        this->enA = pwm;

        pinMode(this->in1, OUTPUT);
        pinMode(this->in2, OUTPUT);
        pinMode(this->enA, OUTPUT);
        
        return 1;
        break;
        
        case 2:
        this->in3 = ctr1;
        this->in4 = ctr2;
        this->enB = pwm;

        pinMode(this->in3, OUTPUT);
        pinMode(this->in4, OUTPUT);
        pinMode(this->enB, OUTPUT);

        return 2;

        default:
        return 0;
}

int multiMotor::initDual(int ctr1, int ctr2, int ctr3, int ctr4, int pwmA, int pwmB, float ocMaxWattage)
/*
   initializes a dual-channel
   args:
    - ctr1: digital pin ID of in1
    - ctr2: digital pin ID of in2
    - ctr3: digital pin ID of in3
    - ctr4: digital pin ID of in4
    - pwmA: pwm pin ID of enA
    - pwmB: pwm pin ID of enB
   returns:
    - 1, if initialization is successful
*/
{

    this->in1 = ctr1;
    this->in2 = ctr2;
    this->in3 = ctr3;
    this->in4 = ctr4;
    this->enA = pwmA;
    this->enB = pwmB;

    this->ocLimit = ocMaxWattage;

    pinMode(this->in1, OUTPUT);
    pinMode(this->in2, OUTPUT);
    pinMode(this->in3, OUTPUT);
    pinMode(this->in4, OUTPUT);
    pinMode(this->enA, OUTPUT);
    pinMode(this->enB, OUTPUT);

    return 1;
}

int multiMotor::driveSingle(char dir, int id, float power)
/*
drives a single-channel motor
args:
- dir: direction of the motor (FORWARDS -> drives forwards | REVERSE -> drives backwards)
- id: channel id of the motor
- power: %power to run the motor at
returns:
- 1, if motor on channel 1 is found and successfully updated
- 2, if motor on channel 2 is found and successfully updated
- 0, if motor has not been found or successfully updated
*/
{
    switch id
    {
        case 1:
            if(dir == "FORWARDS")
            {
            digitalWrite(this->in1, HIGH);
            digitalWrite(this->in2, LOW);
            }
            else if(dir == "REVERSE")
            {
            digitalWrite(this->in1, LOW);
            digitalWrite(this->in2, HIGH);
            }

            analogWrite(this->enA, round(power * 2.55) )
            return 1;
            break;

        case 2:
            if(dir == "FORWARDS")
            {
            digitalWrite(this->in3, HIGH);
            digitalWrite(this->in4, LOW);
            }
            else if(dir == "REVERSE")
            {
            digitalWrite(this->in3, LOW);
            digitalWrite(this->in4, HIGH);
            }

            analogWrite(this->enB, round(power * 2.55) )
            return 2;
            break;

        default:
            return 0;
            break;

    }
}

int multiMotor::driveDual(char dir, float power)
/*
   drives a dual-channel motor
   args:
    - dir: direction of the motor (FORWARDS -> drives forwards | REVERSE -> drives backwards)
    - power: %power to run the motor at
   returns:
    - 1, if motor has been found and successfully updated
*/
{
    if(dir == "FORWARDS")
    {
    digitalWrite(this->in1, HIGH);
    digitalWrite(this->in2, LOW);
    digitalWrite(this->in3, HIGH);
    digitalWrite(this->in4, LOW);
    }
    else if(dir == "REVERSE")
    {
    digitalWrite(this->in1, LOW);
    digitalWrite(this->in2, HIGH);
    digitalWrite(this->in3, LOW);
    digitalWrite(this->in4, HIGH);
    }

    analogWrite(this->enA, round(power * 2.55) )
    return 1;
}

int multiMotor::overclock(float ocWattage)
/*
   overclocks a dual-channel motor
   args:
    - ocWattage: additional overclock wattage to apply to the motor
   returns:
    - 1, if motor has been successfully overclocked
    - 0, if overclock wattage has exceeded safe limits or failed
*/
{
    if(ocWattage <= this->ocLimit)
    {
    analogWrite(this->enB, round(ocWattage * (255/14.4) ) )
    return 1;
    }
    else
    {
    return 0;
    }
}