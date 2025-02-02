#include "Movement.h"

//////////////////////////////////Constructor//////////////////////////////////////
Movement::Movement(BNO *bno, ros::NodeHandle *nh) : bno_(bno), nh_(nh),
pid_straight_(kPPidStraight, kIPidStraight, kDPidStraight, kOutputMinLimitPidStraight, 
kOutputMaxLimitPidStraight, kPidMaxErrorSum, kPidMovementTimeSample), 
pid_rotation_(kPPidRotation, kIPidRotation, kDPidRotation, kOutputMinLimitPidRotation, 
kOutputMaxLimitPidRotation, kPidMaxErrorSum, kPidMovementTimeSample) {
  
  back_left_motor_ = Motor(MotorId::BackLeft, kDigitalPinsBackLeftMotor[0], 
                          kDigitalPinsBackLeftMotor[1], kAnalogPinBackLeftMotor, 
                          kEncoderPinsBackLeftMotor[0], kEncoderPinsBackLeftMotor[1]);
  front_left_motor_ = Motor(MotorId::FrontLeft, kDigitalPinsFrontLeftMotor[0], 
                            kDigitalPinsFrontLeftMotor[1], kAnalogPinFrontLeftMotor, 
                            kEncoderPinsFrontLeftMotor[0], kEncoderPinsFrontLeftMotor[1]);
  back_right_motor_ = Motor(MotorId::BackRight, kDigitalPinsBackRightMotor[0], 
                            kDigitalPinsBackRightMotor[1], kAnalogPinBackRightMotor, 
                            kEncoderPinsBackRightMotor[0], kEncoderPinsBackRightMotor[1]);
  front_right_motor_ = Motor(MotorId::FrontRight, kDigitalPinsFrontRightMotor[0], 
                            kDigitalPinsFrontRightMotor[1], kAnalogPinFrontRightMotor, 
                            kEncoderPinsFrontRightMotor[0], kEncoderPinsFrontRightMotor[1]);
}

//////////////////////////////////Encoders//////////////////////////////////////

void Movement::initEncoders() {
  back_left_motor_.initEncoders();
  front_left_motor_.initEncoders();
  back_right_motor_.initEncoders();
  front_right_motor_.initEncoders();
}

//////////////////////////////////PWM//////////////////////////////////////

void Movement::changePwm(const uint8_t pwm) {
  back_left_motor_.changePwm(pwm);
  front_left_motor_.changePwm(pwm);
  back_right_motor_.changePwm(pwm);
  front_right_motor_.changePwm(pwm);
}


//////////////////////////////////VELOCITY//////////////////////////////////////

void Movement::setDeltaX(const double delta_x) {
  delta_x_ = delta_x;
}

void Movement::setDeltaY(const double delta_y) {
  delta_y_ = delta_y;
}

void Movement::setDeltaAngular(const double delta_angular) {
  delta_angular_ = delta_angular;
}

double Movement::getDeltaX(){
  return delta_x_;
}

double Movement::getDeltaY(){
  return delta_y_;
}

double Movement::getDeltaAngular(){
  return delta_angular_;
}


double Movement::getTargetAngle() {
  //If delta_x_ = 0 it means the angle is either in 90 or 270 degrees, depending on delta_y sign.
  if(delta_x_ == 0) {
    if(delta_y_ > 0) {
      return 90;
    } else {
      return 270;
    }
  }
  // If delta_y_ == 0 it means the angle is either in 0 or 180 degrees, depending on delta_x sign.
  if(delta_y_ == 0) {
    if(delta_x_ > 0) {
      return 0;
    } else {
      return 180;
    }
  }
  const double angle_first_quadrant = radiansToDegrees(atan( abs(delta_y_) / abs(delta_x_)));
  
  // If delta_x is negative and delta_y is positve that means angle is in the second quadrant.
  if(delta_x_ < 0 && delta_y_ > 0 ) {
    return angle_first_quadrant + 90;
  }
  // If both delta_x and delta_y are negative that means angle is in the third quadrant.
  if(delta_x_ < 0 && delta_y_ < 0 ) {
    return angle_first_quadrant + 180;
  }
  // If delta_x is positve and delta_y is negative that means angle is in the fourth quadrant.
  if(delta_x_ > 0 && delta_y_ < 0 ) {
    return angle_first_quadrant + 270;
  }
  // If both delta_y and delta_x are positve that means angle is in the first quadrant.
  return angle_first_quadrant;
}

double Movement::radiansToDegrees(const double radians) {
  return radians * 180 / M_PI;
}

double Movement::getTargetLinearVelocity() {
  return sqrt(delta_x_ * delta_x_ + delta_y_ * delta_y_);
}

double Movement::getTargetAngularVelocity() {
  return delta_angular_;
}

void Movement::stop() {
  front_left_motor_.stop();
  back_left_motor_.stop();
  front_right_motor_.stop();
  back_right_motor_.stop();
}

//////////////////////////////////DIRECTIONS//////////////////////////////////////
Direction Movement::whereToGo(double &current_angle) {
    return whereToGo(current_angle, target_angle_);
}

Direction Movement::whereToGo(double &current_angle, const double target_angle) {
    double current_a = bno_->getCurrentXAngle();
    current_angle = current_a;
    double diff_angle = current_a - target_angle; 

    int sign = 0;
    
    if(diff_angle >= kMinAngle && diff_angle <= kInterAngle || 
      (diff_angle <= kInterAngle * -1 && diff_angle >= kMaxAngle * -1)) {
      sign =  1; 
    } else {
      sign = -1;
    }
    
    diff_angle = static_cast<int>(diff_angle) % kMaxAngle; 
    current_angle = sign * ((diff_angle > kInterAngle) ? kMaxAngle - diff_angle : diff_angle);

    if(sign != 1) {
        return Direction::right;
    }
    return Direction::left;
}

int Movement::angleToDirection(const int angle) {
    int diff = kIntMax;
    for(int i = 0; i <= kCountDirections; ++i) {
        if(diff > abs(angle - i * kDirectionSeparationAngle) ) {
            diff = abs(angle - i * kDirectionSeparationAngle);
        } else {
            return (i - 1) * kDirectionSeparationAngle;
        }
    }
    return 0;
}

void Movement::setDirection(const int angle) {
  switch(angle) {
    case 0:
      move0();
    break;
    case 45:
      move45();
    break;
    case 90:
      move90();
    break;
    case 135:
      move135();
    break;
    case 180:
      move180();
    break;
    case 225:
      move225();
    break;
    case 270:
      move270();
    break;
    case 315:
      move315();
    break;
  }
}

void Movement::move0() {
  front_left_motor_.forward();
  back_left_motor_.backward();
  front_right_motor_.backward();
  back_right_motor_.forward();
}

void Movement::move45() {
  front_left_motor_.forward();
  back_left_motor_.stop();
  front_right_motor_.stop();
  back_right_motor_.forward();
}

void Movement::move90() {
  front_left_motor_.forward();
  back_left_motor_.forward();
  front_right_motor_.forward();
  back_right_motor_.forward();
}

void Movement::move135() {
  front_left_motor_.stop();
  back_left_motor_.forward();
  front_right_motor_.forward();
  back_right_motor_.stop();
}

void Movement::move180() {
  front_left_motor_.backward();
  back_left_motor_.forward();
  front_right_motor_.forward();
  back_right_motor_.backward();
}

void Movement::move225() {
  front_left_motor_.backward();
  back_left_motor_.stop();
  front_right_motor_.stop();
  back_right_motor_.backward();
}

void Movement::move270() {
  front_left_motor_.backward();
  back_left_motor_.backward();
  front_right_motor_.backward();
  back_right_motor_.backward();
}

void Movement::move315() {
  front_left_motor_.stop();
  back_left_motor_.backward();
  front_right_motor_.backward();
  back_right_motor_.stop();
}

void Movement::rotateLeft() {
  front_left_motor_.backward();
  back_left_motor_.backward();
  front_right_motor_.forward();
  back_right_motor_.forward();  
}

void Movement::rotateRight() {
  front_left_motor_.forward();
  back_left_motor_.forward();
  front_right_motor_.backward();
  back_right_motor_.backward();
}

//////////////////////////////////PID//////////////////////////////////////
void Movement::constantLinearSpeed() {
  front_right_motor_.constantSpeed(getTargetLinearVelocity());
  front_left_motor_.constantSpeed(getTargetLinearVelocity());
  back_left_motor_.constantSpeed(getTargetLinearVelocity());
  back_right_motor_.constantSpeed(getTargetLinearVelocity());
}

void Movement::constantAngularSpeed() {
  front_right_motor_.constantSpeed(getTargetAngularVelocity());
  front_left_motor_.constantSpeed(getTargetAngularVelocity());
  back_left_motor_.constantSpeed(getTargetAngularVelocity());
  back_right_motor_.constantSpeed(getTargetAngularVelocity());
}

void Movement::velocityAdjustment(const int adjustment) {
  back_left_motor_.setVelocityAdjustment(
    (back_left_motor_.getCurrentState() == MotorState::Forward) ? adjustment * -1 : adjustment
  );
  front_left_motor_.setVelocityAdjustment(
    (front_left_motor_.getCurrentState() == MotorState::Forward) ? adjustment * -1 : adjustment
  );
  back_right_motor_.setVelocityAdjustment(
    (back_right_motor_.getCurrentState() == MotorState::Backward) ? adjustment * -1 : adjustment
  );
  front_right_motor_.setVelocityAdjustment(
    (front_right_motor_.getCurrentState() == MotorState::Backward) ? adjustment * -1 : adjustment
  );
}

void Movement::pidLinearMovement() {
    setDirection(angleToDirection(getTargetAngle()));
    constantLinearSpeed();
    

    double angle_error = 0;
    Direction where = whereToGo(angle_error);
    pid_straight_.compute(angle_error,  straight_output_, 0);
    velocityAdjustment(straight_output_);
}

void Movement::pidAngularMovement() {
    if(delta_angular_ < 0) {
        rotateRight();
    } else {
        rotateLeft();
    }
    constantAngularSpeed();
}

bool Movement::pidRotate(const double target_angle) {
    double output = 0;
    double angle_error = 0;
    Direction where = whereToGo(angle_error, target_angle);
    
    if(abs(angle_error) <= kPidRotationTolerance && 
       abs(pid_rotation_.getPre()) <= kPidRotationTolerance && 
       angle_error * pid_rotation_.getPre() >= 0) {
       
        stop();
        return true;
    }

    pid_rotation_.compute(angle_error,  output, 1);
    output = abs(output)+kOutputAdjustment;
    
    if(where == Direction::left) {
        rotateLeft();
    } else {
        rotateRight();
    }

    back_left_motor_.setVelocityAdjustment(output);
    front_left_motor_.setVelocityAdjustment(output);
    back_right_motor_.setVelocityAdjustment(output);
    front_right_motor_.setVelocityAdjustment(output);
    constantAngularSpeed();
   
    return false;
}