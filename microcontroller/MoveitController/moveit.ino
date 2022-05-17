#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include <WProgram.h>
#endif

#include <Servo.h> 
#include <ros.h>
#include <std_msgs/UInt16.h>
#include <sensor_msgs/JointState.h>

#include "pines.h"
#include "nema.h"
#include "torso.h"
#include "elevador.h"
#include "munecaH.h"
#include "codo.h"

ros::NodeHandle  nh;

// ARM
double basePinzaJointV = 0; //S3

//GRIPPER

double pinzaGarraDV = 0; // S2
double pinzaGarraIV = 0; // S1

// NECK

double neckJointV = 0; // S7


void rosCallback(const sensor_msgs::JointState& cmd_msg){
  moveTorso(cmd_msg.position[4]);
  moveMunecaH(cmd_msg.position[7]);
  moveCodo(cmd_msg.position[6]);
}

ros::Subscriber<sensor_msgs::JointState> sub("joint_states", rosCallback);

void goToOrigin(){
  goToOriginTorso();
  goToOriginCodo();
  goToOriginMunecaH();
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  /*
  nh.getHardware()->setBaud(115200);
  nh.initNode();
  nh.subscribe(sub);
   */
  declaraPines();
  goToOrigin();
}

void loop() {
  //nh.spinOnce();
}
