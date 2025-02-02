#include <math.h>
#include "Encoder.h"
#include "Motor.h"

//////////////////////////////////Constructor//////////////////////////////////////
Motor::Motor() {}
Motor::Motor(const MotorId id, const uint8_t digital_one, const uint8_t digital_two, 
const uint8_t analog_one, const uint8_t encoder_one, const uint8_t encoder_two) : 
pid_(kP, kI, kD, kPidMinOutputLimit, kPidMaxOutputLimit, kPidMaxErrorSum, kPidMotorTimeSample) {

  id_ = id;
  digital_one_ = digital_one;
  digital_two_ = digital_two;
  analog_one_ = analog_one;
  encoder_one_ = encoder_one;
  encoder_two_ = encoder_two;

  stop();
  defineOutput();

}


//////////////////////////////////Initialization//////////////////////////////////////
void Motor::defineOutput() {
  pinMode(digital_one_, OUTPUT);
  pinMode(digital_two_, OUTPUT);
  pinMode(analog_one_, OUTPUT);
  pinMode(encoder_one_, INPUT);
  pinMode(encoder_two_, INPUT);
}

void Motor::initEncoders() {
  switch (id_) {
    case MotorId::BackLeft:
      attachInterrupt(digitalPinToInterrupt(encoder_one_), Encoder::backLeftEncoder, RISING);
    break;
    case MotorId::FrontLeft:
      attachInterrupt(digitalPinToInterrupt(encoder_one_), Encoder::frontLeftEncoder, RISING);
    break;
    case MotorId::BackRight:
      attachInterrupt(digitalPinToInterrupt(encoder_one_), Encoder::backRightEncoder, RISING);
    break;
    case MotorId::FrontRight:
      attachInterrupt(digitalPinToInterrupt(encoder_one_), Encoder::frontRightEncoder, RISING);
    break;
  }
}

//////////////////////////////////Motor State//////////////////////////////////////
void Motor::forward() {
  
  analogWrite(analog_one_, pwm_);

  if(current_state_ == MotorState::Forward) {
    return;
  }
  
  digitalWrite(digital_one_, HIGH);
  digitalWrite(digital_two_, LOW);

  pid_.reset();
  
  current_state_ = MotorState::Forward;
}

void Motor::backward() {

  analogWrite(analog_one_, pwm_);
  
  if(current_state_ == MotorState::Backward) {
    return;
  }
  
  digitalWrite(digital_one_, LOW);
  digitalWrite(digital_two_, HIGH);
  
  pid_.reset();

  current_state_ = MotorState::Backward;
}

void Motor::stop() {
  analogWrite(analog_one_, LOW);

  if(current_state_ == MotorState::Stop) {
    return;
  }

  digitalWrite(digital_one_, LOW);
  digitalWrite(digital_two_, LOW);
  
  pid_.reset();
  
  current_state_ = MotorState::Stop;
}

//////////////////////////////////Velocity//////////////////////////////////////
double Motor::getTargetRps(const double velocity) {
  return MsToRps(velocity) + velocity_adjustment_;
}

double Motor::getTargetTicks(const double velocity) {
  return RpsToTicks( MsToRps(velocity) );
}

double Motor::RpsToTicks(const double rps) {
  return  (rps / kPidCountTimeSamplesInOneSecond) * kPulsesPerRevolution;
}

double Motor::TicksToRps(const double ticks) {
  return  (ticks * kPidCountTimeSamplesInOneSecond) / kPulsesPerRevolution;
}

double Motor::RpsToMs(const double rps) {
  return  rps * M_PI * kWheelDiameter;
}

double Motor::MsToRps(const double ms) {
  return  (ms / ( M_PI * kWheelDiameter));
}

void Motor::changePwm(const uint8_t pwm) {
  pwm_ = pwm;
  switch(current_state_) {
    case MotorState::Forward:
      forward();
    break;
    case MotorState::Backward:
      backward();
    break;
    case MotorState::Stop:
      stop();
    break;
  }
}

void Motor::constantSpeed(const double velocity) {
  double tmp_pwm = pwm_;
  pid_.compute(
    getTargetRps(velocity), current_speed_, tmp_pwm, pid_ticks_,
    kPulsesPerRevolution, kPidCountTimeSamplesInOneSecond
  );

  changePwm(tmp_pwm);
}

//////////////////////////////////Set Methods//////////////////////////////////////
void Motor::setPidTicks(const int pid_ticks) {
  pid_ticks_ = pid_ticks;
}

void Motor::setOdomTicks(const int odom_ticks) {
  odom_ticks_ = odom_ticks;
}

void Motor::setVelocityAdjustment(const double velocity_adjustment) {
  velocity_adjustment_ = velocity_adjustment;
}

//////////////////////////////////Get Methods//////////////////////////////////////
int Motor::getPidTicks() {
  return pid_ticks_;
}

int Motor::getOdomTicks() {
  return odom_ticks_;
}

double Motor::getLastTicks() {
  return last_ticks_;
}

double Motor::getCurrentSpeed() {
  return current_speed_;
}

MotorState Motor::getCurrentState() {
  return current_state_;
}
