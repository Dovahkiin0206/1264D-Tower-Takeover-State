/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       jennifer chen                                             */
/*    Created:      Fri Nov 08 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// L1                   motor         1               
// L2                   motor         11              
// R1                   motor         10              
// R2                   motor         19              
// Lift1                motor         3               
// Lift2                motor         12              
// Intake1              motor         4               
// Intake2              motor         7               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

competition Competition;

bool liftHolding;

void liftHold(){
  Lift1.stop(brakeType::hold);
  Lift2.stop(brakeType::hold);
  Controller1.Screen.print("       Holding  ");
}

void liftRelease(){
  Lift1.stop(brakeType::coast);
  Lift2.stop(brakeType::coast);
  Controller1.Screen.print("     Not Holding");
}

void liftControl(){
  if(Controller1.Axis2.value() == 0){
    liftHold();
    liftHolding = true;
  }
  else if(Controller1.Axis2.value() > 0){
    if(liftHolding){
      liftRelease();
      liftHolding = false;
    }

    if(Controller1.ButtonR2.pressing()){
      Lift1.spin(directionType::fwd,Controller1.Axis2.value()/4,percentUnits::pct);
      Lift2.spin(directionType::fwd,Controller1.Axis2.value()/4,percentUnits::pct);
    }
    else{
      Lift1.spin(directionType::fwd,Controller1.Axis2.value()/1.5,percentUnits::pct);
      Lift2.spin(directionType::fwd,Controller1.Axis2.value()/1.5,percentUnits::pct);
    }
  }
  else if(Controller1.Axis2.value() < 0){

    if(liftHolding){
      liftRelease();
      liftHolding = false;
    }

    Lift1.spin(directionType::fwd,Controller1.Axis2.value()/2,percentUnits::pct);
    Lift2.spin(directionType::fwd,Controller1.Axis2.value()/2,percentUnits::pct);

  }
  else{
    Brain.Screen.print("ERROR");
  } 
}

void DT(){
  R1.spin(directionType::fwd,Controller1.Axis3.value()-Controller1.Axis4.value(),percentUnits::pct);
  R2.spin(directionType::fwd,Controller1.Axis3.value()-Controller1.Axis4.value(),percentUnits::pct);
  L1.spin(directionType::fwd,Controller1.Axis3.value()+Controller1.Axis4.value(),percentUnits::pct);
  L2.spin(directionType::fwd,Controller1.Axis3.value()+Controller1.Axis4.value(),percentUnits::pct);
}

void intake(){
  if(Controller1.ButtonR1.pressing()){
    Intake1.spin(directionType::rev,100,percentUnits::pct);
    Intake2.spin(directionType::rev,100,percentUnits::pct);
  }
  else if(Controller1.ButtonR2.pressing()){
    Intake1.spin(directionType::fwd,100,percentUnits::pct);
    Intake2.spin(directionType::fwd,100,percentUnits::pct);
  }
  else{
    Intake1.stop(brakeType::brake);
    Intake2.stop(brakeType::brake);
  }
}

/*

        AUTON FUNCTIONS

*/

void driveStraight(double spin, int speed){
  R1.rotateFor(spin, rotationUnits::rev, speed, velocityUnits::pct, false);
  R2.rotateFor(spin, rotationUnits::rev, speed, velocityUnits::pct, false);
  L1.rotateFor(spin, rotationUnits::rev, speed, velocityUnits::pct, false);
  L2.rotateFor(spin, rotationUnits::rev, speed, velocityUnits::pct, true);
}

void turn(double left, double right, int speed){
  R1.rotateFor(right, rotationUnits::rev, speed, velocityUnits::pct, false);
  R2.rotateFor(right, rotationUnits::rev, speed, velocityUnits::pct, false);
  L1.rotateFor(left, rotationUnits::rev, speed, velocityUnits::pct, false);
  L2.rotateFor(left, rotationUnits::rev, speed, velocityUnits::pct, true);
}

void lift(double spin, int speed){
  Lift1.rotateFor(spin, rotationUnits::rev, speed, velocityUnits::pct, false);
  Lift2.rotateFor(spin, rotationUnits::rev, speed, velocityUnits::pct, true);     
}       


void auton(){
  lift(1.5, 70);
  driveStraight(1, 50);    //deploy
  task::sleep(200);
  driveStraight(-.6, 50);
  lift(-1.5, 100);
  lift(1, 60);
  
  
  Intake1.spin(directionType::rev, 100, velocityUnits::pct);   //run intake motors
  Intake2.spin(directionType::rev, 100, velocityUnits::pct);
  task::sleep(300);                  
  driveStraight(1, 60);
  lift(-.7, 50);                       //lower lift to grab 1st cube
  lift(2, 50);
  task::sleep(200);
  Intake1.stop(brakeType::hold);      //stop intake motors
  Intake2.stop(brakeType::hold);

  driveStraight(1.2, 40);           //up to cube tower
  task::sleep(900);
  Intake1.spin(directionType::rev, 100, velocityUnits::pct);    //run intake
  Intake2.spin(directionType::rev, 100, velocityUnits::pct);
  lift(-1.8, 15);               //grab tower and lift
  lift(1, 40);
  task::sleep(200);
  
  driveStraight(-1.8, 50);  //backwards and turn
  turn(.9, -.8, 50);

  driveStraight(1.2, 40);   
  turn(.2, 0, 50);          //slightly angle
  driveStraight(1.5, 30);    //forward into zone

  lift(-1.6, 30);    //lower lift
  task::sleep(400);
  Intake1.spin(directionType::fwd, 40, velocityUnits::pct);
  Intake2.spin(directionType::fwd, 40, velocityUnits::pct);  
  lift(2, 35);      //raise lift   
  Intake1.stop(brakeType::coast);
  Intake2.stop(brakeType::coast);

  driveStraight(-3, 60);
 
}

void driverControl(){
  while(1){
    liftControl();
    DT();
    intake();
    task::sleep(20);
  }
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  Brain.Screen.clearScreen("#525252");
  Brain.Screen.drawImageFromFile("/dlogo.png",120,0);

  Competition.autonomous( auton );
  Competition.drivercontrol( driverControl );
  
}








