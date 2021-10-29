/*******************************************************************************
 * @file main.h  
 *******************************************************************************/
#ifndef main_h // Start of precompiler check to avoid dupicate inclusion of this code block.

#define main_h // Precompiler macro used for precompiler check.

/*******************************************************************************
 * @section mainIncludes Included libraries.
 *******************************************************************************/
#include <Arduino.h> // Arduino Core for ESP32. Comes with PlatformIO.
#include <ArduinoLog.h> // https://github.com/thijse/Arduino-Log.
#include <aaChip.h> // Information about the host processor. 

/************************************************************************************
 * @section mainGlobalVars Global variables and constants.
 ************************************************************************************/
const unsigned long SERIAL_BAUD_RATE = 115200;
aaChip bob;

/************************************************************************************
 * @section mainDeclare Declare functions found in main.cpp.
 ************************************************************************************/
void setupSerial(); // Serial output initilization.
void setup(); // Arduino mandatory function #1. Runs once at boot. 
void loop(); // Arduino mandatory function #2. Runs continually.

#endif // End of precompiler protected code block