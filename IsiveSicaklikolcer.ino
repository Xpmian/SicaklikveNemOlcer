#define BLYNK_TEMPLATE_ID "TMPL6XtTUjLQR"
#define BLYNK_TEMPLATE_NAME "Dht22 Sensor"
#define BLYNK_AUTH_TOKEN "AX_3BU-TLJrWZPR2C9HG5XfvWlNZR7GW"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "DHT.h"

#define DHTPIN 2    
#define DHTTYPE DHT22   
#define BLYNK_PRINT Serial

#define BUZZER_PIN 14  

char auth[] = BLYNK_AUTH_TOKEN; 
char ssid[] = "Sami's Galaxy A50"; 
char pass[] = "birdensekizekadar"; 

BlynkTimer timer;
DHT dht(DHTPIN, DHTTYPE);

float nemEsik = 60.0;
float sicaklikEsik = 30.0;

void sendData()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) 
  {
    Serial.println("DHT Sensor okuma hatasi!");
    return;
  }

  Blynk.virtualWrite(V5, h); 
  Blynk.virtualWrite(V6, t); 

  if (h > nemEsik || t > sicaklikEsik) 
  {
    digitalWrite(BUZZER_PIN, HIGH); 
    Blynk.virtualWrite(V3, 255);
  } 
  else 
  {
    digitalWrite(BUZZER_PIN, LOW); 
    Blynk.virtualWrite(V3, 0); 
  }

  Serial.print("Nem: ");
  Serial.print(h);
  Serial.print(" %  Sıcaklık: ");
  Serial.print(t);
  Serial.println(" °C");
}

void setup()
{
  Serial.begin(9600);
  dht.begin();
  Blynk.begin(auth, ssid, pass);
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW); 

  timer.setInterval(1000L, sendData);
}

void loop()
{
  Blynk.run();
  timer.run();
}
