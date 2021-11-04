/*
                  8888888888                                      888    
                  888                                             888    
                  888                                             888    
 8888b.   8888b.  8888888  .d88b.  888d888 88888b.d88b.   8888b.  888888 
    "88b     "88b 888     d88""88b 888P"   888 "888 "88b     "88b 888    
.d888888 .d888888 888     888  888 888     888  888  888 .d888888 888    
888  888 888  888 888     Y88..88P 888     888  888  888 888  888 Y88b.  
"Y888888 "Y888888 888      "Y88P"  888     888  888  888 "Y888888  "Y888 

Part of the Aging Apprentice's Arduino API for ESP32 core.
Github: https://github.com/theAgingApprentice/icUnderware/tree/main/lib/aaSocMicro
Licensed under the MIT License <http://opensource.org/licenses/MIT>.       
*/

#ifndef aaFormat_h // Start precompiler code block. 

#define aaFormat_h // Precompiler macro used to avoid dupicate inclusion of this code.

/**
 * Included libraries.
 ******************************************************************************/
#include <Arduino.h> // Arduino Core for ESP32. Comes with Platform.io.
#include <ArduinoLog.h> // https://github.com/thijse/Arduino-Log.

/**
 * Global variables.
 ******************************************************************************/
// Put global varables for this class here.

/**
 * The aaFormat class contains methods to convert between various data types.  
 *****************************************************************************/
class aaFormat 
{
   public:
      aaFormat(); // Default constructor for this class.
      ~aaFormat(); // Class destructor.
      const char* noColonMAC(String macAddress); // Returns string of MAC address with no colons in it
      String stringToUpper(String strToConvert); // Retruns string converted to all uppercase
      String ipToString(IPAddress ip); // Returns string of IP address
      void ipToByteArray(const char* str, byte* bytes); // Convert char array containing IP address to byte array
      void macToByteArray(const char* str, byte* bytes); // Convert char array containing MAC address to byte array
      void joinTwoConstChar(const char *a, const char *b, char *out); // Concatinate two const char* arrays  to one buffer.
   private: 
      void _parseBytes(const char* str, char sep, byte* bytes, int8_t maxBytes, int8_t base); // Convert char array (ASCII) to byte array
}; //class aaFormat

extern aaFormat convert; // Expose all public variables and methods for libraries.

#endif // End of precompiler protected code block