/******************************************************************************
 * @file aaChip.cpp
 *
 * @mainpage the Aging Apprentice microprcessor information class 
 * 
 * @section intro_sec Introduction
 *
 * This is an Arduino class that retrieves information about the integrated
 * circuit running the binary.  
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
#include <aaChip.h> // Header file for linking.

/**
 * @class Retrieve integrated circuit configuration details from both FreeRTOS 
 * and the ESP32 Arduino framework.
 * @details This is the first variation of the class constructor. Logging
 * defaults to silent mode.
 * @param null
 * @return null
 * ==========================================================================*/
aaChip::aaChip()
{
   bool showLevel = true; // Prefixed logging output with a single letter level.
   int loggingLevel = LOG_LEVEL_SILENT;
   Print *output = &Serial;
   Log.begin(loggingLevel, output, showLevel); // Set logging parameters. 
   Log.verboseln("<aaChip::FirstFormConstructor> Logging set to %d.", loggingLevel);
   initVars(); // Initialize public variables.
} //aaChip::aaChip()

/**
 * @class Retrieve integrated circuit configuration details from both FreeRTOS 
 * and the ESP32 Arduino framework.
 * @details This is the second variation of the class constructor. Logging is
 * sent to the specified output pointer.
 * @param output class that handles bit stream input.
 * @return null
 * ==========================================================================*/
aaChip::aaChip(Print *output)
{
   bool showLevel = true; // Prefixed logging output with a single letter level.
   int loggingLevel = LOG_LEVEL_SILENT;
   Log.begin(loggingLevel, output, showLevel); // Set logging parameters. 
   Log.traceln("<aaChip::SecondFormConstructor> Logging set to %d.", loggingLevel);
   initVars(); // Initialize public variables.
} //aaChip::aaChip()

/**
 * @class Retrieve integrated circuit configuration details from both FreeRTOS 
 * and the ESP32 Arduino framework.
 * @details This is the third variation of the class constructor. Logging is
 * sent to the specified output pointer at the specified logging level.
 * @param loggingLevel is one of 6 predefined levels from the logging library.
 * @param output class that handles bit stream input.
 * @param showLevel when true prefixs log message with the logging level letter.
 * @return null
 * ==========================================================================*/
aaChip::aaChip(int loggingLevel, Print *output, bool showLevel)
{
   Log.begin(loggingLevel, output, showLevel); // Set logging parameters. 
   Log.traceln("<aaChip::SecondFormConstructor> Logging set to %d.", loggingLevel);
   initVars(); // Initialize public variables.
} //aaChip::aaChip()

/**
 * @brief This is the destructor for this class.
 * @param null
 * @return null
 * ==========================================================================*/
aaChip::~aaChip()
{
   Log.traceln("<aaChip::~aaChip> Destructor running.");
} //aaChip::~aaChip()

/**
 * @brief Populate public variables.
 * @param null
 * @return null
 * ==========================================================================*/
void aaChip::initVars()
{
   Log.traceln("<aaChip::initVars> Populate public variables.");
   strcpy(manufacturer, CHIP_MANUFACTURER);
   strcpy(radio, CHIP_RADIO);
   strcpy(SdkVer, ESP.getSdkVersion());
} // aaChip::initVars()

/**
 * @brief Returns the version number of the SDK used to build the binary.
 * @param null
 * @return cont char* ESP.getSdkVersion()   
 * ==========================================================================*/
//const char* aaChip::getSDKVer()
//{
//   Log.traceln("<aaChip::getSDKVer> Retrieve SDK version.");
//   return ESP.getSdkVersion();
//} //aaChip::getSDKVer()

/**
 * @brief Returns the revision number of the ESP32 chip.
 * @param null
 * @return uint32_t ESP.getChipModel()   
 * ==========================================================================*/
const char* aaChip::getChipModel()
{
   Log.traceln("<aaChip::getChipModel> Retrieve chip model.");
   return ESP.getChipModel();
} //aaChip::getChipModel()

/**
 * @brief Returns the revision number of the ESP32 chip.
 * @param null
 * @return uint32_t ESP.getChipRevision()   
 * ==========================================================================*/
uint8_t aaChip::getChipRevision()
{
   Log.traceln("<aaChip::getChipRevision> Retrieve chip revision.");
   return ESP.getChipRevision();
} //aaChip::getChipRevision()

/**
 * @brief Returns the size of the binary file in bytes.
 * @param null
 * @return uint32_t ESP.getSketchSize()   
 * ==========================================================================*/
uint32_t aaChip::getCodeSize()
{
   Log.traceln("<aaChip::getCodeSize> Retrieve code size.");
   return ESP.getSketchSize();
} //aaChip::getCodeSize()

/**
 * @brief Returns number of bytes of sorted memory the program can use.
 * @param null
 * @return uint32_t ESP.getFreeHeap()   
 * ==========================================================================*/
uint32_t aaChip::getFreeHeap()
{
   Log.traceln("<aaChip::getFreeHeap> Retrieve free heap size.");
   return ESP.getFreeHeap();
} //aaChip::getFreeHeap()

/**
 * @brief Returns the current baud rate that the serial port is set to.
 * @param null
 * @return uint32_t Serial.baudRate()   
 * ==========================================================================*/
uint32_t aaChip::getSerialSpeed()
{
   Log.traceln("<aaChip::getSerialSpeed> Retrieve serial baud rate.");
   return Serial.baudRate();
} //aaChip::getSerialSpeed()

/**
 * @brief Returns the CPU ID of the application core.
 * @param null
 * @return uint32_t xPortGetCoreID()   
 * ==========================================================================*/
uint32_t aaChip::getCpuId()
{
   Log.traceln("<aaChip::getCpuId> Retrieve application core ID.");
   return xPortGetCoreID();
} //aaChip::getCpuId()

/**
 * @brief Returns the clock speed of the application core in Mhz.
 * @param null
 * @return uint32_t Serial.baudRate()   
 * ==========================================================================*/
uint32_t aaChip::getCpuClock()
{
   Log.traceln("<aaChip::getCpuClock> Retrieve application core CPU clock speed.");
   return getCpuFrequencyMhz();
} //aaChip::getCpuClock()