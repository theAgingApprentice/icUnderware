#ifndef main_h // Start of precompiler check to avoid dupicate inclusion of this code block.
   #define main_h // Precompiler macro used for precompiler check.

/**
 * Included libraries.
 ******************************************************************************/
#include <Arduino.h> // Arduino Core for ESP32. Comes with PlatformIO.
#include <ArduinoLog.h> // https://github.com/thijse/Arduino-Log.
#include <aaSocMicro.h> // Information about the host ESP32 SOC. 

/**
 * Global variables, constants and objects.
 */
const unsigned long SERIAL_BAUD_RATE = 115200;
aaSocMicro MCU;
const char* appName = "APP_NAME"; // Put the name of your app here.
char uniqueName[40]; // Unique name safe to use for  MQTT topic trees.

/**
 * Declare functions found in main.cpp.
 ******************************************************************************/
void setupSerial(); // Serial output initilization.
void setup(); // Arduino mandatory function #1. Runs once at boot. 
void loop(); // Arduino mandatory function #2. Runs continually.

#endif // End of precompiler protected code block