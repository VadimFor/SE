#include <PubSubClient.h>

WiFiClient wifiClient;
PubSubClient client(wifiClient);//mqtt

const char* mqttServer = "industrial.api.ubidots.com";
const int mqttPort = 1883;

const char* ubidots_token = "BBFF-QOlG4i8VsjPcsJQDGhkBk6jIoi8SKt";
const char* ubidots_username = "grupo_se";
const char* ubidots_password = "@grupose123";

void callback(char* topic, byte* payload, unsigned int length){
  Serial.print("Ha llegado mensaje en el topic[");
  Serial.print(topic);
  Serial.print("]. Mensaje: ");
  for(int i=0; i<length; i++){ 
    Serial.print((char)payload[i]);
  }

Serial.println(" ");
}

void suscribeMQTT(char* topic){
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
  
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
    if (client.connect("ESP32", ubidots_token, ubidots_password)) {
      Serial.println("Connected to MQTT");     
      client.subscribe(topic);
    } else {
      Serial.print("Failed with state ");
      Serial.print(client.state());
      delay(2000);
    }
  }
}

