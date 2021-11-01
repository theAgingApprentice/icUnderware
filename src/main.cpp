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
#include <main.h> // Header file for linking.

/**
 * Initialize the serial output. The usual Serial.print function used for 
 * serial output to the terminal is replaced in this project by the Arduino 
 * Log function. In the Log.begin() method pass one of the logging levels 
 * defined in Logging.h. Available levels are: LOG_LEVEL_SILENT, 
 * LOG_LEVEL_FATAL, LOG_LEVEL_ERROR, LOG_LEVEL_WARNING, LOG_LEVEL_INFO, 
 * LOG_LEVEL_TRACE or LOG_LEVEL_VERBOSE.
 * 
 * Note: To fully remove all logging code, uncomment the line 
 * #define DISABLE_LOGGING from the file Logging.h. This will significantly 
 * reduce the binary code file size.
 * ============================================================================*/
void setupSerial()
{
   bool showLevel = true; // Prefixed logging output with a single letter level.
   Serial.begin(SERIAL_BAUD_RATE); // Initialize serial port.
   while(!Serial && !Serial.available()) // Wait for serial to connect.
   {
   } // while
   Log.begin(LOG_LEVEL_VERBOSE, &Serial, showLevel); // Set logging parameters. 
} //setupSerial()

/**
 * @brief Standard Arduino initialization routine.
 * ==========================================================================*/
void setup() 
{
   setupSerial(); // Set serial baud rate. 
   Log.traceln("<setup> Start of setup.");
   MCU.logResetReason(); // Report on reason for last CPU reset.
   MCU.logSubsystemDetails(); // Log microprocessor details. 
   Log.traceln("<setup> End of setup."); 
} // start()

/**
 * @brief Standard Arduino main loop.
 * ==========================================================================*/
void loop() 
{

} // loop()
