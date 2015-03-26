// Sweep
// by BARRAGAN <http://barraganstudio.com> 
// This example code is in the public domain.


#include <Servo.h> 
 
Servo leftWheel;
Servo rightWheel;
int pingPin = 7;
 
int leftPos = 91;    //  91 is stop; ~80 is full reverse;   98 is full forward
int rightPos = 92;   //  92 is stop; ~100 is full reverse;  80 is full forward
int leftIR = A1, leftValue = 0;
int rightIR = A0, rightValue = 0;

//int irSensor = 2;
//int irValue = 0;

 
void setup() 
{ 
  leftWheel.attach(9);  // attaches the servo on pin 9 to the servo object 
  rightWheel.attach(10);
  Serial.begin(9600);
} 
 
 
void loop() 
{            
  
    while(true) {
      
      int thresh = 42;
      
      //delay(2);
      
      leftValue = analogRead(leftIR);
      rightValue = analogRead(rightIR);
      
      if(leftValue < thresh && rightValue < thresh) {
        leftPos = 90;
        rightPos = 93;
        
      }
      else if(leftValue < thresh) {
        leftPos = 91;
        rightPos = 96;
      }      
      else if(rightValue < thresh) {
        leftPos = 84;
        rightPos = 92;
      }
      else if(rightValue >50 && leftValue > 50) {
        leftPos = 91;
        rightPos = 92;
      }
      else {
        leftPos = 88;
        rightPos = 95;
        //delay(10);
      }
      
      if(distanceToObject() < 5) {
        leftPos = 91;
        rightPos = 92;
      }
 
 
      
      leftWheel.write(leftPos);
      rightWheel.write(rightPos);
      Serial.print(" LeftIR: ");
      Serial.print(leftValue);
      Serial.print(" RightIR: ");
      Serial.print(rightValue);

      Serial.print(" L_Servo to: ");
      Serial.print(leftPos);
      Serial.print(" R_Servo to: ");
      Serial.print(rightPos);
      Serial.print("\n");
  }
 
} 

long distanceToObject() {
  long microseconds, inches;
  
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);
  
  
  pinMode(pingPin, INPUT);
  microseconds = pulseIn(pingPin, HIGH);
  
  inches = microseconds / 74 / 2;
  Serial.print(" Distance: ");
  Serial.print(inches);
  return inches;
}
