#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>
#include "secrets.h"

const char SSID[] = SECRET_SSID;
const char PASS[] = SECRET_PASS;

void onTemperatureChange();

float temperature;
float voltage;

void initProperties() {

  ArduinoCloud.addProperty(temperature, READWRITE, ON_CHANGE, onTemperatureChange);
  //ArduinoCloud.addProperty(voltage, READWRITE, ON_CHANGE, onVoltageChange);
}

WiFiConnectionHandler ArduinoIoTPreferredConnection(SSID, PASS);