


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

//█████████████ＳＥＮＳＯＲ ＳＵＥＬＯ██████████████

#define PIN_SUELO1 A4 
#define PIN_SUELO2 A5 
#define PIN_SUELO3 A6 
#define PIN_SUELO4 A7 

float getHumedadSuelo(bool publicar,int num_sensor){

  if(num_sensor >= 1 && num_sensor <=4){ //solo hay 4 sensores de suelo
 
    int soilValue = 0;     
    int soilMoisture = 0;
    int soilPin = 0;
    
    switch(num_sensor){
      case 1: soilPin = PIN_SUELO1;
      case 2: soilPin = PIN_SUELO2;
      case 3: soilPin = PIN_SUELO3;
      case 4: soilPin = PIN_SUELO4;
    }
  
    soilValue = analogRead(soilPin);        
    soilMoisture = map(soilValue, 0, 1023, 0, 100);  

    Serial.print("Valor: ");
    Serial.print(soilValue);
    Serial.print("\tHumedadSuelo: ");
    Serial.print(soilMoisture);
    Serial.println("%");
  
  }else{
    Serial.println("ERROR: El sensor de humedad tiene que ser entre el 1 y el 4.");
  }
}
