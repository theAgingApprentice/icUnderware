/*
   d8b          888     888               888                                                          
   Y8P          888     888               888                                                          
                888     888               888                                                          
   888  .d8888b 888     888 88888b.   .d88888  .d88b.  888d888 888  888  888  8888b.  888d888  .d88b.  
   888 d88P"    888     888 888 "88b d88" 888 d8P  Y8b 888P"   888  888  888     "88b 888P"   d8P  Y8b 
   888 888      888     888 888  888 888  888 88888888 888     888  888  888 .d888888 888     88888888 
   888 Y88b.    Y88b. .d88P 888  888 Y88b 888 Y8b.     888     Y88b 888 d88P 888  888 888     Y8b.     
   888  "Y8888P  "Y88888P"  888  888  "Y88888  "Y8888  888      "Y8888888P"  "Y888888 888      "Y8888 

   Log library for Arduino
   https://github.com/theAgingApprentice/icUnderware
   Licensed under the MIT License <http://opensource.org/licenses/MIT>.
 */

#ifndef main_h // Start of precompiler check to avoid dupicate inclusion of this code block.

#define main_h // Precompiler macro used for precompiler check.

/*
 * Included libraries.
 */
#include <Arduino.h> // Arduino Core for ESP32. Comes with PlatformIO.
#include <ArduinoLog.h> // https://github.com/thijse/Arduino-Log.
#include <aaSocMicro.h> // Information about the host ESP32 SOC. 

/*
 * Global variables, constants and objects.
 */
const unsigned long SERIAL_BAUD_RATE = 115200;
aaSocMicro MCU;

/*
 * Declare functions found in main.cpp.
 */
void setupSerial(); // Serial output initilization.
void setup(); // Arduino mandatory function #1. Runs once at boot. 
void loop(); // Arduino mandatory function #2. Runs continually.

#endif // End of precompiler protected code block