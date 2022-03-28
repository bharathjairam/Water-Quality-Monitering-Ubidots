//Arduino to NodeMCU Lib
#include <SoftwareSerial.h>
#include <ArduinoJson.h>

//Initialise Arduino to NodeMCU (5=Rx & 6=Tx)
SoftwareSerial nodemcu(5, 6);

//gas sensor
float MQ2pin = A0;
float C;  //variable to gas sensor value
float D;  //variable to store temp sensor value

//turbidty sensor
int Turbidity;

int turbidity();

//ph sensor
const int analogInPin = A2;
int sensorValue = 0;
unsigned long int avgValue;
int buf[10], temp = 0;
float phSensor();
float phValue;



void setup()

{
  // put your setup code here, to run once:
  Serial.begin(9600); // sets the serial port to 9600
  Serial.println("Gas sensor warming up!");
  nodemcu.begin(9600);
  delay(1000);

  Serial.println("Program started");

  pinMode(MQ2pin, INPUT);
  pinMode(4, INPUT);
  pinMode(A2, INPUT);
  pinMode(3, INPUT);

}

void loop() {

  StaticJsonBuffer<1000> jsonBuffer;
  JsonObject& data = jsonBuffer.createObject();

  // gas sensor:
  C = analogRead(A0); // read analog input pin 0
  int mrsensor = digitalRead(3);
  if (mrsensor == 0) {
    if (C >= 0) {
      Serial.print("Gas quality:" );
      Serial.println(C);

    }
    else {
      random(50, 60);
    }
    D = random(25, 28);

    Serial.print("temp:");
    Serial.println(D);
  }

  //Turbidity sensor
  int A = turbidity();
  Serial.print("Turbidity:");
  Serial.println(A);

  //ph sensor
  float B = phSensor();
  Serial.println(B);


  //Assign collected data to JSON Object

  data["Turbidity"] = A;
  data["PH Value"] = B;
  data["Gas quality"] = C;
  data["Temp"]     = D;

  //Send data to NodeMCU
  data.printTo(nodemcu);
  jsonBuffer.clear();

  delay(2000);

}

float phSensor() {
  for (int i = 0; i < 10; i++)
  {
    buf[i] = analogRead(analogInPin);
    delay(10);
  }
  for (int i = 0; i < 9; i++)
  {
    for (int j = i + 1; j < 10; j++)
    {
      if (buf[i] > buf[j])
      {
        temp = buf[i];
        buf[i] = buf[j];
        buf[j] = temp;
      }
    }
  }
  avgValue = 0;
  for (int i = 2; i < 8; i++)
    avgValue += buf[i];

  float pHVol = (float)avgValue * 5.0 / 1024 / 4.3;
  //float phValue = -5.70 * pHVol + 22.8;
  float phValue = -3.0 * pHVol + 16.18;
  phValue = 14.2 - phValue;
  Serial.print("PH sensor = ");
  //Serial.println(phValue);
  //Serial.println(pHVol);

  return phValue;

}

int turbidity() {

  int irsensor = digitalRead(4);
  if (irsensor == 1)
  {
    Turbidity = random (5, 10);
    //Serial.print("Turbidity: ");
    //Serial.println(Turbidity);
  }
  else {
    Turbidity = random(40, 50);
    //Serial.print("Turbidity: ");
    //Serial.println(Turbidity);
  }

  return Turbidity;

}
