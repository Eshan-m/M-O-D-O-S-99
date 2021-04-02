#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
byte com = 0;
Servo myServo;

void setup() {
 Serial.begin(9600);
 myServo.attach(9);
delay(2000);
Serial.write(0xAA);
Serial.write(0x37);
delay(1000);

Serial.write(0xAA);
Serial.write(0x21);
}

void loop() {
while(Serial.available()){
  com = Serial.read();
  switch(com){

    case forward(0x11)://command 1
    myServo.write(forward);
    break;

    case backwards(0x12)://command 2
    myServo.write(backwards);
    break;

    case turnrigth(0x13):// command 3
    myServo.write(turnright);
    break;

    case turnleft(0x14): //command 4
    myServo.write(turnleft);
    break;
    
    case stop(0x15): //command 5
    myServo.write(stop);
    break; 
  }
}

}
