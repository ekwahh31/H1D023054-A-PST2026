#include <Servo.h>

const int servoPin = 9;
const int ledPin = 8;
const int btnUp = 2;

int pos = 0;

bool DRSnyala = false;

void setup() {
  myservo.attach(servoPin);

  Serial.begin(9600);

  pinMode(btnUp, INPUT_PULLUP);

  pinMode(ledPin, OUTPUT):

  servo.drs=0;
   
}

void loop() {
  bool upState = digitalRead(btnUp);

  if(digitalRead(buttonPin) == LOW) {
    drsServo.write(90);

    Serial.print("DRS : ACTIVE");
  }

  else {
    drsServo.write(0);

    Serial.print("DRS: CLOSED");
  }
}
