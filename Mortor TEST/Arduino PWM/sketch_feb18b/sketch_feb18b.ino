#include <Adafruit_PWMServoDriver.h>//PWM driver library
#include <Wire.h>//I2C 

// Depending on your servo make, the pulse width min and max may vary, you 
// want these to be as small/large as possible without hitting the hard stop
// for max range. You'll have to tweak them as necessary to match the servos you
// have!
#define SERVOMIN  150 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  650 // This is the 'maximum' pulse length count (out of 4096)
#define USMIN  600 // This is the rounded 'minimum' microsecond length based on the minimum pulse of 150
#define USMAX  2400 // This is the rounded 'maximum' microsecond length based on the maximum pulse of 600
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();//PWM Object

int mortorA = 0;
int mortorB = 4;
int mortorC = 8;

int mortorD = 1;
int mortorE = 5;
int mortorF = 9;

int mortorG = 2;
int mortorH = 6;
int mortorI = 10;

int mortorJ = 3;
int mortorK = 7;
int mortorL = 11;

void setup() {
  // put your setup code here, to run once:
  pwm.begin();
  pwm.setPWMFreq(SERVO_FREQ);
  delay(10);
}

void loop() {
  // put your main code here, to run repeatedly:

pwm.setPWM(mortorA, 0, 650);
//pwm.writeMicroseconds(servonum, microsec);
}
