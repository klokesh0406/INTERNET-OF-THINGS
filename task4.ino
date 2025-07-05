// Blynk credentials
#define BLYNK_TEMPLATE_ID "TMPL333kVAfNt"
#define BLYNK_TEMPLATE_NAME "Airmonitor"
#define BLYNK_AUTH_TOKEN "IWqOwIoa1h181p_e53aSo7bVkGlaELO5"

// Wi-Fi credentials
char ssid[] = "Your_WiFi_SSID";
char pass[] = "Your_WiFi_Password";

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <SoftwareSerial.h>
#include <BlynkTimer.h>

BlynkTimer timer;

// MQ135 pin (analog CO₂)
const int mq135Pin = 34;  // You can change this if needed

// PMS5003 setup (PM2.5 sensor via UART)
SoftwareSerial pmsSerial(16, 17); // RX, TX for ESP32

// Function to send data to Blynk
void sendSensorData() {
  int co2_raw = analogRead(mq135Pin);    // Raw analog value from MQ135
  int pm25_value = readPM25();           // PM2.5 value from PMS5003

  Blynk.virtualWrite(V1, co2_raw);       // CO2 -> V1
  Blynk.virtualWrite(V2, pm25_value);    // PM2.5 -> V2

  Serial.print("CO₂ Raw Value: ");
  Serial.print(co2_raw);
  Serial.print(" | PM2.5: ");
  Serial.println(pm25_value);
}

// Basic PM2.5 reader for PMS5003
int readPM25() {
  if (pmsSerial.available()) {
    if (pmsSerial.read() == 0x42 && pmsSerial.read() == 0x4D) {
      byte buffer[30];
      pmsSerial.readBytes(buffer, 30);
      int pm25 = buffer[6] << 8 | buffer[7];
      return pm25;
    }
  }
  return -1;
}

void setup() {
  Serial.begin(115200);
  pmsSerial.begin(9600);
  pinMode(mq135Pin, INPUT);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  timer.setInterval(5000L, sendSensorData); // Send data every 5 sec
}

void loop() {
  Blynk.run();
  timer.run();
}