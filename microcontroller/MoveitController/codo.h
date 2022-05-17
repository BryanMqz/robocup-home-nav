
double codoR = 0; // M1

int stepsInitC = 2700; // NEEDS TEST
double stepPerRadC = stepsInitC / pi;

// dir = 0 is NEEDS TEST
void goToOriginCodo(){
  bool dir = 0;
  while(digitalRead(limitSwitch2) == HIGH){
      nemaStep(dirPinM8, stepPinM8, dir);
      delayMicroseconds(delayBetweenSteps);
  }
  delay(500);
  for(int i=0; i<stepsInitC; i++){
    nemaStep(dirPinM8, stepPinM8, !dir);
    delayMicroseconds(delayBetweenSteps);
  } 
}

void moveCodo(double rad){
  double codoAcR = codoR;
  codoR = rad; // set current pos tu new

  bool dir = codoR < codoAcR ? 0 : 1; // menor -> clockwise
  int stepsToGoal = stepPerRadC * abs(codoR-codoAcR);
  
  for(int i=0; i<stepsToGoal; i++){
    nemaStep(dirPinM8, stepPinM8, dir);
    delayMicroseconds(delayBetweenSteps);
  }
  delay(100);
}
  
