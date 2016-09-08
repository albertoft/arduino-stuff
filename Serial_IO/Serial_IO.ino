int ledPin = 13;
int incomingByte = 0;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  Serial.println(HIGH);
  digitalWrite(ledPin, HIGH);
  delay(2000);
  
  Serial.println(LOW);
  digitalWrite(ledPin, LOW);
  delay(2000);

  if (Serial.available() > 0) {
    incomingByte = Serial.read();
    //lo vuelca a pantalla
    Serial.print("RX: "); 
    Serial.println(incomingByte, DEC);
  } else {
    Serial.println("RX: N/A");
  }
}
