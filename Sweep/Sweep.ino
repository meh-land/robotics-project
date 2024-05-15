#include <Servo.h>

#define R_SERVO_PIN PA7
#define P_SERVO_PIN PB7
#define P_max 120
#define P_min 70
#define R_max 180
#define R_min 0
#define DELAY 30

Servo Pservo;  // create servo object to control Prismatic joint
Servo Rservo;  // create servo object to control Revolute joint

int Ppos = 0;    // variable to store the servo position
int Rpos = 0;
int Plen = 2*(P_max - P_min) + 2;
int Rlen = 2*(R_max - R_min) + 2;
int P_vals[2*(P_max - P_min) + 2];
int R_vals[2*(R_max - R_min) + 2];
int i = 0;
char txt_buffer[128];

void setup() {
  Pservo.attach(P_SERVO_PIN);
  Rservo.attach(R_SERVO_PIN);
  Serial.begin(9600);
  // populate servo arrays
  for(int Ri = R_min; Ri <= R_max; Ri++){R_vals[i] = Ri; i++;}
  for(int Ri = R_max; Ri >= R_min; Ri--){R_vals[i] = Ri; i++;}
  i = 0;
  for(int Pi = P_min; Pi <= P_max; Pi++){P_vals[i] = Pi; i++;}
  for(int Pi = P_max; Pi >= P_min; Pi--){P_vals[i] = Pi; i++;}
  i = 0;
}

void loop() {
  Ppos = P_vals[i % Plen];
  Rpos = R_vals[i % Rlen];
  Pservo.write(Ppos);
  Rservo.write(Rpos);
  sprintf(txt_buffer, "P = %d, R = %d\n", Ppos, Rpos);
  Serial.print(txt_buffer);
  i++;
  if(i == Plen*Rlen){i = 0;} // make it zero every once in a while to avoid int overflow
  delay(DELAY);

}
