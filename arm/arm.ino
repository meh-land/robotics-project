#define __STM32F1__

#include <Servo.h> // include servo library to use its related functions


#include <ros.h> 
#include <std_msgs/Int16MultiArray.h>



#define BASE_PIN    PA3
#define GRIPPER_PIN PA7

#define S1_Min 0
#define S1_Max 90
#define S2_Max  90
#define S2_Min   0


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


Servo J1;  // Define an instance of of Servo with the name of "MG995_Servo"
Servo J2;  // Define an instance of of Servo with the name of "MG995_Servo"




int arm_joints[] = {90, 90};
int arm_state[] = {90, 90};

void damp_write(Servo S, int servo_angle, int setpoint_angle);

void callback_joints(const std_msgs::Int16MultiArray &arm_msg)
{
  arm_joints[0] = constrain(abs(arm_msg.data[0]), S2_Min, S2_Max);
  arm_joints[1] = constrain(abs(arm_msg.data[1]), S1_Min, S1_Max);

  

//  String debug_str = "Got Arm_joints: " + String(arm_joints[0])+ " "+ String(arm_joints[1]);
//  nh.loginfo(&debug_str[0]);
}

ros::Subscriber<std_msgs::Int16MultiArray>  arm_sub("arm_joints",&callback_joints);

void setup() 
{
    J1.attach(BASE_PIN);  
    J2.attach(GRIPPER_PIN);


    nh.initNode();
  
    nh.subscribe(arm_sub);

    delay(CALIBRATION_TIME);

}

void loop() {
  nh.spinOnce();

  damp_write(J1, arm_state[0], arm_joints[0] );
  damp_write(J2, arm_state[1], arm_joints[1] );
  
  arm_state[0] = arm_joints[0];
  arm_state[1] = arm_joints[1];
  delay(ROUTINE);
  
}

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
