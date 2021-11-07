/*
                  8888888888                   .d8888b.   .d8888b.  888       888                                         .d8888b.   .d8888b.            .d8888b.  
                  888                         d88P  Y88b d88P  Y88b 888   o   888                                        d88P  Y88b d88P  Y88b          d88P  Y88b 
                  888                              .d88P        888 888  d8b  888                                             .d88P        888               .d88P 
 8888b.   8888b.  8888888   .d8888b  88888b.      8888"       .d88P 888 d888b 888 888d888 .d88b.   .d88b.  88888b.d88b.      8888"       .d88P 888  888     8888"  
    "88b     "88b 888       88K      888 "88b      "Y8b.  .od888P"  888d88888b888 888P"  d88""88b d88""88b 888 "888 "88b      "Y8b.  .od888P"  888  888      "Y8b. 
.d888888 .d888888 888       "Y8888b. 888  888 888    888 d88P"      88888P Y88888 888    888  888 888  888 888  888  888 888    888 d88P"      Y88  88P 888    888 
888  888 888  888 888            X88 888 d88P Y88b  d88P 888"       8888P   Y8888 888    Y88..88P Y88..88P 888  888  888 Y88b  d88P 888"        Y8bd8P  Y88b  d88P 
"Y888888 "Y888888 8888888888 88888P' 88888P"   "Y8888P"  888888888  888P     Y888 888     "Y88P"   "Y88P"  888  888  888  "Y8888P"  888888888    Y88P    "Y8888P"  
                                     888                                                                                                                           
                                     888                                                                                                                           
                                     888                                                                                                                           

Part of the Aging Apprentice's Arduino API for ESP32 core.
Github: https://github.com/theAgingApprentice/icUnderware/tree/main/lib/aaEsp32Wroom32v3
Licensed under the MIT License <http://opensource.org/licenses/MIT>.                                                                                                              
*/

#ifndef aaEsp32Wroom32v3_h // Start precompiler code block. 
   #define aaEsp32Wroom32v3_h // Precompiler macro to prevent duplicate inclusions.

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
#include "esp_bt_main.h" // Bluetooth support.
#include "esp_bt_device.h" // Bluetooth support.

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
const int8_t _CORE_CPU_COUNT = 0;
const int8_t _CORE_CPU_MODEL = 1;
const int8_t _CORE_CPU_REVISION = 2;
const int8_t _CORE_CPU_SPEED = 3;
const int8_t _CORE_ROM_SIZE = 4;
const int8_t _CORE_SRAM_TOTAL_SIZE = 5;
const int8_t _CORE_SRAM_STACK_SIZE = 6;
const int8_t _CORE_SRAM_STATIC_SIZE = 7;
const int8_t _CORE_SRAM_STATIC_FREE = 8;
const int8_t _CORE_SRAM_HEAP_SIZE = 9;
const int8_t _CORE_SRAM_HEAP_FREE = 10;
const int8_t _SPI_FLASH_MODE = 11;
const int8_t _SPI_FLASH_SIZE = 12;
const int8_t _SPI_FLASH_SPEED = 13;
const int8_t _SPI_PSRAM_SIZE = 14;
const int8_t _SPI_PSRAM_FREE = 15;
const int8_t _WIRELESS_AP_NAME = 16;
const int8_t _WIRELESS_AP_ENCRYPT_METHOD = 17;
const int8_t _WIRELESS_AP_SIGNAL_STRENGTH  = 18;
const int8_t _WIRELESS_WIFI_MAC = 19;
const int8_t _WIRELESS_WIFI_IP = 20;
const int8_t _WIRELESS_BLUETOOTH_MAC = 21;
const int8_t _RTC_PMU = 22;
const int8_t _RTC_ULP = 24;
const int8_t _RTC_RAM = 25;
const int8_t _CRYPTO_SHA = 26;
const int8_t _CRYPTO_RSA = 27;
const int8_t _CRYPTO_AES = 28;
const int8_t _CRYPTO_RNG = 29;
const int8_t _PERIPHERAL = 30;

/**
 * The aaEsp32Wroom32v3 class provides a single object of authority regarding 
 * the ESP32Wroom32 version 3 SOC. Details are collected from both FreeRTOS and
 * the ESP32 Arduino framework. The information comes from the ESP32's six 
 * sub-systems which are outlined below.
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
class aaEsp32Wroom32v3 
{
   public:
      aaEsp32Wroom32v3(); // First form class constructor.
      aaEsp32Wroom32v3(Print*); // Second form of class constructor.
      aaEsp32Wroom32v3(int, Print*, bool); // Third form of class constructor.
      ~aaEsp32Wroom32v3(); // Class destructor.
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
      bool getSubsystemDetails(uint8_t, char&); // Retrieve SOC subsystem details.      
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
}; //class aaEsp32Wroom32v3

#endif // End of precompiler protected code block
