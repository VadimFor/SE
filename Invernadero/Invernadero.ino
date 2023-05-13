#include <Wire.h>
#include "MAX30105.h"
#include <ArduinoHttpClient.h>
#include "heartRate.h"
#include <Adafruit_SSD1306.h>
#include <string> 
#include <ArduinoBLE.h>
#include <sstream>
#include <stdlib.h>
#include <avr/dtostrf.h>

//AUXILIARES
#include "aux_wifi.h"
#include "aux_mqtt.h"
#include "aux_telegram.h"
#include "aux_sensores.h"

void setup() { 
  
  delay(3000); //delay para que inicio el draw
  Serial.begin(9600);
  Serial.println("Programa iniciado.");

  conectarWifi(); //aux_wifi.h

  //SENSORES
  suscribeMQTT((char *)"/v1.6/devices/invernadero/luminico/lv");
  suscribeMQTT((char *)"/v1.6/devices/invernadero/humedad/lv");
  suscribeMQTT((char *)"/v1.6/devices/invernadero/temperatura/lv");

  //SUELO
  suscribeMQTT((char *)"/v1.6/devices/invernadero/humedadsuelo/lv");
  suscribeMQTT((char *)"/v1.6/devices/invernadero/humedadsuelo_2/lv");
  suscribeMQTT((char *)"/v1.6/devices/invernadero/humedadsuelo_3/lv");
  suscribeMQTT((char *)"/v1.6/devices/invernadero/humedadsuelo_4/lv");


  dht.begin(); //para que funcione el sensor de temp. y humedad.

}

void loop() {

  client.loop(); //para que recibamos del productor de mqtt
  
  float luz = getLuz();
  float temperatura = getTemperatura(); 
  float humedad = getHumedad(); 

  sendDataToUbidots(luz,temperatura,humedad);

  float humedadSuelo1 = getHumedadSuelo(1);
  float humedadSuelo2 = getHumedadSuelo(2);
  float humedadSuelo3 = getHumedadSuelo(3);
  float humedadSuelo4 = getHumedadSuelo(4);

  sendSueloDataToUbidots(humedadSuelo1,humedadSuelo2, humedadSuelo3,humedadSuelo4);

  
  delay(5000);
}
