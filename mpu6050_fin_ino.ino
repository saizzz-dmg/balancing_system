#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

int left_forward  = 9;
int left_reverse = 10;
int right_forward = 11;
int right_reverse = 12;

int time = 0;
char dir = NULL;
char prev_dir = NULL;

void setup() 
{
  Serial.begin(115200);

  Serial.println("Initialize MPU6050");

  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }
  pinMode(left_forward, OUTPUT);
  pinMode(left_reverse , OUTPUT);
  pinMode(right_forward , OUTPUT);
  pinMode(right_reverse , OUTPUT);
}

void loop()
{
  Vector normAccel = mpu.readNormalizeAccel();
  int tilt = (atan2(normAccel.YAxis, normAccel.ZAxis)*180.0)/M_PI;
  Serial.print(" Tilt = ");
  Serial.print(tilt); 
  Serial.println();

  if (tilt > 2){
    if (dir && time){
      Serial.print("time balancing");
      digitalWrite(right_reverse , HIGH);
      delay(time);
      digitalWrite(right_reverse , LOW);
      prev_dir = NULL;
      dir = NULL;
      time = 0;
    }
    else{
    Serial.print("left motor activated");
    digitalWrite(left_forward, HIGH);
    prev_dir = "left";
    time  = time+100;
    }
  }
  else if (tilt < -2){
    if (dir && time){
      Serial.print("time balancing");
      digitalWrite(left_reverse , HIGH);
      delay(time);
      digitalWrite(left_reverse , LOW);
      prev_dir = NULL;
      dir = NULL;
      time = 0;
    }
    else{
    Serial.print("right motor activated");
    digitalWrite(right_forward, HIGH);
    prev_dir = "right";
    time  = time+100;
    }
  }
  else{
    digitalWrite(right_forward, LOW);
    digitalWrite(left_forward, LOW);

    if (prev_dir){
      dir = prev_dir;
      prev_dir = NULL;
    }
  }
  delay(100);

}
    






















