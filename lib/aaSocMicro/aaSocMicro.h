/*
                   .d8888b.                    888b     d888 d8b                          
                  d88P  Y88b                   8888b   d8888 Y8P                          
                  Y88b.                        88888b.d88888                              
 8888b.   8888b.   "Y888b.    .d88b.   .d8888b 888Y88888P888 888  .d8888b 888d888 .d88b.  
    "88b     "88b     "Y88b. d88""88b d88P"    888 Y888P 888 888 d88P"    888P"  d88""88b 
.d888888 .d888888       "888 888  888 888      888  Y8P  888 888 888      888    888  888 
888  888 888  888 Y88b  d88P Y88..88P Y88b.    888   "   888 888 Y88b.    888    Y88..88P 
"Y888888 "Y888888  "Y8888P"   "Y88P"   "Y8888P 888       888 888  "Y8888P 888     "Y88P"  
                                                                                                                                                  
Part of the Aging Apprentice's Arduino API for ESP32 core.
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
#include <WiFi.h> // Required to connect to WiFi network. Comes with Platform.io.
#include <aaFormat.h> // Collection of handy format conversion functions.
#include <knownNetworks.h> // Defines Access points and passwords that the robot can scan for and connect to.
#include <ESP32Ping.h> // Verify IP addresses. https://github.com/marian-craciunescu/ESP32Ping.
#include "esp_bt_main.h"
#include "esp_bt_device.h"

/**
 * Global variables.
 ******************************************************************************/
enum signalStrength ///< Provides text translation of Wifi signal strength.
{
    amazing = -30, ///< -30 db or more is the best signal strength.
    veryGood = -67, ///< -67 db or more is a good signal strength.
    okay = -70, ///< -70 db is a workable signal strength.
    notGood = -80, ///< -80 db may start to have connection issues. 
    unusable = -90, ///< -90 db or less will make the connection unsuable.     
}; //enum

static const int8_t HOST_NAME_SIZE = 30;  ///< Max size of network name. 

/**
 * The aaSocMicro class provides a single object of authority regarding the 
 * ESP32. Details are collected from both FreeRTOS and the ESP32 Arduino 
 * framework. The information comes from the ESP32's six sub-systems which are 
 * outlined below.
 * 
 * ## Core subsystem
 * 
 * The core subsystem is made up of two CPUs, refered to as COR0 and COR1, as 
 * well as both ROM and RAM memory, referred to as core memory.
 * 
 * ## Wireless subsystem
 * 
 * The wireless subsystem is comprised of WiFi and Bluetooth which share a 
 * common RF send/recieve, clock, switch and balun.
 * 
 * ## RTC subsystem
 * 
 * The Real Time Clock (RTC) subsystem is used by the ESP32 for low power modes. It
 * contains the following: 
 * 
 * 1. The Phasor Measurement Unit (PMU)
 * 2. The small and ultra low power (ULP) 32-bit co-processor
 * 3. 8Kbs of RAM memory known as the recovery memory. 
 * 
 * ## Crytographic Acceleration subsystem
 * 
 * The Cryptograpic Acceleration subsystem provides hardware encrytion acceleration.
 * The following algorithms are supported:
 * 
 * 1. SHA
 * 2. RSA
 * 3. AES
 * 4. RNG 
 * 
 * ## Peripherals subsystem
 * 
 * The Peripherals subsystem handles all of the General Purpose Input/Output (GPIO) 
 * interfaces.
 ************************************************************************************/
class aaSocMicro 
{
   public:
      aaSocMicro(); // First form class constructor.
      aaSocMicro(Print*); // Second form of class constructor.
      aaSocMicro(int, Print*, bool); // Third form of class constructor.
      ~aaSocMicro(); // Class destructor.
      void logResetReason(); // Logs last CPU reset reason for both cores.
      void logSubsystemDetails(); // Logs details of host micro controller.
      void getUniqueName(char&, const char*); // Construct a name that is sure to be unique on the network.
      bool areWeConnected(); // Return flag reporting if we are wifi connected or not.
      void connectWifi(); // Connect to Wifi.
      long rfSignalStrength(int8_t); // Collect an average WiFi signal strength. 
      const char* evalSignal(int16_t); // Return human readable assessment of signal strength.
      bool pingIP(IPAddress); // Ping IP address and return response. Assume 1 ping.
      bool pingIP(IPAddress, int8_t); // Ping IP address and return response. User specified num pings.
      bool configure(); // Configure the SOC.      
   private:
      void _transReasonCode(char&, RESET_REASON); // Translate reset reason codes.
      void _logCoreCPU(); // Logs CPU details inside of the core subsystem.
      void _logCoreMem(); // Logs memory details inside of the core subsystem.
      void _logIntegratedFlash(); // Logs integrated flash details.
      void _logPsramMem(); // Logs PSRAM details.
      void _transFlashModeCode(char&); // Translate flash memory mode code.
      void _logGPIO(); // Logs GPIO details inside of the Peripherals subsystem.
      void _logWireless(); // Logs WiFi and Bluetooth details inside of the Wireless subsystem.
      void _logRTC(); // Logs PMU, ULP and RAM details inside of the RTC subsystem.
      void _logCrypto(); // Logs details inside of the crytographic hardware acceleration subsystem.
      const char* _lookForAP(); // Scan 2.4GHz radio spectrum for known Access Point.
      const char* _translateEncryptionType(wifi_auth_mode_t); // Provide human readable wifi encryption method.
      const char* _connectionStatus(wl_status_t); // Provide human readable text for wifi connection status codes. 
      static void _wiFiEvent(WiFiEvent_t, WiFiEventInfo_t); // Event handler for wifi.
      bool _initBluetooth(); // Initialize the Bluetooth system.
      void _btAddress(char*); // Retrieve Bluetooth address. 
      char* _int32toa(uint32_t, char*); // Format uint32 number.
      const char* _unknownAP = "unknown"; // Comparitor used to check if a valid AP was found.
      const char* _ssid; // SSID of Access Point selected to connect to over Wifi. 
      const char* _password; // Password of Access Point selected to connect to over Wifi.
      aaFormat _convert; // Accept various variable type/formats and return a different variable type/format.
      int8_t _SSIDIndex = 0; // Contains the SSID index number from the known list of APs.
      char _uniqueName[HOST_NAME_SIZE]; // Character array that holds unique name for Wifi network purposes. 
      char *_uniqueNamePtr = &_uniqueName[0]; // Pointer to first address position of unique name character array.
      const char* _HOST_NAME_PREFIX; // Prefix for unique network name. 
}; //class aaSocMicro

#endif // End of precompiler protected code block
