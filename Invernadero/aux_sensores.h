


//█████████ＳＥＮＳＯＲ ＬＵＭＩＮＯＳＩＤＡＤ██████████

#define PIN_LUZ A0 

float getLuz(bool publicar){
   // Leemos el valor del sensor
  int sensorValue = analogRead(PIN_LUZ);
  float lux = sensorValue * (5.0 / 1023.0); 

  // Imprimimos el valor en el monitor serial
  Serial.print("Intensidad lumínica: ");
  Serial.print(lux);
  Serial.println(" lux");

  if(publicar){ publishMQTT((char *)"/v1.6/devices/invernadero/luminico", lux);}

  return lux;
}

//█████ＳＥＮＳＯＲ ＨＵＭＥＤＡＤ Ｙ ＴＥＭＰＥＲＡＴＵＲＡ██████

#include "DHT.h"

#define DHTPIN 2          // El pin GPIO al que se conecta el sensor DHT22
#define DHTTYPE DHT22     // Tipo de sensor DHT22

DHT dht(DHTPIN, DHTTYPE);

float getHumedad(bool publicar){
  float humidity = dht.readHumidity();           // Leer humedad relativa en porcentaje
  
  Serial.print("Humedad: ");
  Serial.print(humidity);
  Serial.println(" %");

  if(publicar){ publishMQTT((char *)"/v1.6/devices/invernadero/humedad", humidity);}

  return humidity;
}

float getTemperatura(bool publicar){
  float temperature = dht.readTemperature();     // Leer temperatura en grados Celsius
  
  Serial.print("Temperatura: ");
  Serial.print(temperature);
  Serial.println(" ºC");

  if(publicar){ publishMQTT((char *)"/v1.6/devices/invernadero/temperatura", temperature);}

  return temperature;
}
