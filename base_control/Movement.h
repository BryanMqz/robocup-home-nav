// This class has all the functions related to Movement.
#ifndef Movement_h
#define Movement_h

#include "MotorId.h"

#include <ros.h>
#include <math.h>
#include <Arduino.h>

#include "BNO.h"
#include "PID.h"
#include "Motor.h"

enum class Direction{
    left = 1,
    right = 2 
};

class Movement {
  public:
    //////////////////////////////////Constructor//////////////////////////////////////
    Movement(BNO * bno, ros::NodeHandle *nh);


    //////////////////////////////////Motors//////////////////////////////////////
    // TODO(Josecisneros001): Change the declaration of motors to a simple array of size 
    // 4 and use MotorId enum as index. 
    Motor back_right_motor_;
    Motor back_left_motor_;
    Motor front_right_motor_;
    Motor front_left_motor_;


    //////////////////////////////////Encoders//////////////////////////////////////
    // Initialize motor encoders.
    void initEncoders();


    //////////////////////////////////PWM//////////////////////////////////////
    // Set same pwm to all motors.
    void changePwm(const uint8_t pwm);


    //////////////////////////////////VELOCITY//////////////////////////////////////
    // Change deltaX value.
    void setDeltaX(const double delta_x);
    
    // Change deltaY value.
    void setDeltaY(const double delta_y);
    
    // Change deltaAngular value.
    void setDeltaAngular(const double delta_angular);

    // Return deltaX value.
    double getDeltaX();
    
    // Return deltaY value.
    double getDeltaY();
    
    // Return deltaAngular value.
    double getDeltaAngular();
    
    // Return target linear angle.
    double getTargetAngle();
    
    // Return target linear velocity.
    double getTargetLinearVelocity();
    
    // Return target anuglar velocity.
    double getTargetAngularVelocity();
    
    // This function sets a direction according to an angle.
    void setDirection(const int angle); 
    
    // This function change any angle to the closer mechanum direction angle. 
    int angleToDirection(const int angle);
    
    // Stop robot.
    void stop();
    
    //////////////////////////////////PID//////////////////////////////////////
    // Robot moves linear with pid.
    void pidLinearMovement();
    
    // Robot moves angular with pid.
    void pidAngularMovement();
    
    // Robot rotate to a custom targetAngle with pid. Returns true when its done otherwise returns false.
    bool pidRotate(const double target_angle);

    
  private:
  
    //////////////////////////////////DIRECTIONS//////////////////////////////////////
    // This function tells where is the target Angle of the class, left or right.
    Direction whereToGo(double &current_angle);
    
    // This function tells where is a custom target Angle, left or right.
    Direction whereToGo(double &current_angle, const double target_angle);
    
    // Convert radians to degrees.
    double radiansToDegrees(const double radians);

    
    // Put motors in 0° direction.
    void move0();
    
    // Put motors in 45° direction.
    void move45();
    
    // Put motors in 90° direction.
    void move90();
    
    // Put motors in 135° direction.
    void move135();
    
    // Put motors in 180° direction.
    void move180();
    
    // Put motors in 225° direction.
    void move225();
    
    // Put motors in 270° direction.
    void move270();
    
    // Put motors in 315° direction.
    void move315();
    
    // Put motors rotating left.
    void rotateLeft();
    
    // Put motors rotating right.
    void rotateRight();


    //////////////////////////////////PID//////////////////////////////////////
    // Set motors to respect linear velocity. 
    void constantLinearSpeed();
    
    // Set motors to respect angular velocity. 
    void constantAngularSpeed();
    
    // Fix robot inclination while is moving.
    void velocityAdjustment(const int adjustment);

    // Pins,
    static constexpr uint8_t kDigitalPinsFrontLeftMotor[2] = {14, 15};
    static constexpr uint8_t kAnalogPinFrontLeftMotor = 11;
    static constexpr uint8_t kEncoderPinsFrontLeftMotor[2] = {3, 25};

    static constexpr uint8_t kDigitalPinsBackLeftMotor[2] = {22, 23};
    static constexpr uint8_t kAnalogPinBackLeftMotor = 6;
    static constexpr uint8_t kEncoderPinsBackLeftMotor[2] = {2, 37};

    static constexpr uint8_t kDigitalPinsFrontRightMotor[2] = {27,26};
    static constexpr uint8_t kAnalogPinFrontRightMotor = 7;
    static constexpr uint8_t kEncoderPinsFrontRightMotor[2] = {19, 33};

    static constexpr uint8_t kDigitalPinsBackRightMotor[2] = {30,31};
    static constexpr uint8_t kAnalogPinBackRightMotor = 8;
    static constexpr uint8_t kEncoderPinsBackRightMotor[2] = {18, 29};

    // ROS
    ros::NodeHandle * nh_;

    // Bno.
    BNO *bno_;
    
    // Pid.
    int target_angle_ = 0;
    double straight_output_ = 0;
    PID pid_straight_;
    PID pid_rotation_;
    static constexpr uint8_t kPidMovementTimeSample = 100;
    static constexpr uint16_t kPidMaxErrorSum = 3000;
    static constexpr double kOutputMinLimitPidStraight = -0.175;
    static constexpr double kOutputMaxLimitPidStraight = 0.175;
    static constexpr double kPPidStraight = 0.0008;
    static constexpr double kIPidStraight = 0.00015;
    static constexpr double kDPidStraight = 0.0002;
    static constexpr double kOutputMinLimitPidRotation = -0.18;
    static constexpr double kOutputMaxLimitPidRotation = 0.18;
    static constexpr double kOutputAdjustment = -0.075;
    static constexpr double kPidRotationTolerance = 1;
    static constexpr double kPPidRotation = 0.00050;
    static constexpr double kIPidRotation = 0.00110;
    static constexpr double kDPidRotation = 0.00080;
    
    // Velocity.
    double delta_x_ = 0;
    double delta_y_ = 0;
    double delta_angular_ = 0;

    // Constants.
    static constexpr uint16_t kIntMax = 65535;
    static constexpr uint16_t kMinAngle = 0;
    static constexpr uint16_t kInterAngle = 180;
    static constexpr uint16_t kMaxAngle = 360;
    static constexpr uint16_t kDirectionSeparationAngle = 45;
    static constexpr uint16_t kCountDirections = kMaxAngle/kDirectionSeparationAngle;
        
};
#endif
