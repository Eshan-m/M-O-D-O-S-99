
//SERVO-------------------------------------------------------------------------------
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
uint8_t FrontRightUpper = 1;
uint8_t FrontLeftUpper = 0;
uint8_t BackRightUpper = 3;
uint8_t BackLeftUpper = 2;

uint8_t FrontRightMid = 5;
uint8_t FrontLeftMid = 4;
uint8_t BackRightMid = 7;
uint8_t BackLeftMid = 6;

uint8_t FrontRightLower = 9;
uint8_t FrontLeftLower = 8;
uint8_t BackRightLower = 11;
uint8_t BackLeftLower = 10;
uint16_t rez = 0;

uint8_t FrontLeftRot=12;
uint8_t BackLeftRot=14;
uint8_t BackRightRot=15;
uint8_t FrontRightRot=13;
//End of server Info
const uint16_t FrontLegsMin = 200;
const uint16_t FrontLegsMax = 300;
//SERVO_END___________________________________________________

//LIGHT_SENSOR-----------------------------------
int light = 0;
//LIGHT_SENSOR_END_______________________________
//Voice---------------------------------------------
int group = 1;
byte com = 0;
//Voice_____________________________________________
//Obstical------------------------------------------------
#define echoPin 2 
#define trigPin 3
long duration;
int distance; 
//Obstical_END_____________________________________________


//---------------------------------------------------------------
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);
#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11);
# include <DHT.h>
#define Type DHT11
int sensorGas = A2; // choose the input pin (for Smoke sensor) 
int buzzer = 8; //choose the pin for the Buzzer
String number = "+94763039766";
int read_value; //variable for reading the gaspin status
int set = 50; //we start, assuming Smoke detected
int senseDht=7;
DHT HT (senseDht,Type);
float humidity;
float tempC;
float tempF;
int setTime=500;
int dt=1000;
//__________________________________________________________

int data;
void setup() {
  //Common---------------------
  Serial.begin(9600); 
//Common_END_________________
//SERVO----------------------------
  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates
  delay(10);
//SERVO END________________________
//Obstical----------------------------------------
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
//Obstical_END____________________________________
//Voice-----------------------------------------------------------
Serial.write(0xAA);
Serial.write(0x00);//waiting
delay(1000);
Serial.write(0xAA);
Serial.write(0x37);// compact mode
delay(1000);
Serial.write(0xAA);
Serial.write(0x00);//waiting
delay(1000);
Serial.write(0xAA);
Serial.write(0x21);
//Voice___________________________________________________________
/*LIGHT_SENSOR 
-------------------------------------*/ 

 pinMode(13, OUTPUT); // configure digital pin 13 as an output
 pinMode(12, OUTPUT); // configure digital pin 12 as an output

/*LIGHT SENSOR END
-------------------------------------*/
//------------------------------------------------------------------
randomSeed(analogRead(5));
mySerial.begin(9600); //Setting the baud rate of GSM Module
Serial.begin(9600);  //Setting the baud rate of Serial Monitor (Arduino)
HT.begin();
pinMode(sensorGas, INPUT); //declare sensor as input
pinMode(buzzer,OUTPUT);  //declare Buzzer as output
lcd.begin();
lcd.clear();
lcd.setCursor(0,0);
lcd.print("SMOKE & TEMP");
lcd.setCursor(0,1);
lcd.print("Detector Active");
delay(3000);
lcd.clear();
//____________________________________________________________________

}
//------------------------------------
//Front Lower Range
const uint16_t FrontLowerMin = 70;
const uint16_t FrontLowerMid = 205;
const uint16_t FrontLowerMax = 500;

//Front Lower Test
void FrontLower() {
  for (uint16_t pulselen = FrontLowerMin; pulselen < FrontLowerMax; pulselen++) {
    Serial.println(pulselen);
    delay(300);
    pwm.setPWM(FrontRightLower, 0, pulselen);
    pwm.setPWM(FrontLeftLower, 0, pulselen);
    pwm.setPWM(BackLeftLower, 0, pulselen);
    pwm.setPWM(BackRightLower, 0, pulselen);
  }
  for (uint16_t pulselen = FrontLowerMax; pulselen > FrontLowerMin; pulselen--) {
    Serial.println(pulselen);
    delay(300);
    pwm.setPWM(FrontRightLower, 0, pulselen);
    pwm.setPWM(FrontLeftLower, 0, pulselen);
    pwm.setPWM(BackLeftLower, 0, pulselen);
    pwm.setPWM(BackRightLower, 0, pulselen);
  }
}

//Front Lower Range
const uint16_t RotMin = 70;
const uint16_t RotMid = 300;
const uint16_t RotMax = 590;

void RotationLeftTest() {
  for (uint16_t pulselen = RotMid; pulselen < RotMax; pulselen++) {
    Serial.println(pulselen);
    pwm.setPWM(BackLeftRot, 0, pulselen);
    pwm.setPWM(BackRightRot, 0, pulselen);
    pwm.setPWM(FrontRightRot, 0, pulselen);
    pwm.setPWM(FrontLeftRot, 0, pulselen);
    
  }
  for (uint16_t pulselen = RotMax; pulselen > RotMid; pulselen--) {
    Serial.println(pulselen);
    pwm.setPWM(BackLeftRot, 0, pulselen);
    pwm.setPWM(BackRightRot, 0, pulselen);
    pwm.setPWM(FrontRightRot, 0, pulselen);
    pwm.setPWM(FrontLeftRot, 0, pulselen);
  }
}

void RotationRightTest() {
  for (uint16_t pulselen = RotMid; pulselen > RotMin; pulselen--) {
    Serial.println(pulselen);
    pwm.setPWM(BackLeftRot, 0, pulselen);
    pwm.setPWM(BackRightRot, 0, pulselen);
    pwm.setPWM(FrontRightRot, 0, pulselen);
    pwm.setPWM(FrontLeftRot, 0, pulselen);
  }
  for (uint16_t pulselen = RotMin; pulselen < RotMid; pulselen++) {
    Serial.println(pulselen);
    pwm.setPWM(BackLeftRot, 0, pulselen);
     pwm.setPWM(BackRightRot, 0, pulselen);
     pwm.setPWM(FrontRightRot, 0, pulselen);
     pwm.setPWM(FrontLeftRot, 0, pulselen); 
  }
}

const uint16_t Stop = 270;
const uint16_t WheelBackBackward=280;
const uint16_t WheelForntBackward=315;
const uint16_t WheelFrontForward=240;
const uint16_t WheelBackForward=255;
uint16_t motionF=270;
uint16_t motionB=270;
void WheelsForward() {
    pwm.setPWM(BackLeftLower, 0, 255);
    pwm.setPWM(BackRightLower, 0, WheelBackForward);
     pwm.setPWM(FrontRightLower, 0, WheelFrontForward);
    pwm.setPWM(FrontLeftLower, 0, WheelFrontForward);
  
}
void WheelStop(){
    pwm.setPWM(FrontRightLower, 0, Stop);
    pwm.setPWM(FrontLeftLower, 0, Stop);
    pwm.setPWM(BackLeftLower, 0, Stop);
    pwm.setPWM(BackRightLower, 0, Stop);
  }

void WheelsBack(){
  pwm.setPWM(FrontRightLower, 0, WheelForntBackward);
    pwm.setPWM(FrontLeftLower, 0, WheelForntBackward);
    pwm.setPWM(BackLeftLower, 0, WheelBackBackward);
    pwm.setPWM(BackRightLower, 0, WheelBackBackward);
  }
//270 stop
//280 backward





uint16_t FrontLowerFMax = 320;
void FrontLowerLeftForwardUp() {
  for (uint16_t pulselen = FrontLowerMid; pulselen < FrontLowerFMax; pulselen++) {
    delay(6);
    Serial.println(pulselen);
    pwm.setPWM(FrontLeftLower, 0, pulselen);
  }
}
void FrontLowerLeftForwardDown() {
  for (uint16_t pulselen = FrontLowerFMax; pulselen > FrontLowerMid; pulselen--) {
    delay(6);
    Serial.println(pulselen);
    pwm.setPWM(FrontLeftLower, 0, pulselen);
  }
}

void FrontLowerRightForwardUp() {
  for (uint16_t pulselen = FrontLowerMid; pulselen < FrontLowerMax; pulselen++) {
    delay(6);
    Serial.println(pulselen);
    pwm.setPWM(FrontRightLower, 0, pulselen);
  }
}
void FrontLowerRightForwardDown() {
  for (uint16_t pulselen = FrontLowerMax; pulselen > FrontLowerMid; pulselen--) {
    delay(6);
    Serial.println(pulselen);
    pwm.setPWM(FrontRightLower, 0, pulselen);
  }
}
const uint16_t FrontLowerWalkMin = 180;
void FrontLowerLeftSit() {
  for (uint16_t pulselen = FrontLowerMid; pulselen > FrontLowerWalkMin; pulselen--) {
    delay(6);
    Serial.println(pulselen);
    pwm.setPWM(FrontLeftLower, 0, pulselen);
  }
}

void FrontLowerLeftUp() {
  for (uint16_t pulselen = FrontLowerWalkMin; pulselen < FrontLowerMid; pulselen++) {
    delay(6);
    Serial.println(pulselen);
    pwm.setPWM(FrontLeftLower, 0, pulselen);
  }
}



void FrontLowerRightUp() {
  for (uint16_t pulselen = FrontLowerMid; pulselen > FrontLowerMin; pulselen--) {
    delay(6);
    Serial.println(pulselen);
    pwm.setPWM(FrontRightLower, 0, pulselen);

  }
}
void FrontLowerRightSit() {
  for (uint16_t pulselen = FrontLowerMin; pulselen < FrontLowerMid; pulselen++) {
    delay(6);
    Serial.println(pulselen);
    pwm.setPWM(FrontRightLower, 0, pulselen);
  }
}
//Front Sit

//Front Lower Test
void FrontLowerSit() {
  for (uint16_t pulselen = FrontLowerMid; pulselen > FrontLowerMin; pulselen--) {
    delay(6);
    Serial.println(pulselen);
    pwm.setPWM(FrontRightLower, 0, pulselen);
    pwm.setPWM(FrontLeftLower, 0, pulselen);
  }
}
void FrontLowerUp() {
  for (uint16_t pulselen = FrontLowerMin; pulselen < FrontLowerMid; pulselen++) {
    delay(6);
    Serial.println(pulselen);
    pwm.setPWM(FrontRightLower, 0, pulselen);
    pwm.setPWM(FrontLeftLower, 0, pulselen);
  }
}
//-----------------------------------------------------------------------------------
//Back Lower Range
const uint16_t BackLowerMin = 70; //250
const uint16_t BackLowerMid = 400;
const uint16_t BackLowerMax = 490;

//Back Lower Right Test
void BackLower() {
  for (uint16_t pulselen = BackLowerMin; pulselen < BackLowerMax; pulselen++) {
    delay(600);
    Serial.println(pulselen);
    pwm.setPWM(BackRightLower, 0, pulselen);
    pwm.setPWM(BackLeftLower, 0, pulselen);

  }
  for (uint16_t pulselen = BackLowerMax; pulselen > BackLowerMin; pulselen--) {
    delay(600);
    Serial.println(pulselen);
    pwm.setPWM(BackRightLower, 0, pulselen);
    pwm.setPWM(BackLeftLower, 0, pulselen);
  }
}

void BackLowerRightForwardStand() {
  for (uint16_t pulselen = BackLowerMin; pulselen < BackLowerMid; pulselen++) {
    delay(6);
    Serial.println(pulselen);
    pwm.setPWM(BackRightLower, 0, pulselen);
  }
}
void BackLowerRightForwardSit() {
  for (uint16_t pulselen = BackLowerMid; pulselen > BackLowerMin; pulselen--) {
    delay(6);
    Serial.println(pulselen);
    pwm.setPWM(BackRightLower, 0, pulselen);
  }
}


void BackLowerLeftForwardStand() {
  for (uint16_t pulselen = BackLowerMin; pulselen < BackLowerMid; pulselen++) {
    delay(6);
    Serial.println(pulselen);
    pwm.setPWM(BackLeftLower, 0, pulselen);
  }
}
void BackLowerLeftForwardSit() {
  for (uint16_t pulselen = BackLowerMid; pulselen > BackLowerMin; pulselen--) {
    delay(6);
    Serial.println(pulselen);
    pwm.setPWM(BackLeftLower, 0, pulselen);
  }
}


const uint16_t BackLowerSitMin = 210;
//BackLowerMid=400;
//BackLowerMax=480;
//Back Sit
void BackLowerSit() {
  for (uint16_t pulselen = BackLowerMin; pulselen > BackLowerSitMin; pulselen--) {
    delay(6);
    Serial.println(pulselen);
    pwm.setPWM(BackRightLower, 0, pulselen);
    pwm.setPWM(BackLeftLower, 0, pulselen);

  }
}
void BackLowerUp() {
  for (uint16_t pulselen = BackLowerSitMin; pulselen < BackLowerMin; pulselen++) {
    delay(6);
    Serial.println(pulselen);
    pwm.setPWM(BackRightLower, 0, pulselen);
    pwm.setPWM(BackLeftLower, 0, pulselen);
  }
}

void BackLowerLeftSit() {
  for (uint16_t pulselen = BackLowerMin; pulselen > BackLowerSitMin; pulselen--) {
    delay(6);
    Serial.println(pulselen);
    pwm.setPWM(BackLeftLower, 0, pulselen);

  }
}
void BackLowerLeftUp() {
  for (uint16_t pulselen = BackLowerSitMin; pulselen < BackLowerMin; pulselen++) {
    delay(6);
    Serial.println(pulselen);
    pwm.setPWM(BackLeftLower, 0, pulselen);
  }
}



const uint16_t BackLowerRightSitMin = 223;
void BackLowerRightSit() {
  for (uint16_t pulselen = BackLowerMin; pulselen > BackLowerRightSitMin; pulselen--) {
    delay(6);
    Serial.println(pulselen);
    pwm.setPWM(BackRightLower, 0, pulselen);
  }
}
void BackLowerRightUp() {
  for (uint16_t pulselen = BackLowerRightSitMin; pulselen < BackLowerMin; pulselen++) {
    delay(6);
    Serial.println(pulselen);
    pwm.setPWM(BackRightLower, 0, pulselen);
  }
}

//Back Lower Range
const uint16_t BackLowerLeftMin = 160;
const uint16_t BackLowerLeftMid = 260;
const uint16_t BackLowerLeftMax = 480;
void BackLowerLeft() {
  for (uint16_t pulselen = BackLowerLeftMin; pulselen < BackLowerLeftMid; pulselen++) {
    delay(6);
    Serial.println(pulselen);
    pwm.setPWM(BackLeftLower, 0, pulselen);
  }
  for (uint16_t pulselen = BackLowerLeftMid; pulselen > BackLowerLeftMin; pulselen--) {
    delay(6);
    Serial.println(pulselen);
    pwm.setPWM(BackLeftLower, 0, pulselen);
  }

}
//------------------------------------------------------------------------------------------------------------------------------------


//FrontLeftUpper Range ***********************************
const uint16_t FrontLeftUpperMin=296;//400 //307
const uint16_t FrontLeftUpperMax=295;//200 270

void FrontLeftUpperTest() {
  for (uint16_t pulselen = FrontLeftUpperMin; pulselen > FrontLeftUpperMax; pulselen--) {
    delay(15);
    Serial.println(pulselen);
    pwm.setPWM(FrontLeftUpper, 0, pulselen);
  }
  for (uint16_t pulselen = FrontLeftUpperMax; pulselen < FrontLeftUpperMin; pulselen++) {
    delay(15);
    Serial.println(pulselen);
    pwm.setPWM(FrontLeftUpper, 0, pulselen);
  }
}
uint16_t FrontLeftUpperForwardMax = 275;
void FrontLeftUpperForward()
{
  for (uint16_t pulselen = FrontLeftUpperMin; pulselen > FrontLeftUpperForwardMax; pulselen--) {
    delay(6);
    Serial.println(pulselen);
    pwm.setPWM(FrontLeftUpper, 0, pulselen);
  }
}

void FrontLeftUpperBackward() {
  for (uint16_t pulselen = FrontLeftUpperForwardMax; pulselen < FrontLeftUpperMin; pulselen++) {
    delay(6);
    Serial.println(pulselen);
    pwm.setPWM(FrontLeftUpper, 0, pulselen);
  }
}
//------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------

//FrontRightUpper Range
const uint16_t FrontRightUpperMin=323;//240 330
const uint16_t FrontRightUpperMax=324; //400 400



void FrontRightUpperTest() {

  for (uint16_t pulselen = FrontRightUpperMin; pulselen < FrontRightUpperMax; pulselen++) {
    delay(15);
    Serial.println(pulselen);
    pwm.setPWM(FrontRightUpper, 0, pulselen);
  }
  for (uint16_t pulselen = FrontRightUpperMax; pulselen > FrontRightUpperMin; pulselen--) {
    delay(15);
    Serial.println(pulselen);
    pwm.setPWM(FrontRightUpper, 0, pulselen);
  }
}
uint16_t FrontRightUpperFMax = 345;
void FrontRightUpperForward() {
  for (uint16_t pulselen = FrontRightUpperMin; pulselen < FrontRightUpperFMax; pulselen++) {
    delay(6);
    Serial.println(pulselen);
    pwm.setPWM(FrontRightUpper, 0, pulselen);
  }
}

void FrontRightUpperBackward() {
  for (uint16_t pulselen = FrontRightUpperFMax; pulselen > FrontRightUpperMin; pulselen--) {
    delay(6);
    Serial.println(pulselen);
    pwm.setPWM(FrontRightUpper, 0, pulselen);
  }
}

//-----------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------
//BackRightUpper ********************************************
const uint16_t BackRightUpperMin=295; 
const uint16_t BackRightUpperMax=296; // 280 Mid

void BackRightUpperTest(){
  for (uint16_t pulselen = BackRightUpperMin; pulselen < BackRightUpperMax; pulselen++) {
    delay(6);
    Serial.println(pulselen);
    pwm.setPWM(BackRightUpper,0,pulselen); 
  }
  for (uint16_t pulselen = BackRightUpperMax; pulselen > BackRightUpperMin; pulselen--) {
    delay(6);
    Serial.println(pulselen);
    pwm.setPWM(BackRightUpper,0,pulselen);
  }
}


void BackRightUpperBackward() {
  for (uint16_t pulselen = BackRightUpperMax; pulselen > BackRightUpperMin; pulselen--) {
    delay(6);
    Serial.println(pulselen);
    pwm.setPWM(BackRightUpper, 0, pulselen);
  }
}
void BackRightUpperForward() {
  for (uint16_t pulselen = BackRightUpperMin; pulselen < BackRightUpperMax; pulselen++) {
    delay(6);
    Serial.println(pulselen);
    pwm.setPWM(BackRightUpper, 0, pulselen);
  }
}
//------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------
const uint16_t BackLeftUpperMin=349;
const uint16_t BackLeftUpperMax=350;//435

void BackLeftUpperTest(){
  for (uint16_t pulselen = BackLeftUpperMax; pulselen > BackLeftUpperMin; pulselen--) {
    delay(6);
    Serial.println(pulselen);
    pwm.setPWM(BackLeftUpper,0,pulselen); 
  }
  for (uint16_t pulselen = BackLeftUpperMin; pulselen < BackLeftUpperMax; pulselen++) {
    delay(6);
    Serial.println(pulselen);
    pwm.setPWM(BackLeftUpper,0,pulselen);
  }
}


void BackLeftUpperBackward() {
  for (uint16_t pulselen = BackLeftUpperMin; pulselen < BackLeftUpperMax; pulselen++) {
    delay(6);
    Serial.println(pulselen);
    pwm.setPWM(BackLeftUpper, 0, pulselen);
  }
}

void BackLeftUpperForward() {
  for (uint16_t pulselen = BackLeftUpperMax; pulselen > BackLeftUpperMin; pulselen--) {
    delay(6);
    Serial.println(pulselen);
    pwm.setPWM(BackLeftUpper, 0, pulselen);
  }
}

//-----------------------------------
//------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------

//FrontRightMid
const uint16_t FrontRightMidOut = 415;
const uint16_t FrontRightMidMid = 445;
const uint16_t FrontRightMidIn = 480;

void FrontRightMidMidToOut() {
  for (uint16_t pulselen = FrontRightMidMid; pulselen > FrontRightMidOut; pulselen--) {
    delay(20);
    Serial.println(pulselen);
    pwm.setPWM(FrontRightMid, 0, pulselen);
  }
}
void FrontRightMidOutToMid() {
  for (uint16_t pulselen = FrontRightMidOut; pulselen < FrontRightMidMid; pulselen++) {
    delay(20);
    Serial.println(pulselen);
    pwm.setPWM(FrontRightMid, 0, pulselen);
  }
}
void FrontRightMidMidToIn() {
  for (uint16_t pulselen = FrontRightMidMid; pulselen < FrontRightMidIn; pulselen++) {
    delay(20);
    Serial.println(pulselen);
    pwm.setPWM(FrontRightMid, 0, pulselen);
  }
}
void FrontRightMidInToMid() {
  for (uint16_t pulselen = FrontRightMidIn; pulselen > FrontRightMidMid; pulselen--) {
    delay(20);
    Serial.println(pulselen);
    pwm.setPWM(FrontRightMid, 0, pulselen);
  }
}


//FrontLeftMid
const uint16_t FrontLeftMidMinIn = 380;
const uint16_t FrontLeftMidMidMid = 406;
const uint16_t FrontLeftMidMaxOut = 450;

void FrontLeftMidIntoMid() {
  for (uint16_t pulselen = FrontLeftMidMinIn; pulselen < FrontLeftMidMidMid; pulselen++) {
    delay(20);
    Serial.println(pulselen);
    pwm.setPWM(FrontLeftMid, 0, pulselen);
  }
}
void FrontLeftMidMidToIn() {
  for (uint16_t pulselen = FrontLeftMidMidMid; pulselen > FrontLeftMidMinIn; pulselen--) {
    delay(20);
    Serial.println(pulselen);
    pwm.setPWM(FrontLeftMid, 0, pulselen);
  }
}
void FrontLeftMidMidToOut() {
  for (uint16_t pulselen = FrontLeftMidMidMid; pulselen < FrontLeftMidMaxOut; pulselen++) {
    delay(20);
    Serial.println(pulselen);
    pwm.setPWM(FrontLeftMid, 0, pulselen);
  }
}
void FrontLeftMidOutToMid() {
  for (uint16_t pulselen = FrontLeftMidMaxOut; pulselen > FrontLeftMidMidMid; pulselen--) {
    delay(20);
    Serial.println(pulselen);
    pwm.setPWM(FrontLeftMid, 0, pulselen);
  }
}


//BackLeftMid
const uint16_t BackLeftMidMinOut = 330;
const uint16_t BackLeftMidMidMid = 358; //360
const uint16_t BackLeftMidMaxIn = 395;

void BackLeftMidMidToOut() {
  for (uint16_t pulselen = BackLeftMidMidMid; pulselen > BackLeftMidMinOut; pulselen--) {
    delay(20);
    Serial.println(pulselen);
    pwm.setPWM(BackLeftMid, 0, pulselen);
  }
}
void BackLeftMidOutToMid() {
  for (uint16_t pulselen = BackLeftMidMinOut; pulselen < BackLeftMidMidMid; pulselen++) {
    delay(20);
    Serial.println(pulselen);
    pwm.setPWM(BackLeftMid, 0, pulselen);
  }
}
void BackLeftMidMidToIn() {
  for (uint16_t pulselen = BackLeftMidMidMid; pulselen < BackLeftMidMaxIn; pulselen++) {
    delay(20);
    Serial.println(pulselen);
    pwm.setPWM(BackLeftMid, 0, pulselen);
  }
}
void BackLeftMidInToMid() {
  for (uint16_t pulselen = BackLeftMidMaxIn; pulselen > BackLeftMidMidMid; pulselen--) {
    delay(20);
    Serial.println(pulselen);
    pwm.setPWM(BackLeftMid, 0, pulselen);
  }
}


//BackRightMid
const uint16_t BackRightMidIn = 330;
const uint16_t BackRightMidMid = 358;
const uint16_t BackRightMidOut = 379;

void BackRightMidIntoMid() {
  for (uint16_t pulselen = BackRightMidIn; pulselen < BackRightMidMid; pulselen++) {
    delay(20);
    Serial.println(pulselen);
    pwm.setPWM(BackRightMid, 0, pulselen);
  }
}
void BackRightMidMidToIn() {
  for (uint16_t pulselen = BackRightMidMid; pulselen > BackRightMidIn; pulselen--) {
    delay(20);
    Serial.println(pulselen);
    pwm.setPWM(BackRightMid, 0, pulselen);
  }
}
void BackRightMidMidToOut() {
  for (uint16_t pulselen = BackRightMidMid; pulselen < BackRightMidOut; pulselen++) {
    delay(20);
    Serial.println(pulselen);
    pwm.setPWM(BackRightMid, 0, pulselen);
  }
}
void BackRightMidOutToMid() {
  for (uint16_t pulselen = BackRightMidOut; pulselen > BackRightMidMid; pulselen--) {
    delay(20);
    Serial.println(pulselen);
    pwm.setPWM(BackRightMid, 0, pulselen);
  }
}


//const uint16_t RightSideSpeed =230;
void TurnRight(){
  pwm.setPWM(FrontRightLower, 0, 240);
  pwm.setPWM(BackRightLower, 0, 255);
   
pwm.setPWM(FrontLeftLower, 0, 370);//230
pwm.setPWM(BackLeftLower, 0, 290); //255 
}


void Stand() {
  for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++) {
    delay(100);
    Serial.println(pulselen);
    delay(100);
    pwm.setPWM(BackRightUpper, 0, pulselen);
    delay(100);
    pwm.setPWM(BackLeftUpper, 0, pulselen);
  }
  for (uint16_t pulselen = SERVOMAX; pulselen > SERVOMIN; pulselen--) {
    delay(100);
    Serial.println(pulselen);
    delay(100);
    pwm.setPWM(BackRightUpper, 0, pulselen);
    delay(100);
    pwm.setPWM(BackLeftUpper, 0, pulselen);
  }
}


void WalkFrontLegs() {

  //Front legs
  for (uint16_t pulselen = FrontLegsMin; pulselen < FrontLegsMax; pulselen++) {
    delay(100);
    Serial.println(pulselen);
    delay(100);
    pwm.setPWM(FrontRightUpper, 0, pulselen);
    delay(100);
    pwm.setPWM(FrontLeftUpper, 0, pulselen);
  }
  for (uint16_t pulselen = FrontLegsMax; pulselen > FrontLegsMin; pulselen--) {
    delay(100);
    Serial.println(pulselen);
    delay(100);
    pwm.setPWM(FrontRightUpper, 0, pulselen);
    delay(100);
    pwm.setPWM(FrontLeftUpper, 0, pulselen);
  }
}


void Test() {
  for (uint16_t pulselen = 0; pulselen < 480; pulselen++) {
    delay(6);
    Serial.println(pulselen);
    pwm.setPWM(15, 0, pulselen);
  }

  for (uint16_t pulselen = 480; pulselen > 0; pulselen--) {
    delay(100);
    Serial.println(pulselen);
    pwm.setPWM(15, 0, pulselen);
  }
}


void Walk() {
  uint16_t rez;
  /* for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++) {
     delay(5);
     Serial.println(pulselen);
     delay(5);
     pwm.setPWM(BackRightUpper,0,pulselen);
     delay(5);
     pwm.setPWM(BackLeftUpper,0,pulselen);
    }
    for (uint16_t pulselen = SERVOMAX; pulselen > SERVOMIN; pulselen--) {
     delay(5);
     Serial.println(pulselen);
     delay(5);
     pwm.setPWM(BackRightUpper,0,pulselen);
     delay(5);
     pwm.setPWM(BackLeftUpper,0,pulselen);
    }*/
  /* for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++) {
     delay(10);
     pwm.setPWM(FrontLeftUpper, 0, pulselen);
     pwm.setPWM(FrontRightUpper, 0, pulselen);
     pwm.setPWM(BackRightUpper, 0, pulselen);
     pwm.setPWM(BackLeftUpper, 0, pulselen);
    delay(10);
     pwm.setPWM(FrontRightLower, 0, pulselen);
     pwm.setPWM(FrontLeftLower, 0, pulselen);
     pwm.setPWM(BackRightLower, 0, pulselen);
     pwm.setPWM(BackLeftLower, 0, pulselen);
    delay(10);


    pwm.setPWM(FrontRightMid, 0, pulselen);
     pwm.setPWM(FrontLeftMid, 0, pulselen);
     pwm.setPWM(BackRightMid, 0, pulselen);
     pwm.setPWM(BackLeftMid, 0, pulselen);
     delay(10);
     Serial.println(pulselen);
    }*/
  /*for (uint16_t pulselen = SERVOMAX; pulselen > SERVOMIN; pulselen--) {
      delay(10);
      pwm.setPWM(FrontLeftUpper, 470, pulselen);
      pwm.setPWM(FrontRightUpper, 470, pulselen);
      pwm.setPWM(BackRightUpper, 470, pulselen);
      pwm.setPWM(BackLeftUpper, 470, pulselen);
     delay(10);
      pwm.setPWM(FrontRightLower, 470, pulselen);
      pwm.setPWM(FrontLeftLower, 470, pulselen);
      pwm.setPWM(BackRightLower, 470, pulselen);
      pwm.setPWM(BackLeftLower, 470, pulselen);
     delay(10);
      pwm.setPWM(FrontRightMid, 470, pulselen);
      pwm.setPWM(FrontLeftMid, 470, pulselen);
      pwm.setPWM(BackRightMid, 470, pulselen);
      pwm.setPWM(BackLeftMid, 470, pulselen);
      delay(10);
      Serial.println(pulselen);
    }*/
}
void DodgeLeft() {
  FrontLowerRightUp();
  FrontRightMidMidToOut();
  FrontLowerRightSit();
  FrontLowerLeftSit();
  FrontLeftMidMidToIn();
  FrontLowerLeftUp();
  FrontRightMidOutToMid();
  FrontLeftMidIntoMid();
}

void loop() {
  //LIGHT_SENSOR---------------------------------
 light = analogRead(A0);
 unsigned int AnalogValue;
 AnalogValue = analogRead(A1);
 Serial.println(light); // print current light value
    if(light >500) { // If it is bright...
        Serial.println("It is quite light!");
        digitalWrite(13,LOW); //turn left LED off
        digitalWrite(12,LOW); // turn right LED off
    }
    else { // If it's dark...
        Serial.println("It is pretty dark!");
        digitalWrite(13,HIGH); // Turn left LED on
        digitalWrite(12,HIGH); // Turn right LED on
    }
    delay(1000);
//LIGHT_SENSOR_END---------------------------------
//SERVO-------------------------------
  (Serial.available());
  data = Serial.read();
  switch (data) {
    case'D': FrontLower(); break;
    //backlow Right
    case'E': BackLower(); break;

    case'F': FrontLeftUpperTest(); break;

    case'G': FrontRightUpperTest(); break;

    case'H': BackRightUpperTest(); break;

    case'I': BackLeftUpperTest(); break;
    //backlow Left
    case'J': BackLowerLeft(); break;

    case'K': FrontLowerSit(); break;
    case'N': FrontLowerUp(); break;

    case 'L': BackLowerSit(); break;
    case 'O': BackLowerUp(); break;
    //P
    case 'M': FrontRightMidMidToOut(); break;
    case 'Q': FrontRightMidOutToMid(); break;
    case 'R': FrontRightMidMidToIn(); break;
    case 'S': FrontRightMidInToMid(); break;

    case 'T': BackRightMidIntoMid(); break;
    case 'U': BackRightMidMidToIn(); break;
    case 'V': BackRightMidMidToOut(); break;
    case 'W': BackRightMidOutToMid(); break;

    case 'X': BackLeftMidMidToOut(); break;
    case 'Y': BackLeftMidOutToMid(); break;
    case 'Z': BackLeftMidMidToIn(); break;
    case 'a': BackLeftMidInToMid(); break;

    case 'b': FrontLeftMidIntoMid(); break;
    case 'c': FrontLeftMidMidToIn(); break;
    case 'd': FrontLeftMidMidToOut(); break;
    case 'e': FrontLeftMidOutToMid(); break;

    case 'f': FrontLowerLeftUp(); break;
    case 'g': FrontLowerLeftSit(); break;

    case 'h': FrontLowerRightSit(); break;
    case 'i': FrontLowerRightUp(); break;

    case 'j': BackLowerLeftSit(); break;
    case 'k': BackLowerLeftUp(); break;

    case 'l': BackLowerRightSit(); break;
    case 'm': BackLowerRightUp(); break;

    case 'n': DodgeLeft(); break;

    case'o': FrontLowerLeftForwardUp(); break;
    case'p': FrontLowerLeftForwardDown(); break;

    case 'q': FrontLeftUpperForward(); break;
    case 'r': FrontLeftUpperBackward(); break;

    case 's': FrontRightUpperForward(); break;
    case 't': FrontRightUpperBackward(); break;

    case 'u': FrontLowerRightForwardUp(); break;
    case 'v': FrontLowerRightForwardDown(); break;

    case 'w': BackRightUpperBackward(); break;
    case 'x': BackRightUpperForward(); break;

    case 'y': BackLowerRightForwardStand(); break; //opp
    case 'z': BackLowerRightForwardSit(); break; //opp

    case 'A': BackLeftUpperBackward(); break;
    case 'B': BackLeftUpperForward(); break;

    case 'C': BackLowerLeftForwardStand(); break;
    case '!': BackLowerLeftForwardSit(); break;

    case '@':WheelsForward();break;
    case '#':WheelStop();break;
    case '$':WheelsBack();break;
    case '%':TurnRight();break;
    case '^':RotationLeftTest();break;
    case '&':RotationRightTest();break;

      //A B C
  }
//SERVO END------------------------------------

//Voice-----------------------------------------
while(Serial.available()){
  com = Serial.read();

  if(group == 1)//start group 1
  { 
    if(com == 0x11)//forward
    {
      WheelsForward();
      break;
    }

    if(com == 0x12)//Backwards
    {
      WheelsBack();
      break;
    }

    if(com == 0x13)//right
    {
      break;
    }

    if(com == 0x14)//left
    {
      break;
    }

    if(com == 0x15)//stop
    {
      WheelStop();
      break;
    }
}//End of group 1

//Start group 2
if(group == 2)
{
  if(com == 0x11)//lights on
  {
    Serial.write(0xAA);
    Serial.write(0x00);//waiting
    delay(100);
    Serial.write(0xAA);
    Serial.write(0x22);//group 2
    break;
  }

  if(com == 0x12)//down
  {
    Serial.write(0xAA);
    Serial.write(0x00);
    delay(100);
    Serial.write(0xAA);
    Serial.write(0x22);
    break;
  }

  if(com == 0x13)//up
  { 
    Serial.write(0xAA);
    Serial.write(0x00);
    delay(100);
    Serial.write(0xAA);
    Serial.write(0x22);
    break;
  }

  if(com == 0x14)//bark
  {
    Serial.write(0xAA);
    Serial.write(0x00);
    delay(100);
    Serial.write(0xAA);
    Serial.write(0x22);
    break;
  }

  if(com == 0x15)//lights off
  {
    Serial.write(0xAA);
    Serial.write(0x00);
    delay(100);
    Serial.write(0xAA);
    Serial.write(0x22);
    break;
  }
 }
}
//Voice_________________________________________________

//Obstical----------------------------------------------
 digitalWrite(trigPin, LOW);
 delayMicroseconds(2);
 digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
 //Obstical_END______________________________________________


 //--------------------------------------------------

 humidity=HT.readHumidity();
tempC=HT.readTemperature();
read_value = (analogRead(sensorGas)); //read input value
read_value = read_value - 50;
if(read_value<0){read_value=0;}
lcd.print ("Detector is ON");
lcd.setCursor(0,1);
lcd.print("Smoke Level: ");
lcd.print(read_value);
delay(3000);
lcd.clear();
lcd.setCursor(0,0);
lcd.print(" Temperature: ");
lcd.setCursor(0,1);
lcd.print(tempC);
lcd.print(" C ");
delay(3000);
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Scanning!!");
delay(9000);

if(read_value>set) //check if the Smoke variable is High
{
SendMessege();
Serial.print("Smoke detect alarm");
lcd.clear();
lcd.setCursor(0, 0);
lcd.print("Alert!Smoke Level Exceed");
lcd.setCursor(0, 1);
lcd.print("SMS SENT!!!");
alarm();
delay(1000);
}
else
{
Serial.print("Smoke Level Low");
lcd.clear();
lcd.setCursor(0, 0);
lcd.print("Normal!!!");
lcd.clear();
digitalWrite(buzzer, LOW); //Turn Buzzer off. 
delay(4000);
}
lcd.clear();

if(tempC>40.00)
{
SendMessege1();
alarm1();
lcd.setCursor(0,0);
lcd.print("High Temperature detect");
lcd.setCursor(0,1);
lcd.print("SMS SENT!!!");
delay (10000);
}
else
{
  Serial.print("Temperature Level Low");
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Temp is Normal!");  
  delay(1000);
  lcd.clear();
  delay(1000);
}
lcd.clear();
}
void SendMessege()
{
Serial.println("I am in send SMOKE");
mySerial.println("AT+CMGF=1"); //Sets the GSM Module in Text Mode
delay(200); // Delay of 1000 milli seconds or 1 second
mySerial.println("AT+CMGS=\"" + number + "\"\r"); // Replace x with mobile number
delay(200);
String SMS = "Excess Gas Detected. Open Windows";
mySerial.println(SMS);
delay(100);
mySerial.println((char)26);// ASCII code of CTRL+Z
delay(200);
Serial.println("send");
}
void alarm()
{
tone(buzzer, 160); // Send 1KHz sound signal...
delay(1000);        // ...for 1 sec
tone(buzzer, 100);
delay(1000);
tone(buzzer, 160);
delay(1000);
tone(buzzer, 100);
delay(1000);// ...for 1sec
tone(buzzer, 160); // Send 1KHz sound signal...
delay(1000);        // ...for 1 sec
tone(buzzer, 100);
delay(1000);
tone(buzzer, 160);
delay(1000);
tone(buzzer, 100);
delay(1000);// ...for 1sec
tone(buzzer, 160); // Send 1KHz sound signal...
delay(1000);        // ...for 1 sec
tone(buzzer, 100);
delay(1000);
tone(buzzer, 160);
delay(1000);
tone(buzzer, 100);
delay(1000);// ...for 1sec
noTone(buzzer);// Stop sound...
delay(1000);    
}
void SendMessege1()
{
Serial.println("I am in send");
mySerial.println("AT+CMGF=1"); //Sets the GSM Module in Text Mode
delay(200); // Delay of 1000 milli seconds or 1 second
mySerial.println("AT+CMGS=\"" + number + "\"\r"); // Replace x with mobile number
delay(200);
String SMS = "Temp is high please check!!";
mySerial.println(SMS);
delay(100);
mySerial.println((char)26);// ASCII code of CTRL+Z
delay(200);
Serial.println("send");
}
void alarm1()
{
tone(buzzer, 200); // Send 1KHz sound signal...
delay(1000);        // ...for 1 sec
tone(buzzer, 100);
delay(1000);
tone(buzzer, 200);
delay(1000);
tone(buzzer, 100);
delay(1000);// ...for 1sec
tone(buzzer, 200); // Send 1KHz sound signal...
delay(1000);        // ...for 1 sec
tone(buzzer, 100);
delay(1000);
tone(buzzer, 200);
delay(1000);
tone(buzzer, 100);
delay(1000);// ...for 1sec
tone(buzzer, 200); // Send 1KHz sound signal...
delay(1000);        // ...for 1 sec
tone(buzzer, 100);
delay(1000);
tone(buzzer, 200);
delay(1000);
tone(buzzer, 100);
delay(1000);// ...for 1sec
noTone(buzzer);     // Stop sound...
delay(1000);    
//_______________________________________________________________________
}
