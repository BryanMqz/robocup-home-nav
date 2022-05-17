
double torsoR = 0;
int stepsInitT = 3200;
double stepPerRadT = stepsInitT / (pi/8.0);

// dir = 0 is anti clockwise
void goToOriginTorso(){
  bool dir = 0;
  while(digitalRead(limitSwitch3) == HIGH){
      nemaStep(dirPinM4, stepPinM4, dir);
      delayMicroseconds(delayBetweenSteps);
  }
  delay(500);
  for(int i=0; i< stepsInitT; i++){
    nemaStep(dirPinM4, stepPinM4, !dir);
    delayMicroseconds(delayBetweenSteps);
  }
}


void moveTorso(double rad){
  double torsoAcR = torsoR;
  torsoR = rad; // set current pos to new

  bool dir = torsoR < torsoAcR ? 1 : 0; // menor -> clockwise
  int stepsToGoal = stepPerRadT * abs(torsoR-torsoAcR);
  
  for(int i=0; i<stepsToGoal; i++){
    nemaStep(dirPinM4, stepPinM4, dir);
    delayMicroseconds(delayBetweenSteps);
  }
  delay(100);
}
  
