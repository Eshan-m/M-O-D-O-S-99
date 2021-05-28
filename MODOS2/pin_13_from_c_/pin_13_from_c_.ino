#include<Servo.h>
int data; 
char str[] = "Hello";
void setup() {  
    
    Serial.begin(9600);  
    pinMode(13, OUTPUT);  
    pinMode (9, OUTPUT);
    
}  
void loop() {  
    (Serial.available());  
     data = Serial.read();  
            
    switch (data)
    {
      case 'A':
        digitalWrite(13, HIGH);  
        break;
        case 'B':
        digitalWrite(13, LOW);  
        break;
        case 'C':
        Serial.print("he") ;
        break;
        case 'D':
        Serial.print(str);  
        break;
    }
}  
