#include <SoftwareSerial.h>

#define CMDSTART '#'

SoftwareSerial bt(4, 2); // cross RX-TX

void setup() {
  Serial.begin(9600);
  bt.begin(9600);
}

void loop() {
  int command = 0;
  char buf = ' ';
  
  if (bt.available()) {
    buf = bt.read();

    // no command found
    if (buf != CMDSTART) { 
      return;
    }
    
    command = bt.parseInt();

    // print received command
    Serial.println("rx: " + String(command));

    // send some response to command
    bt.println("tx-response: " + String(command));
  }
}
