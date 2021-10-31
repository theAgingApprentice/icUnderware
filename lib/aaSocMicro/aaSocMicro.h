/**
 * @file aaSocMicro.h
 * @brief Library for the host Software On a Chip (SOC) Micro Controller (MC).  
 * @details This library was written to manage access to the four subsystems 
 * embedded in the ESP32 family of SOCs.  
 ===================================================================================*/
#ifndef aaSocMicro_h // Start precompiler code block. 

#define aaSocMicro_h // Precompiler macro used to avoid dupicate inclusion of this code.

/**
 * @section aaSocMicroIncludes Included libraries.
 ************************************************************************************/
#include <Arduino.h> // Arduino Core for ESP32. Comes with Platform.io.
#include <ArduinoLog.h> // https://github.com/thijse/Arduino-Log.
#include <rom/rtc.h> // Low level RTC functions such as RESET_REASON.

/**
 * @section aaSocMicroVars Define global variables.
 ************************************************************************************/
//const char CHIP_MANUFACTURER[20] = "Espressif";
//const char CHIP_RADIO[60] = "802.11 b/g/n/e/i (802.11n @ 2.4 GHz up to 150 Mbit/s)";
const int8_t NUM_CORES = 2;

/**
 * @class Manage wifi connection to Access Point.
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
