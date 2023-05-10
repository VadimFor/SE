#include <Wire.h>
#include "MAX30105.h"
#include <ArduinoHttpClient.h>
#include "heartRate.h"
#include <Adafruit_SSD1306.h>
#include <string> 
#include <ArduinoBLE.h>
#include <sstream>
#include <stdlib.h>

//AUXILIARES
#include "aux_wifi.h"
#include "aux_mqtt.h"

// Definimos el pin al que está conectado el sensor
#define SENSOR_PIN A0 

void setup() { 
  
  delay(3000); //delay para que inicio el draw
  Serial.begin(9600);
  Serial.println("Programa iniciado.");

  conectarWifi(); //aux_wifi.h

  suscribeMQTT((char *)"/v1.6/devices/invernadero/luminico/lv");
 
}
  
void loop() {
  // Leemos el valor del sensor
  int sensorValue = analogRead(SENSOR_PIN);
  float lux = sensorValue * (5.0 / 1023.0); 

  // Imprimimos el valor en el monitor serial
  Serial.print("Intensidad lumínica: ");
  Serial.print(lux);
  Serial.println(" lux");

  char luxStr[8];
  sprintf(luxStr, "%f", lux);
  
  if (client.publish((char *)"/v1.6/devices/invernadero/luminico", luxStr)) {
     Serial.println((std::string(luxStr) + " publicado correctamente.").c_str()) ;
  }
  
  delay(1000);
}








/*  SENSOR SUELO

const int soilPin = A0;
int soilValue = 0;     
int soilMoisture = 0; 

void setup() {
  Serial.begin(9600);  
}

void loop() {
  soilValue = analogRead(soilPin);        
  soilMoisture = map(soilValue, 0, 1023, 0, 100);  
  
  Serial.print("Valor: ");
  Serial.print(soilValue);
  Serial.print("\tHumedad: ");
  Serial.print(soilMoisture);
  Serial.println("%");
  
  delay(1000); 
}


*/



/*  SENSOR TEMP Y HUMEDAD DHT22

#include "DHT.h"

#define DHTPIN 2          // El pin GPIO al que se conecta el sensor DHT22
#define DHTTYPE DHT22     // Tipo de sensor DHT22

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  delay(2000);
  
  float temperature = dht.readTemperature();     // Leer temperatura en grados Celsius
  float humidity = dht.readHumidity();           // Leer humedad relativa en porcentaje
  
  Serial.print("Temperatura: ");
  Serial.print(temperature);
  Serial.print(" °C\tHumedad: ");
  Serial.print(humidity);
  Serial.println(" %");
}


*/
