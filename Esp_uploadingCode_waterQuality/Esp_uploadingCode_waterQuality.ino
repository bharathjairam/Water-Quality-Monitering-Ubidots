
#include <ESP8266WiFi.h>
#include <OneWire.h>
#include <SoftwareSerial.h>
#include <ArduinoJson.h>


//D6 = Rx & D5 = Tx
SoftwareSerial nodemcu(D6, D5);

#define WIFI_SSID "MAJOR PROJECT"
#define WIFI_PASSWORD "12345678"

void setup() {

  // Initialize Serial port
  Serial.begin(9600);
  nodemcu.begin(9600);
  while (!Serial) continue;

}

void loop() {
  // Serial Communication
  StaticJsonBuffer<1000> jsonBuffer;
  JsonObject& data = jsonBuffer.parseObject(nodemcu);

  if (data == JsonObject::invalid()) {
    //Serial.println("Invalid Json Object");
    jsonBuffer.clear();
    return;
  }

  Serial.println("JSON Object Recieved");
  Serial.print("Turbidity:  ");
  float A = data["Turbidity"];
  Serial.println(A);
  Serial.print("PH Value:  ");
  float B = data["PH Value"];
  Serial.println(B);
  Serial.print("Gas quality:  ");
  float C = data["Gas quality"];
  Serial.println(C);
  Serial.print("Temp:  ");
  float D = data["Temp"];
  Serial.println(D);
  Serial.println("-----------------------------------------");


}
