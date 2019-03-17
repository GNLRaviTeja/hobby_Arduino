#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

unsigned int moisture = D1;
unsigned int thermocouple = A0;

unsigned int value= 0;
float temperature = 0;

char auth[] = "c61f7ce51d864ed386cb02c2d83af3aa";
char ssid[] = "Just books";
char pass[] = "VMJYUFCM";

void setup(){
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  pinMode(moisture, INPUT);
}

void loop(){
  temperature = analogRead(thermocouple);
  temperature = (((temperature*4.88)-0.0027)/20.0);
  //temperature = (((temperature*4.88)-0.0027)/10.0); // correct data
  Serial.println(temperature);
  Blynk.virtualWrite(V1,temperature);
  delay(1000);
  value = digitalRead(moisture);
  if(value == HIGH){
    Blynk.virtualWrite(V0,255);
  }
  if(value == LOW){
    Blynk.virtualWrite(V0,0);
  }
  Blynk.run();
}
