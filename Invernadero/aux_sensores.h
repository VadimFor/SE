
char* floatToString(float f) {
    char* str = (char*) malloc(sizeof(char) * 20); // dynamically allocate memory
    if(str == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    sprintf(str, "%.3f", f); // write the float to the string

    return str; // return the string
}


//█████████ＳＥＮＳＯＲ ＬＵＭＩＮＯＳＩＤＡＤ██████████

#define PIN_LUZ A0 

float getLuz(){ return analogRead(PIN_LUZ) * (5.0 / 1023.0);}

//█████ＳＥＮＳＯＲ ＨＵＭＥＤＡＤ Ｙ ＴＥＭＰＥＲＡＴＵＲＡ██████

#include "DHT.h"

#define DHTPIN 2          // El pin GPIO al que se conecta el sensor DHT22
#define DHTTYPE DHT22     // Tipo de sensor DHT22

DHT dht(DHTPIN, DHTTYPE);

float getHumedad(){return dht.readHumidity();}
float getTemperatura(){return dht.readTemperature();}

//█████████████ＳＥＮＳＯＲ ＳＵＥＬＯ██████████████

#define PIN_SUELO1 A4 
#define PIN_SUELO2 A5 
#define PIN_SUELO3 A6 
#define PIN_SUELO4 A7 

float getHumedadSuelo(int num_sensor){
  if(num_sensor >= 1 && num_sensor <=4){ //solo hay 4 sensores de suelo
 
    float soilMoisture = 0;
    int soilPin = 0;
    
    switch(num_sensor){
      case 1: soilPin = PIN_SUELO1;
      case 2: soilPin = PIN_SUELO2;
      case 3: soilPin = PIN_SUELO3;
      case 4: soilPin = PIN_SUELO4;
    }
     return map(analogRead(soilPin), 0, 1023, 0, 100);
  }
}
