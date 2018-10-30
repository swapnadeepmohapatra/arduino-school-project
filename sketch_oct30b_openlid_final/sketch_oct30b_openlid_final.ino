#include <Servo.h>

Servo servo;


// Pin INIT

int trigPin = 8;
int echoPin = 7;
int servoPin = 6;

int greenLed = 11;
int yellowLed = 12;
int redLed = 13;

const int trigPinBin = 10;
const int echoPinBin = 9;

long durationBin ;
int distanceBin ;

int led= 10;
long duration, dist, average;   
long aver[3];  


// Pin Setup


void setup() {       
    servo.attach(servoPin);  
    pinMode(trigPin, OUTPUT);  
    pinMode(echoPin, INPUT);  

    pinMode(trigPinBin, OUTPUT);
    pinMode(echoPinBin, INPUT); 
    Serial.begin(19200);
    
    servo.write(0);        
    delay(100);
    servo.detach(); 
} 


// Measure the dist of the person

void measure() {  
  digitalWrite(10,HIGH);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(15);
  digitalWrite(trigPin, LOW);
  pinMode(echoPin, INPUT);
duration = pulseIn(echoPin, HIGH);
dist = (duration/2) / 29.1; 
}

void loop() { 
  for (int i=0;i<=2;i++) {  
    measure();               
   aver[i]=dist;            
    delay(10);            
  }
 dist=(aver[0]+aver[1]+aver[2])/3;    



// Amount of Bin

digitalWrite(trigPinBin, LOW);
delayMicroseconds(2);
digitalWrite(trigPinBin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPinBin, LOW);
durationBin = pulseIn(echoPinBin, HIGH);
distanceBin = durationBin*0.034/2;
Serial.print("Distance: ");
Serial.println(distanceBin);



// Error

if(distanceBin > 2000){
  Serial.println("Error");
}


// Displays Level of bin in LED

if(distanceBin <= 25 || distanceBin >= 16){
  digitalWrite(greenLed, LOW);
  digitalWrite(yellowLed, HIGH);
  digitalWrite(redLed, HIGH);
 
}else if(distanceBin <= 15 || distanceBin >= 8){
  digitalWrite(greenLed, HIGH);
  digitalWrite(yellowLed, LOW);
  digitalWrite(redLed, HIGH);
  
}else if(distanceBin <= 7 || distanceBin >= 0){
  digitalWrite(greenLed, HIGH);
  digitalWrite(yellowLed, HIGH);
  digitalWrite(redLed, LOW);
  
}else{
  digitalWrite(LED1, HIGH);
  delay(200);                
  digitalWrite(LED2, HIGH);  
  delay(200);                   
  digitalWrite(LED3, HIGH); 
  delay(200);                
  digitalWrite(LED1, LOW);    
  delay(300);              
  digitalWrite(LED2, LOW);  
  delay(300);               
  digitalWrite(LED3, LOW);     
  delay(300);
}



// Open the lid


if ( dist<50 && (distanceBin > 5 || distanceBin > 2000)) {
 servo.attach(servoPin);
  delay(1);
 servo.write(0);  
 delay(3000);       
 servo.write(180);    
 delay(1000);
 servo.detach();      
}
}
