/******************************************************************************
 * @file main.cpp
 *
 * @mainpage the Aging Apprentice underwear 
 * 
 * @section intro_sec Introduction
 *
 * This Arduino for ESP32 code serves as the base code you will use to create 
 * your IOT embedded system's device software. Extend this code to create your 
 * application. This code is broken down into modules. 
 *
 * @section dependencies Dependencies
 * 
 * This class depends on on <a href="https://github.com/espressif/arduino-esp32">
 * Arduino.h</a> being present on your system. This is the Arduino core library
 * that comes bundled with PlatformIO.
 *
 * @section author Author(s)
 *
 * Written by Old Squire for the Aging Apprentice.
 *
 * @section license license
 *
 * Copyright 2021 the Aging Apprentice 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to 
 * deal in the Software without restriction, including without limitation the 
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is 
 * furnished to do so, subject to the following conditions: The above copyright
 * notice and this permission notice shall be included in all copies or 
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.  
 *****************************************************************************/
#include <main.h> // Header file for linking.

/**
 * @brief Initialize the serial output.
 * @details The usual Serial.print function used for serial output to the 
 * terminal is replaced in this project by the Arduino Log function. In the 
 * Log.begin() method pass one of the logging levels defined in Logging.h. 
 * Available levels are: LOG_LEVEL_SILENT, LOG_LEVEL_FATAL, LOG_LEVEL_ERROR, 
 * LOG_LEVEL_WARNING, LOG_LEVEL_INFO, LOG_LEVEL_TRACE or LOG_LEVEL_VERBOSE.
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
   Log.verboseln("<setup> Chip manufacturer = %s.", bob.manufacturer); 
   Log.verboseln("<setup> Chip model = %u.", bob.getChipModel()); 
   Log.verboseln("<setup> Chip revision = %u.", bob.getChipRevision()); 
   Log.verboseln("<setup> SDK version = %s.", bob.SdkVer); 
//- manufacturer - public const char manufacturer[]
//- model - getChipModel(), getChipRevision()
//- cpu - getCpuId(), getCpuClock()
//- memory - getCodeSize(), getFreeHeap()   
   Log.traceln("<setup> End of setup."); 
} // start()

/**
 * @brief Standard Arduino main loop.
 * ==========================================================================*/
void loop() 
{

} // loop()