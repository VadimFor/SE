#include <WiFiNINA_Generic.h>


const char* ssid = "P";
const char* password = "sd123456";


void conectarWifi(){
  while (WiFi.begin(ssid, password) != WL_CONNECTED) {
    Serial.print("Conectando a ");
    Serial.print(ssid);
    Serial.println(" ...");
    delay(5000);
  }
  Serial.println("¡Conectado a la red wifi correctamente!");
}

