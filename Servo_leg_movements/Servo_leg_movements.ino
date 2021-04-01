#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
// you can also call it with a different address you want
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x41);
// you can also call it with a different address and I2C interface
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40, Wire);


#define SERVOMIN  230// This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  450 // This is the 'maximum' pulse length count (out of 4096)
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

// Servo InfoF
uint8_t FrontRightUpper=1;
uint8_t FrontLeftUpper=0;
uint8_t BackRightUpper=3;
uint8_t BackLeftUpper=2;

uint8_t FrontRightMid=5;
uint8_t FrontLeftMid=4;
uint8_t BackRightMid=7;
uint8_t BackLeftMid=6;

uint8_t FrontRightLower=9;
uint8_t FrontLeftLower=8;
uint8_t BackRightLower=11;
uint8_t BackLeftLower=10;
uint16_t rez=0;
//End of server Info

const uint16_t FrontLegsMin=200;
const uint16_t FrontLegsMax=300;
const uint16_t FrontLowerMin=135;
const uint16_t FrontLowerMid=205;
const uint16_t FrontLowerMax=400;
const uint16_t BackLowerMin=250;//250
const uint16_t BackLowerMid=400;
const uint16_t BackLowerMax=480;
const uint16_t FrontLeftUpperMin=400;
const uint16_t FrontLeftUpperMax=200;
const uint16_t FrontRightUpperMin=240;
const uint16_t FrontRightUpperMax=400;
const uint16_t BackRightUpperMin=250;
const uint16_t BackRightUpperMax=400;
const uint16_t BackLeftUpperMin=255;
const uint16_t BackLeftUpperMax=400;//435

int data; 
void setup() {
  Serial.begin(9600);
  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates
  delay(10);
}

uint16_t FrontLowerFMax=320;
void FrontLowerLeftForwardUp(){
  for (uint16_t pulselen = FrontLowerMid; pulselen < FrontLowerFMax; pulselen++) {
    delay(6);
    Serial.println(pulselen);
    pwm.setPWM(FrontLeftLower,0,pulselen); 
  }
}
void FrontLowerLeftForwardDown(){
for (uint16_t pulselen = FrontLowerFMax; pulselen > FrontLowerMid; pulselen--) {
    delay(6);
    Serial.println(pulselen);
    pwm.setPWM(FrontLeftLower,0,pulselen); 
  }
  }

void FrontLowerRightForwardUp(){
  for (uint16_t pulselen = FrontLowerMid; pulselen < FrontLowerMax; pulselen++) {
    delay(6);
    Serial.println(pulselen);
    pwm.setPWM(FrontRightLower,0,pulselen); 
  }
}
void FrontLowerRightForwardDown(){
for (uint16_t pulselen = FrontLowerMax; pulselen > FrontLowerMid; pulselen--) {
    delay(6);
    Serial.println(pulselen);
    pwm.setPWM(FrontRightLower,0,pulselen); 
  }
  }
const uint16_t FrontLowerWalkMin=180;
void BackLowerRightForwardStand(){
  for (uint16_t pulselen = BackLowerMin; pulselen < BackLowerMid; pulselen++) {
    delay(6);
    Serial.println(pulselen);
    pwm.setPWM(BackRightLower,0,pulselen);
  } 
}
void BackLowerRightForwardSit(){
  for (uint16_t pulselen = BackLowerMid; pulselen > BackLowerMin; pulselen--) {
    delay(6);
    Serial.println(pulselen);
    pwm.setPWM(BackRightLower,0,pulselen);
  }
  }

 
void BackLowerLeftForwardStand(){
  for (uint16_t pulselen = BackLowerMin; pulselen < BackLowerMid; pulselen++) {
    delay(6);
    Serial.println(pulselen);
    pwm.setPWM(BackLeftLower,0,pulselen);
  } 
}
void BackLowerLeftForwardSit(){
  for (uint16_t pulselen = BackLowerMid; pulselen > BackLowerMin; pulselen--) {
    delay(6);
    Serial.println(pulselen);
    pwm.setPWM(BackLeftLower,0,pulselen);
  }
  }

  uint16_t FrontLeftUpperForwardMax=275;
void FrontLeftUpperForward()
{
  for (uint16_t pulselen = FrontLeftUpperMin; pulselen > FrontLeftUpperForwardMax; pulselen--) {
    delay(6);
    Serial.println(pulselen);
    pwm.setPWM(FrontLeftUpper,0,pulselen);
  }
}

void FrontLeftUpperBackward(){
for (uint16_t pulselen = FrontLeftUpperForwardMax; pulselen < FrontLeftUpperMin; pulselen++) {
    delay(6);
    Serial.println(pulselen);
    pwm.setPWM(FrontLeftUpper,0,pulselen);
  }
}
uint16_t FrontRightUpperFMax=345;
void FrontRightUpperForward(){
  for (uint16_t pulselen = FrontRightUpperMin; pulselen < FrontRightUpperFMax; pulselen++) {
    delay(6);
    Serial.println(pulselen);
    pwm.setPWM(FrontRightUpper,0,pulselen); 
  }
}

void FrontRightUpperBackward(){
  for (uint16_t pulselen = FrontRightUpperFMax; pulselen > FrontRightUpperMin; pulselen--) {
    delay(6);
    Serial.println(pulselen);
    pwm.setPWM(FrontRightUpper,0,pulselen);
  }
}
void BackRightUpperBackward(){
  for (uint16_t pulselen = BackRightUpperMax; pulselen > BackRightUpperMin; pulselen--) {
    delay(6);
    Serial.println(pulselen);
    pwm.setPWM(BackRightUpper,0,pulselen); 
  }
}
void BackRightUpperForward(){
  for (uint16_t pulselen = BackRightUpperMin; pulselen < BackRightUpperMax; pulselen++) {
    delay(6);
    Serial.println(pulselen);
    pwm.setPWM(BackRightUpper,0,pulselen);
  }
  }
  void BackLeftUpperBackward(){
  for (uint16_t pulselen = BackLeftUpperMin; pulselen < BackLeftUpperMax; pulselen++) {
    delay(6);
    Serial.println(pulselen);
    pwm.setPWM(BackLeftUpper,0,pulselen); 
  }
}

void BackLeftUpperForward(){
  for (uint16_t pulselen = BackLeftUpperMax; pulselen > BackLeftUpperMin; pulselen--) {
    delay(6);
    Serial.println(pulselen);
    pwm.setPWM(BackLeftUpper,0,pulselen);
  }
  }

void loop() {
  (Serial.available());  
     data = Serial.read(); 
     switch(data){
    case'o':FrontLowerLeftForwardUp();break;
      case'p':FrontLowerLeftForwardDown();break;

      case 'q':FrontLeftUpperForward();break;
      case 'r':FrontLeftUpperBackward();break;

      case 's':FrontRightUpperForward();break;
      case 't':FrontRightUpperBackward();break;

      case 'u':FrontLowerRightForwardUp();break;
      case 'v':FrontLowerRightForwardDown();break;

      case 'w':BackRightUpperBackward();break;
      case 'x':BackRightUpperForward();break;

      case 'y':BackLowerRightForwardStand();break; //opp
      case 'z':BackLowerRightForwardSit();break; //opp

      case 'A':BackLeftUpperBackward();break;
      case 'B':BackLeftUpperForward();break;

      case 'C':BackLowerLeftForwardStand();break;
      case '!':BackLowerLeftForwardSit();break;
     }
  }
