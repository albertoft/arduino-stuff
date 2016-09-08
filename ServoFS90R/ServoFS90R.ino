#include <Servo.h>

#define pSERVORIGHT 10
#define pSERVOLEFT 9

Servo servoRight;
Servo servoLeft;

void setup() {
  servoRight.attach(pSERVORIGHT);
  servoLeft.attach(pSERVOLEFT);  
}

void loop() {
  // full speed one direction
  servoLeft.write(0);
  servoRight.write(180);
  delay(5000);

  // stop
  servoLeft.write(90);
  servoRight.write(90);
  delay(5000);

  // full speed the other direction
  servoLeft.write(180);
  servoRight.write(0);
  delay(5000);
}
