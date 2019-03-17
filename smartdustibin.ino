/*
********************************************
14CORE ULTRASONIC DISTANCE SENSOR CODE TEST 
********************************************
*/
#define TRIGGER D2
#define ECHO    D1

// NodeMCU Pin D1 > TRIGGER | Pin D2 > ECHO

#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "b7fef5946dd043038efe3cbb9209b8f1";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "SnapCracklePop";
char pass[] = "sunny123";

//LED FOR INDICATION
int full = D3;  //bin is full
int qtofull= D4;//3/4 bin is full
int half = D5;  //1/2 bin is full
int quarter = D6;// 1/4 bin is full
int empty = D0; // total bin is empty
void setup() {
  // 9600 represents bit rate i.e. 9600 bits transmitted in 1 second
  Serial.begin (9600);
  //verifying authorization code, ssid and password
  Blynk.begin(auth, ssid, pass);
  //declaring trig pin in sensor as output and echo pin as input
  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);
//enabling the pins in microcontroller as digital output
  pinMode(empty,OUTPUT);
  pinMode(quarter,OUTPUT);
  pinMode(half,OUTPUT);
  pinMode(qtofull,OUTPUT);
  pinMode(full,OUTPUT);
}

void loop() {
  
  long duration, distance;
  //creating a square pulse with a duration of 2 microseconds and 10 microseconds
  digitalWrite(TRIGGER, LOW);  
  delayMicroseconds(2); 
  
  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10); 
  
  digitalWrite(TRIGGER, LOW);
  duration = pulseIn(ECHO, HIGH);
  
 // distance = (duration/2) / 29.1; // (this is one way of representing the equation.
 //for understanding
 /* distance = duration * (speed of sound / 10 micro seconds)/2;
  *  distance = duration*(343m/s / 10 *10^-6*10^3 seconds)/2  ----> distance = duration *(343 m/s /10^-2 *2) [: 1 mt=100cms]
  *  distance = duration *((343/100*2*10^2) -------> distance = [duration*(343/20000)] cms 
  */
  distance = duration*(343/20000):  // another way of representation
  Serial.print(distance);
  Serial.println("Centimeter:");

  Blynk.virtualWrite(V1, 255);//empty led
  Blynk.virtualWrite(V0, distance);//guage
  Blynk.virtualWrite(V6, distance);//level
  digitalWrite(empty,HIGH); // empty led is on
  
 if (distance <= 16) {
    Blynk.virtualWrite(V2, 255);//1/4 led is on
    Blynk.virtualWrite(V1, 0);
    Blynk.virtualWrite(V3, 0);
    Blynk.virtualWrite(V4, 0);
    Blynk.virtualWrite(V5, 0);

    digitalWrite(quarter,HIGH);
    digitalWrite(half,LOW);
    digitalWrite(qtofull,LOW);
    digitalWrite(full,LOW);
    digitalWrite(empty,LOW);
}
  else {
    Blynk.virtualWrite(V2, 0);//1/4 led is off
    Blynk.virtualWrite(V3, 0);
    Blynk.virtualWrite(V4, 0);
    Blynk.virtualWrite(V5, 0);

    digitalWrite(quarter,LOW);
    digitalWrite(half,LOW);
    digitalWrite(qtofull,LOW);
    digitalWrite(full,LOW);
  }

   if (distance <= 10) {
    Blynk.virtualWrite(V3, 255);//1/2 led is on
    Blynk.virtualWrite(V1, 0);
    Blynk.virtualWrite(V2, 0);
    Blynk.virtualWrite(V4, 0);
    Blynk.virtualWrite(V5, 0);

    digitalWrite(half,HIGH);
    digitalWrite(quarter,LOW);
    digitalWrite(qtofull,LOW);
    digitalWrite(full,LOW);
    digitalWrite(empty,LOW);
}
  else {
    Blynk.virtualWrite(V3, 0);//1/2 led is off
    Blynk.virtualWrite(V2, 0);
    Blynk.virtualWrite(V4, 0);
    Blynk.virtualWrite(V5, 0);

    digitalWrite(quarter,LOW);
    digitalWrite(half,LOW);
    digitalWrite(qtofull,LOW);
    digitalWrite(full,LOW);
  }

   if (distance <= 9) {
    Blynk.virtualWrite(V4, 255);//3/4 led is on
    Blynk.virtualWrite(V1, 0);
    Blynk.virtualWrite(V2, 0);
    Blynk.virtualWrite(V3, 0);
    Blynk.virtualWrite(V5, 0);

    digitalWrite(qtofull,HIGH);
    digitalWrite(quarter,LOW);
    digitalWrite(half,LOW);
    digitalWrite(full,LOW);
    digitalWrite(empty,LOW);
}
  else {
    Blynk.virtualWrite(V4, 0);//3/4 led is off
    Blynk.virtualWrite(V2, 0);
    Blynk.virtualWrite(V3, 0);
    Blynk.virtualWrite(V5, 0);

    digitalWrite(quarter,LOW);
    digitalWrite(half,LOW);
    digitalWrite(qtofull,LOW);
    digitalWrite(full,LOW);
  }

   if (distance <= 6) {
    Blynk.virtualWrite(V5, 255);//full led is on
    Blynk.virtualWrite(V1, 0);
    Blynk.virtualWrite(V2, 0);
    Blynk.virtualWrite(V3, 0);
    Blynk.virtualWrite(V4, 0);

    digitalWrite(full,HIGH);
    digitalWrite(quarter,LOW);
    digitalWrite(half,LOW);
    digitalWrite(qtofull,LOW);
    digitalWrite(empty,LOW);
}
  else {
    Blynk.virtualWrite(V5, 0);//full led is off
    Blynk.virtualWrite(V2, 0);
    Blynk.virtualWrite(V3, 0);
    Blynk.virtualWrite(V4, 0);

    digitalWrite(quarter,LOW);
    digitalWrite(half,LOW);
    digitalWrite(qtofull,LOW);
    digitalWrite(full,LOW);
  }

  delay(200);
  Blynk.run();
}
