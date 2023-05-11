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
#include "aux_telegram.h"
#include "aux_sensores.h"

void setup() { 
  
  delay(3000); //delay para que inicio el draw
  Serial.begin(9600);
  Serial.println("Programa iniciado.");

  conectarWifi(); //aux_wifi.h

  suscribeMQTT((char *)"/v1.6/devices/invernadero/luminico/lv");//NOTA: es necesario suscribirse para poder publicar.
  suscribeMQTT((char *)"/v1.6/devices/invernadero/humedad/lv");//NOTA: es necesario suscribirse para poder publicar.
  suscribeMQTT((char *)"/v1.6/devices/invernadero/temperatura/lv");//NOTA: es necesario suscribirse para poder publicar.

  dht.begin(); //para que funcione el sensor de temp. y humedad.

}
  
void loop() {

  client.loop(); //para que recibamos del productor de mqtt
  
  getLuz(true);
  getTemperatura(true); 
  getHumedad(true); 
  
  delay(5000);
}
