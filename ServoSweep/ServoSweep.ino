/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards


int MOVE = 0;

int pos = 0;    // variable to store the servo position
int maxAngle = 180;
int delayTime = 15;


void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
}

void loop() {
  
  if (MOVE == 0) {
    myservo.write(0);
  } else {
    for (pos = 0; pos <= maxAngle; pos += 1) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(delayTime);                       // waits 15ms for the servo to reach the position
    }
    for (pos = maxAngle; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(delayTime);                       // waits 15ms for the servo to reach the position
    }  
  }
}
