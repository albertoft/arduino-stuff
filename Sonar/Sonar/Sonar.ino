#include <Servo.h>

// servo-motor
#define pSERVO 12
#define SERVODELAY 15
#define ANGLEMAX 165
#define ANGLEMIN 15
Servo myservo;
int servoPos = 15;
int servoDir = 1;

// ultra-sonic sensor
#define pECHO 10
#define pTRIG 11
#define RANGEMAX 40
#define RANGE1 (RANGEMAX*0.33)
#define RANGE2 (RANGEMAX*0.66)
#define RANGE3 RANGEMAX
long duration, distance;    // duration used to calculate distance

// LEDs
#define pLEDBAR3 9
#define pLEDBAR2 8
#define pLEDBAR1 7
#define LEDBARSIZE 3
#define pLEDMODE 13
int ledBar[LEDBARSIZE] = {pLEDBAR1, pLEDBAR2, pLEDBAR3};

// buzzer
#define pBUZZ 6

// button
#define pBUTTON 2
#define MANUALMODE HIGH
#define AUTOMODE LOW
int mode = AUTOMODE;

// pot
#define pPOT A0

// Initialize
void setup() {
  Serial.begin (9600);

  // servo
  myservo.attach(pSERVO);

  // ultrasonic
  pinMode(pTRIG, OUTPUT);
  pinMode(pECHO, INPUT);

  // LEDs
  ledBarStart();

  // mode
  pinMode(pLEDMODE, OUTPUT);

  // button
  attachInterrupt(digitalPinToInterrupt(pBUTTON), changeMode, RISING);
}

// Main loop
void loop() {
  // calculate next servo position depending on MANUAL or AUTO mode
  servoPosition();
  
  // move servo
  myservo.write(servoPos);
  delay(SERVODELAY);

  // calculate ultrasonic object distance
  distance = ultraSonicDistance();
  
  // data to serial port: pos,distance.
  // this data can be processed with "Processing" to plot a radar graph
  Serial.print(servoPos);
  Serial.print(",");
  Serial.print(distance);
  Serial.print(".");

  // use LEDs to represent object found in RANGE 33%, RANGE 66%, RANGE
  ledBarDistance(distance);
}


// Calculate next servo position depending on MANUAL or AUTO mode
void servoPosition() {
  // MANUALMODE
  if (mode == MANUALMODE) {
    int potVal = analogRead(pPOT);
    servoPos = map(potVal, 1023, 0, ANGLEMIN, ANGLEMAX);
  }
  // AUTOMODE
  else {
    if (servoDir) { 
      servoPos++;
      if (servoPos >= ANGLEMAX) servoDir = !servoDir; 
    } else {
      servoPos--;
      if (servoPos <= ANGLEMIN) servoDir = !servoDir;
    }
  }
}

// Calculate distance measured by ultrasonic sensor
int ultraSonicDistance() {
  // pTRIG/pECHO cycle is used to determine the distance of the nearest object by bouncing soundwaves off of it  
  digitalWrite(pTRIG, LOW); 
  delayMicroseconds(2);
  digitalWrite(pTRIG, HIGH); 
  delayMicroseconds(10);
  digitalWrite(pTRIG, LOW);

  // pECHO returns the sound wave travel time (in microseconds)
  duration = pulseIn(pECHO, HIGH);
  distance = duration / 29 / 2;
  return distance;
}

// Turn on a 3 led as follows:
// object found in 33%  RANGEMAX (danger!)    => turn on 3 LEDs, 
// object found in 66%  RANGEMAX (too close!) => turn on 2 LEDs, 
// object found in 100% RANGEMAX (warning)    => turn on 1 LED 
void ledBarDistance(int dist) {
  digitalWrite(pLEDBAR1, LOW);
  digitalWrite(pLEDBAR2, LOW);
  digitalWrite(pLEDBAR3, LOW);
  
  if ((dist > 0) && (dist <= RANGE3)) {
    digitalWrite(pLEDBAR1, HIGH);
  } 
  if ((dist > 0) && (dist <= RANGE2)) {
    digitalWrite(pLEDBAR2, HIGH);
  }
  if ((dist > 0) && (dist <= RANGE1)) {
    digitalWrite(pLEDBAR3, HIGH);
    tone(pBUZZ, 1024, 10);
  }
}

// Initialization for LED bar
void ledBarStart() {
  pinMode(pLEDBAR3, OUTPUT);
  pinMode(pLEDBAR2, OUTPUT);
  pinMode(pLEDBAR1, OUTPUT);

  for (int i=0; i < LEDBARSIZE; i++) {
    digitalWrite(ledBar[i], HIGH);
    delay(300);
    digitalWrite(ledBar[i], LOW);
  }
}

// Change mode button ISR (Interrupt Service Routine). 
void changeMode() {
  // switch mode
  mode = (mode == AUTOMODE) ? MANUALMODE:AUTOMODE;
  
  // update mode LED
  digitalWrite(pLEDMODE, mode);

  // set servo conditions
  if (mode == AUTOMODE) {
    servoDir = 1;
  }
  servoPos = ANGLEMIN;
}
