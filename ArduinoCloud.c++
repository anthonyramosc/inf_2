#include "thingProperties.h"
#include <DHT.h>


#define DHTPIN 22   
#define BUZZERPIN 26  
#define FANPIN 25   
#define LIGHTPIN 35  
#define LEDPIN 5    


DHT dht(DHTPIN, DHT11);


float temperature;
float humidity;
int lightLevel;
bool fanState;
bool buzzerState;
bool ledState;

void setup() {
  Serial.begin(115200);
  dht.begin();
  
  
  pinMode(BUZZERPIN, OUTPUT);
  pinMode(FANPIN, OUTPUT);
  pinMode(LEDPIN, OUTPUT);
  
  initProperties();
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
}

void loop() {
  ArduinoCloud.update();


  temperature = dht.readTemperature();
  humidity = dht.readHumidity();
  

  lightLevel = analogRead(LIGHTPIN);
  

  if (temperature > 30) {
   
    fanState = true;
  } else {
   
    fanState = false;
  }
  
  if (lightLevel > 500) {

    ledState = true;
    buzzerState = true;
  } else {

    ledState = false;
    buzzerState = false;
  }
  

  digitalWrite(FANPIN, fanState);
  digitalWrite(BUZZERPIN, buzzerState);
  digitalWrite(LEDPIN, ledState);
  
  delay(1000); 
}

void onLedSwitchChange() {

}