#define __STM32F1__

#include <Servo.h> // include servo library to use its related functions


#include <ros.h> 
#include <std_msgs/Int16MultiArray.h>



#define P_PIN    PB7
#define R_PIN PA7

#define SP_Min 70
#define SP_Max 120
#define SR_Max  180
#define SR_Min   0


#define DAMPING     10
#define START_TIME 2000
#define ROUTINE 1
#define CALIBRATION_TIME 2000

#define MAX_PUBLISHERS 10
#define MAX_SUBSCRIBERS 10
#define PUBLISHERS_BUFFER_SIZE 2048
#define SUBSCRIBERS_BUFFER_SIZE 2048

#define BAUD_RATE 115200

ros::NodeHandle_<ArduinoHardware,
                 MAX_PUBLISHERS,
                 MAX_SUBSCRIBERS,                 
                 PUBLISHERS_BUFFER_SIZE,           
                 SUBSCRIBERS_BUFFER_SIZE>               
                  nh;                             


Servo JP;  // Define an instance of of Servo with the name of "MG995_Servo"
Servo JR;  // Define an instance of of Servo with the name of "MG995_Servo"




int arm_joints[] = {90, 90};
int arm_state[] = {90, 90};

void damp_write(Servo S, int servo_angle, int setpoint_angle);

void callback_joints(const std_msgs::Int16MultiArray &arm_msg)
{
  arm_joints[0] = constrain(abs(arm_msg.data[0]), SR_Min, SR_Max);
  arm_joints[1] = constrain(abs(arm_msg.data[1]), SP_Min, SP_Max);

  

//  String debug_str = "Got Arm_joints: " + String(arm_joints[0])+ " "+ String(arm_joints[1]);
//  nh.loginfo(&debug_str[0]);
}

ros::Subscriber<std_msgs::Int16MultiArray>  arm_sub("arm_joints",&callback_joints);

void setup() 
{
    JP.attach(P_PIN);  
    JR.attach(R_PIN);


    nh.initNode();
  
    nh.subscribe(arm_sub);

    delay(CALIBRATION_TIME);

}

void loop() {
  nh.spinOnce();

  damp_write(JP, arm_state[0], arm_joints[0] );
  damp_write(JR, arm_state[1], arm_joints[1] );
  
  arm_state[0] = arm_joints[0];
  arm_state[1] = arm_joints[1];
  delay(ROUTINE);
  
}

// servo_angle is the current angle
// setpoint_angle is the target
void damp_write(Servo S, int servo_angle, int setpoint_angle)
{
  if (setpoint_angle > servo_angle)
  {
    while(setpoint_angle > servo_angle)
    {
      servo_angle++;
      S.write(servo_angle);
      delay(DAMPING);
    }
  }

  else if (setpoint_angle < servo_angle)
  {
    while(setpoint_angle < servo_angle)
    {
      servo_angle--;
      S.write(servo_angle);

      delay(DAMPING);
    }
  }
}
