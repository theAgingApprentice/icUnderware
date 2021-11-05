#include <main.h> // Header file for linking
/**
 * Initialize the serial output. The usual Serial.print function used for 
 * serial output to the terminal is replaced in this project by the Arduino 
 * Log function. In the Log.begin() method pass one of the logging levels 
 * defined in Logging.h. Available levels are: LOG_LEVEL_SILENT, 
 * LOG_LEVEL_FATAL, LOG_LEVEL_ERROR, LOG_LEVEL_WARNING, LOG_LEVEL_INFO, 
 * LOG_LEVEL_TRACE or LOG_LEVEL_VERBOSE.
 * 
 * Note: To fully remove all logging code, uncomment the line 
 * #define DISABLE_LOGGING from the file Logging.h. This will 
 * significantly reduce the binary code file size.
 ******************************************************************************/
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
 * Standard Arduino initialization routine.
 ******************************************************************************/
void setup() 
{
   setupSerial(); // Set serial baud rate. 
   Log.traceln("<setup> Start of setup.");
   MCU.logResetReason(); // Report on reason for last CPU reset.
   MCU.configure(); // Configure robot.
   MCU.logSubsystemDetails(); // Log microprocessor details.
   MCU.getUniqueName(*uniqueName, appName);
   Log.verboseln("<setup> Unique network name = %s.", uniqueName);
   Log.traceln("<setup> End of setup.");
} // start()

/**
 * Standard Arduino main loop.
 ******************************************************************************/
void loop() 
{

} // loop()
