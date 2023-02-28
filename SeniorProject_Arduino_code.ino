#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
#define SERVOMIN 150 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX 600 // this is the 'maximum' pulse length count (out of 4096)1,0
int currentAngle[4];
// Array to store the current angle of each servo
 bool angleUpdated = false; 
// Flag to keep track of whether a new angle has been setvoid setup() 
{  
 Serial.begin(9600);  pwm.begin();  pwm.setPWMFreq(60);  
// Analog servos run at ~60 Hz updates  for (int i = 0; i < 4; i++) 
{    
  currentAngle[i] = 90; // Initialize all servo angles to 90 degrees 
}
}
void loop() 
{  
if (Serial.available() > 0) 
{   
// Read the incoming motor number    
int motorNumber = Serial.parseInt();  
  // Read the incoming angle degree   
int servoAngle = Serial.parseInt();    
// Map the degree value to a PWM value   
int pwmValue = map(servoAngle, 0, 180, SERVOMIN, SERVOMAX);    
// Set the PWM value for the motor    
pwm.setPWM(motorNumber-1, 0, pwmValue);    
// Update the current angle of the servo   
currentAngle[motorNumber-1] = servoAngle;   
// Set the angle updated flag to true   
angleUpdated = true;   
// Add a delay to slow down the servo movement   
delay(500); // delay time in milliseconds  
}
  // Print out the current angle of each servo in the serial monitor
  // only if a new angle has been set 
if (angleUpdated) 
{    
for (int i = 0; i < 4; i++) 
{     
Serial.print("Servo ");      
Serial.print(i+1);      
Serial.print(" angle: ");     
Serial.println(currentAngle[i]);   
}    
// Reset the angle updated flag   
angleUpdated = false; 
}
}
