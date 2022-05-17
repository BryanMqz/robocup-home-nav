
double munecaHR = 0; // M1

int stepsInitMH = 2700;
double stepPerRadMH = stepsInitMH / pi;

// dir = 0 is clockwise
void goToOriginMunecaH(){
  bool dir = 0;
  while(digitalRead(limitSwitch1) == HIGH){
      nemaStep(dirPinM1, stepPinM1, dir);
      delayMicroseconds(delayBetweenSteps);
  }
  delay(500);
  for(int i=0; i<stepsInitMH; i++){
    nemaStep(dirPinM1, stepPinM1, !dir);
    delayMicroseconds(delayBetweenSteps);
  } 
}

void moveMunecaH(double rad){
  double munecaHAcR = munecaHR;
  munecaHR = rad; // set current pos tu new

  bool dir = munecaHR < munecaHAcR ? 0 : 1; // menor -> clockwise
  int stepsToGoal = stepPerRadMH * abs(munecaHR-munecaHAcR);
  
  for(int i=0; i<stepsToGoal; i++){
    nemaStep(dirPinM1, stepPinM1, dir);
    delayMicroseconds(delayBetweenSteps);
  }
  delay(100);
}
  
