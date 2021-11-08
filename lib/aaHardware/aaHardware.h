/*
                  888    888                      888                                        
                  888    888                      888                                        
                  888    888                      888                                        
 8888b.   8888b.  8888888888  8888b.  888d888 .d88888 888  888  888  8888b.  888d888 .d88b.  
    "88b     "88b 888    888     "88b 888P"  d88" 888 888  888  888     "88b 888P"  d8P  Y8b 
.d888888 .d888888 888    888 .d888888 888    888  888 888  888  888 .d888888 888    88888888 
888  888 888  888 888    888 888  888 888    Y88b 888 Y88b 888 d88P 888  888 888    Y8b.     
"Y888888 "Y888888 888    888 "Y888888 888     "Y88888  "Y8888888P"  "Y888888 888     "Y8888  
                                                                                                                                                  
The Aging Apprentice's hardware Arduino API for ESP32.
Github: https://github.com/theAgingApprentice/icUnderware/tree/main/lib/aaHardware
Licensed under the MIT License <http://opensource.org/licenses/MIT>.                                                                                                              
*/

#ifndef aaHardware_h // Start precompiler code block. 
   #define aaHardware_h // Precompiler macro to prevent duplicate inclusions.

/**
 * Compiler substitution macros.
 ******************************************************************************/
#define ESP32_WROOM_32_V3 // SOC chip that comes on the Adafruit Huzzah32. 
// #define someOtherChip // No second MCU currently supported.
// #define yetAnotherChip // No second MCU currently supported.

/**
 * Included libraries.
 ******************************************************************************/
#include <Arduino.h> // Arduino Core for ESP32. Comes with Platform.io.
#include <ArduinoLog.h> // https://github.com/thijse/Arduino-Log.
#ifdef ESP32_WROOM_32_V3 
   #include <aaEsp32Wroom32v3.h> 
#endif // ESP32_WROOM_32_V3
#ifdef someOtherChip
   #include <someOtherChip.h>
#endif // someOtherChip
#ifdef yetAnotherChip
   #include <yetAnotherChip.h>
#endif // yetAnotherChip 

/**
 * Global variables.
 ******************************************************************************/

/**
 * The aaHardware class provides a single object of authority regarding the 
 * hardware that underlies your ESP32 embedded Arduino appication.  The 
 * hardware is imagined as follows:
 * 
 * # MCU 
 * 
 * All hardware is under the control of the Micro Controller Unit (MCU) via
 * the I2C bus or a GPIO pin. The icUnderware project currenty only supports the
 * ESP32_WROOM_32_V3 SOC and does not support the SPI bus.
 * 
 * # Main PCB 
 * 
 * The main PCB has the MCU and all of its usable pins broken out for easy 
 * access. The Adafruit Huzzah32 is the only development board that is 
 * currently supported.  
 * 
 * # Onboard controls
 * 
 * Buttons and switches mounted on the project platform.
 *
 * # Ongoard Indicators
 * 
 * LEDs used to indicate status information at a glance.
 * 
 * # Onboard diplays
 * 
 * OLED or LCDs used to provide detailed information or add other visually 
 * fun things like facial expressions.  
 ******************************************************************************/
class aaHardware 
{
   public:
      aaHardware(); // First form class constructor.
      aaHardware(Print*); // Second form of class constructor.
      aaHardware(int, Print*, bool); // Third form of class constructor.
      ~aaHardware(); // Class destructor.
      void start(); // Initialize the application hardware.
      const unsigned long SERIAL_BAUD_RATE = 115200;
      const char* APP_NAME = "APP_NAME"; // Put the name of your app here.
      char uniqueName[40]; // Unique name safe to use for  MQTT topic trees.
      #ifdef ESP32_WROOM_32_V3
         aaEsp32Wroom32v3 MCU;
      #endif // ESP32_WROOM_32_V3 
      #ifdef someOtherChip
         someOtherChip MCU;
      #endif // someOtherChip
      #ifdef yetAnotherChip
         yetAnotherChip MCU
      #endif // yetAnotherChip 
   private:
}; //class aaHardware

#endif // End of precompiler protected code block