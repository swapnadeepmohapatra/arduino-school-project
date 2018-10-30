#include <Servo.h>   //servo library
Servo servo;     
int trigPin = 12;    
int echoPin = 11;   
int servoPin = 7;

const int trigPinBin = 5;
const int echoPinBin = 6;

long durationBin ;
int distanceBin ;

int led= 10;
long duration, dist, average;   
long aver[3];   //array for average


void setup() {       
    Serial.begin(9600);
    servo.attach(servoPin);  
    pinMode(trigPin, OUTPUT);  
    pinMode(echoPin, INPUT);  

pinMode(trigPinBin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPinBin, INPUT); // Sets the echoPin as an Input
Serial.begin(19200);
    
    servo.write(0);         //close cap on power on
    delay(100);
    servo.detach(); 
} 

void measure() {  
 digitalWrite(10,HIGH);
digitalWrite(trigPin, LOW);
delayMicroseconds(5);
digitalWrite(trigPin, HIGH);
delayMicroseconds(15);
digitalWrite(trigPin, LOW);
pinMode(echoPin, INPUT);
duration = pulseIn(echoPin, HIGH);
dist = (duration/2) / 29.1;    //obtain distance
}
void loop() { 
  for (int i=0;i<=2;i++) {   //average distance
    measure();               
   aver[i]=dist;            
    delay(10);              //delay between measurements
  }
 dist=(aver[0]+aver[1]+aver[2])/3;    

digitalWrite(trigPinBin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPinBin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPinBin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
durationBin = pulseIn(echoPinBin, HIGH);
// Calculating the distance
distanceBin = durationBin*0.034/2;
// Prints the distance on the Serial Monitor
Serial.print("Distance: ");
Serial.println(distanceBin);

if(distanceBin > 2000){
  Serial.println("Error");
}

if ( dist<50 && (distanceBin > 5 || distanceBin > 2000)) {
//Change distance as per your need
 servo.attach(servoPin);
  delay(1);
 servo.write(0);  
 delay(3000);       
 servo.write(180);    
 delay(1000);
 servo.detach();      
}
//Serial.print(dist);
}
