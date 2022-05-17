

// nema single step is 1.8° or 0.031 rad. 
void nemaStep(int dirPin,int stepPin, bool clockWise){
  //Activar una direccion y fijar la velocidad con stepDelay
  if(clockWise == true){
      digitalWrite(dirPin, HIGH); 
  }else{
    digitalWrite(dirPin, LOW);
  }
  const int stepDelay = 250;
  digitalWrite(stepPin, HIGH);
  delayMicroseconds(stepDelay);
  digitalWrite(stepPin, LOW);
  delayMicroseconds(stepDelay);
}

void testNema(int dirPin, int stepPin){
  for(int i = 0; i<100; i++){
    nemaStep(dirPin, stepPin, 1);
    delayMicroseconds(delayBetweenSteps);
  }
  delay(1000);
  for(int i = 0; i<100; i++){
    nemaStep(dirPin, stepPin, 0);
    delayMicroseconds(delayBetweenSteps);
  }
  delay(1000);
}
