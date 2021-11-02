/*
                   .d8888b.                    888b     d888 d8b                          
                  d88P  Y88b                   8888b   d8888 Y8P                          
                  Y88b.                        88888b.d88888                              
 8888b.   8888b.   "Y888b.    .d88b.   .d8888b 888Y88888P888 888  .d8888b 888d888 .d88b.  
    "88b     "88b     "Y88b. d88""88b d88P"    888 Y888P 888 888 d88P"    888P"  d88""88b 
.d888888 .d888888       "888 888  888 888      888  Y8P  888 888 888      888    888  888 
888  888 888  888 Y88b  d88P Y88..88P Y88b.    888   "   888 888 Y88b.    888    Y88..88P 
"Y888888 "Y888888  "Y8888P"   "Y88P"   "Y8888P 888       888 888  "Y8888P 888     "Y88P"  
                                                                                                                                                  
EP32 core control library for Arduino
Github: https://github.com/theAgingApprentice/icUnderware/tree/main/lib/aaSocMicro
Licensed under the MIT License <http://opensource.org/licenses/MIT>.                                                                                                              
*/

#ifndef aaSocMicro_h // Start precompiler code block. 

#define aaSocMicro_h // Precompiler macro to prevent duplicate inclusions.

/**
 * Included libraries.
 ******************************************************************************/
#include <Arduino.h> // Arduino Core for ESP32. Comes with Platform.io.
#include <ArduinoLog.h> // https://github.com/thijse/Arduino-Log.
#include <rom/rtc.h> // Low level RTC functions such as RESET_REASON.

/**
 * Global variables.
 ******************************************************************************/
const int8_t NUM_CORES = 2;

/**
 * The aaSocMicro class provides a single object of authority regarding the 
 * ESP32. Details are collected from both FreeRTOS and the ESP32 Arduino 
 * framework. The information comes from the ESP32's six substems which are 
 * outlined below.
 * 
 * Core subsystem
 * ==============
 * 
 * The core subsystem is made up of two CPUs, refered to as COR0 and COR1, as 
 * well as both ROM and RAM memory, referred to as core memory.
 * 
 * WiFi subsystem
 * ==============
 * 
 * The Wifi subsystem shares RF send/recieve, clock, switch and balun with the 
 * Bluetooth subsystem.
 * 
 * Bluetooth subsystem
 * ===================
 * 
 * The Bluetooth subsystem shares RF send/recieve, clock, switch and balun with 
 * the WiFi subsystem.
 * 
 * RTC subsystem
 * =============
 * 
 * The Real Time Clock (RTC) subsystem is used by the ESP32 for low power modes. It
 * contains the following: 
 * 
 * 1. The Phasor Measurement Unit (PMU)
 * 2. The small and ultra low power (ULP) 32-bit co-processor
 * 3. 8Kbs of RAM memory known as the recovery memory. 
 * 
 * Crytographic Acceleration subsystem
 * =================================== 
 * The Cryptograpic Acceleration subsystem provides hardware encrytion acceleration.
 * The following algorithms are supported:
 * 
 * 1. SHA
 * 2. RSA
 * 3. AES
 * 4. RNG 
 * 
 * Peripherals subsystem
 * =====================
 * 
 * The Peripherals subsystem handles all of the General Purpose Input/Output (GPIO) 
 * interfaces.
 ************************************************************************************/
class aaSocMicro 
{
   public:
      aaSocMicro(); // First form class constructor.
      aaSocMicro(Print *); // Second form of class constructor.
      aaSocMicro(int, Print *, bool); // Third form of class constructor.
      ~aaSocMicro(); // Class destructor.
      void logResetReason(); // Logs last CPU reset reason for both cores.
      void logSubsystemDetails(); // Logs details of host micro controller.
   private:
      void _transReasonCode(char &, RESET_REASON); // Translate reset reason codes.
      void _logCoreCPU(); // Logs core CPU details.
      void _logCoreMem(); // Logs core memory details.
      void _logIntegratedFlash(); // Logs integrated flash details.
      void _logPsramMem(); // Logs PSRAM details.
      void _transFlashModeCode(char &); // Translate flash memory mode code.
      void _logGPIO(); // Logs GPIO details.
      void _Wireless(); // Logs radio details.
      void _Bluetooth(); // Logs bluetooth details.     
}; //class aaSocMicro

#endif // End of precompiler protected code block
