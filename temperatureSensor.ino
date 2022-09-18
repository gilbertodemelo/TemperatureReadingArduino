#include <WiFi101.h>
#include "secrets.h"
#include "arduinoCloud.h"
#include "ThingSpeak.h"

char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;


WiFiClient client;

unsigned long myChannelNumber = SECRET_CH_ID;
const char* myWriteAPIKey = SECRET_WRITE_APIKEY;

int sensorPin = A0;
int sensorValue = 0;
// float temperature;
// float voltage;



void setup() {
  Serial.begin(9600);
  analogReadResolution(10);

  // Connect to ThingSpeak
  ThingSpeak.begin(client);

  // defined in arduinoCloud.h
  initProperties();

  // Connect to Arduino IoT Clound
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);

  /*
     The following function allows you to obtain more information
     related to the state of network and IoT Cloud connection and errors
     the higher number the more granular information you’ll get.
     The default is 0 (only errors).
     Maximum is 4
 */
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}

void loop() {

  ArduinoCloud.update();

  // connect to WiFi
   if(WiFi.status() != WL_CONNECTED){
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(SECRET_SSID);
    while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid, pass);  // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      delay(5000);     
    } 
    Serial.println("\nConnected.");
   }

  sensorValue = analogRead(sensorPin);
  Serial.print("sensorValue = ");
  Serial.print(sensorValue);
  Serial.print("\n");
  
  voltage = (sensorValue * (3300/1024)); // milliVolt
  Serial.print("voltage = ");
  Serial.print(voltage);
  Serial.print("\n");

  temperature = ((voltage - 500) / 10);
  Serial.print("temperature(°C) =  ");
  Serial.print(temperature);
  Serial.print("\n");

  // Write to ThingSpeak
  int x = ThingSpeak.writeField(myChannelNumber, 1, temperature, myWriteAPIKey);
  if (x = 200) {
    Serial.println("Channel update successful.");
  } else {
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }

  delay(2000);

}

/*
  Since Temperature is READ_WRITE variable, onTemperatureChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onTemperatureChange()  {
  // Add your code here to act upon Temperature change
}
