/* multiMotor
 by Mark Sheng

 modified 11 Nov 2025
 by Mark Sheng
 https://github.com/someone225/multiMotor
*/
#include <multiMotor.h>


multiMotor testMotor(12); //initializes a multiMotor class named testMotor with a nominal voltage of 12V
//you can think of a multiMotor class as representing an L293n motor driver
void setup() {
  // put your setup code here, to run once:
}

void loop() {

  //running a single-channel motor
  testMotor.initSingle(1, 2, 9, 1); //declares a single-channel motor onto channel id 1, with pins in1 = d1, in2 = d2, enA = d9 

  testMotor.driveSingle(1, 100) //runs the motor on channel id 1 forwards at 100% power

  testMotor.driveSingle(1, -100) //runs the motor on channel id 1 backwards at 100% power
  //you can declare two single-channel motors as the L293n has two channels
  

  //running a dual-channel motor
  //if the circuit is set up correctly, dual-channel motors are overclockeable 
  testMotor.initDual(1, 2, 3, 4, 9, 10, 12) //declares a dual-channel motor with pins in1 = d1, in2 = d2, in3 = d3, in4 = d4, enA = d9, enB = d10, and a max overclock TGP of +12W
  
  testMotor.driveDual(100, 12) //drives the declared dual-channel motor forwards at 100% power with an overclock of +12W

  testMotor.driveDual(-100, 12) //drives the declared dual-channel motor backwards at 100% power with an overclock of +12W



}