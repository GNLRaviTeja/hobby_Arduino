#include "UbidotsESPMQTT.h"
#include "DHT.h"

#define pir D0

#define relay D2

#define zero D3
#define one D4
#define two D5
#define three D6
#define four D7
#define five D8

#define DHTPIN D1
/****************************************
 * Define Constants
 ****************************************/
#define TOKEN "A1E-f249b3c05f6a4126603623a52c9478f56c50" // Your Ubidots TOKEN
#define WIFINAME "Nokia 8" //Your SSID
#define WIFIPASS "raviteja" // Your Wifi Pass

Ubidots client(TOKEN);

#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
/****************************************
 * Auxiliar Functions
 ****************************************/

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i=0;i<length;i++) {
    Serial.print((char)payload[i]);
  }
  if ((char)payload[0]=='1'){
    digitalWrite(16, HIGH);
  }
  else{
    digitalWrite(16, LOW);
  }
  Serial.println();
}

/****************************************
 * Main Functions
 ****************************************/

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  client.setDebug(true); // Pass a true or false bool value to activate debug messages
  client.wifiConnection(WIFINAME, WIFIPASS);
  client.begin(callback);
  pinMode(16, OUTPUT);
  client.ubidotsSubscribe("Home Automation","Temperature"); //Insert the dataSource and Variable's Labels
  client.ubidotsSubscribe("Home Automation","Humidity"); 
  client.ubidotsSubscribe("Home Automation","Motion Trigger");
  dht.begin();
  pinMode(pir, INPUT);
  pinMode(relay, OUTPUT);

  pinMode(zero, OUTPUT);
  pinMode(one, OUTPUT);
  pinMode(two, OUTPUT);
  pinMode(three, OUTPUT);
  pinMode(four, OUTPUT);
  pinMode(five, OUTPUT);
  }

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C ");
  // put your main code here, to run repeatedly:
  if(!client.connected()){
      client.reconnect();
      client.ubidotsSubscribe("Home Automation","Temperature"); //Insert the dataSource and Variable's Labels
      client.ubidotsSubscribe("Home Automation","Humidity"); 
      client.ubidotsSubscribe("Home Automation","Mtion Trigger"); 
      }
  client.add("Temperature", t);
  client.add("Humidity", h);
  client.add("Motion Trigger", 1);
  client.ubidotsPublish("Home Automation");
  client.loop();
  }
