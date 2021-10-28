/******************************************************************************
 * @file aaTemplate.cpp
 *
 * @mainpage the Aging Apprentice flash memory class 
 * 
 * @section intro_sec Introduction
 *
 * This is an Arduino class that saves variables to flash memory to preserve
 * information through a reboot. This is part of a series of classes made 
 * to support a standard set of APIs for robot platforms. 
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
#include <aaTemplate.h> // Header file for linking.

/**
 * @class Write variables to flash memory.
 ============================================================================*/
aaTemplate::aaTemplate() 
{
   Serial.println("<aaTemplate::aaTemplate> Default constructor running.");
} // aaTemplate::aaTemplate()

/**
 * @brief This is the destructor for this class.
 =============================================================================*/
aaTemplate::~aaTemplate() 
{
   Serial.println("<aaTemplate::aaTemplate> Destructor running.");
} // aaTemplate::aaTemplate()

/**
 * @brief This is a public class that is exlained in one sentence.
 * @param int This is an explanation of what this parameter is for.
 =============================================================================*/
void examplePublicFunction(int var)
{
} // aaTemplate::examplePublicFunction()

/**
 * @brief This is a private class with an underscore at the front of the name.
 * @return .
 =============================================================================*/
bool _examplePrivateFunction()
{
   bool var = true;
   return var;
} // aaTemplate::_examplePrivateFunction()