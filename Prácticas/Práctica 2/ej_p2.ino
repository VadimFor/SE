#include <Wire.h>
#include "MAX30105.h"

#include "heartRate.h"
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET     -1

MAX30105 particleSensor;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const byte RATE_SIZE = 4; //Increase this for more averaging. 4 is good.
byte rates[RATE_SIZE]; //Array of heart rates
byte rateSpot = 0;
long lastBeat = 0; //Time at which the last beat occurred

float beatsPerMinute;
int beatAvg;

//Pantalla
int TextSize=1; //tamaño del texto a imprimir
bool TextInverted=false; //false=Texto normal, true=Texto invertido
String Texto; //Texto a imprimir
int TextX; //Ubicacion en X del texto
int TextY; //Ubicacion en Y del texto
bool ClearScreen=false; //Limpiar pantalla
String Linea1;
String Linea2;

int led = 13;
void setup()
{

   
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
  Serial.print("SSD1306 allocation failed");
    for(;;); // Don't proceed, loop forever
  }

  display.display(); //Requerido por Adafruit Copywrite
  delay(2000); // Pause for 2 seconds
  display.clearDisplay();

  // Initialize sensor
  if (!particleSensor.begin(Wire, I2C_SPEED_FAST)) //Use default I2C port, 400kHz speed
  {
    Serial.println("MAX30105 was not found. Please check wiring/power. ");
    while (1);
  }
  particleSensor.setup(); //Configure sensor with default settings
  particleSensor.setPulseAmplitudeRed(0x0A); //Turn Red LED to low to indicate sensor is running
  particleSensor.setPulseAmplitudeGreen(0); //Turn off Green LED

 
  display.clearDisplay();
  PrintText(1,4,3,"Inicializando...");  
  display.display();
  pinMode(led,OUTPUT);
  digitalWrite(led,HIGH);
  delay(3000);
  digitalWrite(led,LOW);
  delay(500);


}

void loop()
{
  printErrorDEDO();
  long irValue = particleSensor.getIR();
  
  while(irValue < 50000){
    irValue = particleSensor.getIR();
  
    if (checkForBeat(irValue) == true)
    {
      //We sensed a beat!
      long delta = millis() - lastBeat;
      lastBeat = millis();
  
      beatsPerMinute = 60 / (delta / 1000.0);
  
      if (beatsPerMinute < 255 && beatsPerMinute > 20)
      {
        rates[rateSpot++] = (byte)beatsPerMinute; //Store this reading in the array
        rateSpot %= RATE_SIZE; //Wrap variable
  
        //Take average of readings
        beatAvg = 0;
        for (byte x = 0 ; x < RATE_SIZE ; x++)
          beatAvg += rates[x];
        beatAvg /= RATE_SIZE;
      }
    }
  }

  if(irValue <50000)
  {
    Linea1="ERROR DEDO";
    Linea2="";
  }
  else
  {
    Linea1="BPM = " + String (int(beatsPerMinute));
    Linea2="Avg = " + String(beatAvg);
  }
  
  display.clearDisplay();
  PrintText(1,4,3,Linea1);  
  PrintText(1,4,18, Linea2);
  //display.drawRect(1, 1, 126,31, WHITE);
  display.display();

  //LED
  if (int(beatsPerMinute) < 70){ //FIJO
    digitalWrite(led,HIGH);
    delay(5000); //delay 5 segundos
    digitalWrite(led,LOW); 
  }else{
    if(int(beatsPerMinute) >= 70 && int(beatsPerMinute) < 110){ //PARDPADEO CADA SEGUNDO EN 5 SEGUNDOS
        parpadeo(1000); //2s
        parpadeo(1000); //2s
        parpadeoHIGH(1000); //1s
        digitalWrite(led,LOW); 
    }else{
      if(int(beatsPerMinute) > 110){ //PARDPADEO CADA MEDIO SEGUNDO EN 5 SEGUNDOS
        parpadeo(500); //1s
        parpadeo(500); //1s
        parpadeo(500); //1s
        parpadeo(500); //1s
        parpadeo(500); //1s
      }
    }
  }

  beatsPerMinute=0;
}

////FUNCIONES//////////////////////////

//Imprimir Text en pantalla
void PrintText(int Size,int X, int Y,String Texto)
{
  display.setTextSize(Size);
  display.setTextColor(WHITE);
  display.setCursor(X,Y);
  display.println(Texto);

}

void printErrorDEDO(){
  display.clearDisplay();
  PrintText(1,4,3,"ERROR DEDO");  
  digitalWrite(led,LOW);
  display.display();
}

void parpadeo(int ms){
  parpadeoHIGH(ms);
  parpadeoLOW(ms);
}

void parpadeoHIGH(int ms){
    digitalWrite(led,HIGH);
    delay(ms);   
}

void parpadeoLOW(int ms){
    digitalWrite(led,LOW);  
    delay(ms);  
}
