#define BLYNK_TEMPLATE_ID "TMPL3R_AaR0s0"
#define BLYNK_TEMPLATE_NAME "Home automation"
#define BLYNK_AUTH_TOKEN "MXH_aE1fNcKna6_D1Hsch3XBjiLpsfwM"

#include<wifi.h>
#include<BlynkSimpleEsp32.h>

#define RELAY_FAN_PIN 23 //relay control pin for fan 
#define LED_PIN 22      //relay control pin for LED
// WIFI credentials
const char* ssid="your_SSID";
const char* password="your_Password";

//Initializing blynk
void setup()
{
  Serial.begin(115200); //serial communication for ESP32
  pinMode(RELAY_FAN_PIN,OUTPUT);
  pinMode(LED_PIN,OUTPUT);

  digitalWrite(RELAY_FAN_PIN,LOW);
  digitalWrite(LED_PIN,LOW);         //set the both pins as low

  Blynk.begin(BLYNK_AUTH_TOKEN,ssid,password);  //wifi connection
}
BLYNK_WRITE(V1)  //virtual pin1 for fan
{                  
 int fanState=param.asInt(); //get the value from the app
 digitalWrite(RELAY_FAN_PIN,fanState);
 }
BLYNK_WRITE(V2){      //virtual pin2 for LED
  int ledState=param.asInt();
  digitalWrite(LED_PIN,ledState);
}
void loop(){
  Blynk.run();   //blynk run to keep connection alive
}