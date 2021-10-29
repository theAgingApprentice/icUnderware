/*!
 * @file aaNetwork.h  
 * @defgroup globalVariables Class global variables.
 ===================================================================================*/
#ifndef aaChip_h // Start precompiler code block. 

#define aaChip_h // Precompiler macro used to avoid dupicate inclusion of this code.
/************************************************************************************
 * @section aaNetworkIncludes Included libraries.
 ************************************************************************************/
#include <Arduino.h> // Arduino Core for ESP32. Comes with Platform.io.
#include <ArduinoLog.h> // https://github.com/thijse/Arduino-Log.

const char CHIP_MANUFACTURER[20] = "Espressif";
const char CHIP_RADIO[60] = "802.11 b/g/n/e/i (802.11n @ 2.4 GHz up to 150 Mbit/s)";
/************************************************************************************
 * @class Manage wifi connection to Access Point.
 ************************************************************************************/
class aaChip 
{
/*
integratedCircuit object notes. 
- Extends chip class
- Extends network class
From Chip
- manufacturer - public const char manufacturer[]
- model - getChipModel(), getChipRevision()
- cpu - getCpuId(), getCpuClock()
- memory - getCodeSize(), getFreeHeap()
- Secondary Storage - Flash-W25Q32 (4M Bytes)
- getSdkVersion() - Where does this fit in?
From Network
- Radio - 2.4Gh transmit & recieve.
- TCP/IP, full 802.11 b/g/n/e/i WLAN MAC protocol. Also it is able to create an Access point with full 802.11 b/g/n/e/i.
*/
   public:
      aaChip(); // First form class constructor.
      aaChip(Print *); // Second form of class constructor.
      aaChip(int, Print *, bool); // Third form of class constructor.
      ~aaChip(); // Class destructor.
//      const char* getSDKVer();
      const char* getChipModel();
      uint8_t getChipRevision();
      uint32_t getSerialSpeed();
      uint32_t getCodeSize();
      uint32_t getFreeHeap();
      uint32_t getCpuId();
      uint32_t getCpuClock();
      char manufacturer[20];
      char radio[60];
      char SdkVer[20];
   private:
      void initVars();
}; //class aaNetwork

// extern aaChip IC; // Expose all public variables and methods.

#endif // End of precompiler protected code block
