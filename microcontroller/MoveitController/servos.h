// ARM [-1,0.5] (up, down)
double munecaVR = 0; //S3
int munecaVG = 90; // to test

//GRIPPER

double garraDR = 0; // S2
int garraDG = 90;
double garraIR = 0; // S1
int garraIG = 90;

// NECK

double neckJointV = 0; // S7

void constraint(double &g){
  if(g<0){
    g = 0;
  }else if(g>180){
    g=180;
  }
}

void moveMunecaV(double rad){
  double actual = munecaVR;
  munecaVR = rad;
  double deltaRad = abs(rad - actual);
  double deltaGrad = to_grad(deltaRad);
  bool dir = 1;
  if(dir == 1){
    munecaVG+=deltaGrad;
  }else{
    munecaVG-=deltaGrad;
  }
  constraint(munecaVG);
  munecaV.write(munecaVG);
}

void moveGarraI(double rad){
  double actual = garraIR;
  garraIR = rad;
  double deltaRad = abs(rad - actual);
  double deltaGrad = to_grad(deltaRad);
  bool dir = 1;
  if(dir == 1){
    garraIG+=deltaGrad;
  }else{
    garraIG-=deltaGrad;
  }
  constraint(garraIG);
  garraI.write(garraIG);
}

void moveGarraD(double rad){
  double actual = garraDR;
  garraDR = rad;
  double deltaRad = abs(rad - actual);
  double deltaGrad = to_grad(deltaRad);
  bool dir = 1;
  if(dir == 1){
    garraDG+=deltaGrad;
  }else{
    garraDG-=deltaGrad;
  }
  constraint(garraDG);
  garraD.write(garraDG);
}
