#include <aaFormat.h> // Header file for linking.

/**
 * @brief This is the first constructor form for this class.
 * @details Instantiating this class using the first form results in the 
 * following defaullt settings.
 * 
 * 1. Logging level = Silent. This means that this class will not send messages 
 * to the log.
 * 2. Logging output goes to the standard Serial interface. 
 * 3. Show Logging level = TRUE. This prefixes a single letter to each log  
 * message that indicates the method used to issue it (e.g. Log.verbose() 
 * messages show up in the logs with a V prepended to them).
 * @param null
 * @return null
 ******************************************************************************/
aaFormat::aaFormat() 
{
   bool showLevel = true; // Prefixed logging output with a single letter level.
   int loggingLevel = LOG_LEVEL_SILENT;
   Print *output = &Serial;
   Log.begin(loggingLevel, output, showLevel); // Set logging parameters. 
   Log.verboseln("<aaFormat::FirstFormConstructor> Logging set to %d.", loggingLevel);
} // aaFormat::aaFormat()

/**
 * @brief This is the destructor for this class.
 * @param null
 * @return null
 ******************************************************************************/
aaFormat::~aaFormat() 
{
   Log.traceln("<aaFormat::~aaFormat> Destructor running.");
} // aaFormat::~aaFormat()

/**
 * @brief Format the devices MAC address.
 * @details Strip the colons out of the MAC address as well as converting it 
 * from String to const char*.
 * @param String MAC address.
 * @return const char* MAC address without colons. 
 ******************************************************************************/
const char* aaFormat::noColonMAC(String macAddress)
{
   macAddress.remove(2, 1); // Remove first colon from MAC address
   macAddress.remove(4, 1); // Remove second colon from MAC address
   macAddress.remove(6, 1); // Remove third colon from MAC address
   macAddress.remove(8, 1); // Remove forth colon from MAC address
   macAddress.remove(10, 1); // Remove fifth colon from MAC address
   return macAddress.c_str();
} // aaFormat::noColonMAC()

/**
 * @brief Convert String to all upper case.
 * @param String Sting to be converted.
 * @return String String in  all upper case. 
 ******************************************************************************/
String aaFormat::stringToUpper(String strToConvert)
{
   std::transform(strToConvert.begin(), strToConvert.end(), strToConvert.begin(), ::toupper);
   return strToConvert;
} // aaFormat::stringToUpper()

/**
 * @brief Convert IPAddress format to String format.
 * @param IPAddress IP address to be converted.
 * @return String Converted IP address. 
 ******************************************************************************/
String aaFormat::ipToString(IPAddress ip)
{
   String s = "";
   for (int i = 0; i < 4; i++)
   {
      s += i ? "." + String(ip[i]) : String(ip[i]);
   } //for
   return s;
} // aaFormat::ipToString()

/**
 * @brief Convert char array containing IP address to byte array.
 * @param const char* IP address to be converted.
 * @param bytes Pointer to byte array into which to place IP address octets. 
 * @return null.
 ******************************************************************************/
void aaFormat::ipToByteArray(const char* str, byte* bytes)
{
   int8_t ipv4NumBytes = 4; // IPv4 has 4 byte address
   int8_t baseNumberingSystem = 10; // IPv4 uses base 10 for its bytes
   char byteSeperator = '.'; // IP address bytes are seperated with a period
   _parseBytes(str, byteSeperator, bytes, ipv4NumBytes, baseNumberingSystem);
} // aaFormat::ipToByteArray()

/**
 * @brief Convert char array containing MAC address to byte array.
 * @param const char* MAC address to be converted.
 * @param bytes Pointer to byte array into which to place MAC address octets. 
 * @return null.
 ******************************************************************************/
void aaFormat::macToByteArray(const char* str, byte* bytes)
{
   int8_t macNumBytes = 6; // MAC addresses have 6 byte addresses
   int8_t baseNumberingSystem = 16; // MAC addresses use base 16 for their bytes
   char byteSeperator = ':'; // MAC address bytes are seperated with a dash
   _parseBytes(str, byteSeperator, bytes, macNumBytes, baseNumberingSystem);
} // aaFormat::macToByteArray()

/**
 * @brief Concatinate two const char* arrays in one buffer.
 * @param const char* First array.
 * @param const char* Second array. 
 * @param const char* pointer to target array in main. 
 * @return null.
 ******************************************************************************/
void aaFormat::joinTwoConstChar(const char *a, const char *b, char *out)
{
   strcpy(out, a);
   strcat(out, b);
} // aaFormat::joinTwoConstChar()

/**
 * @brief Convert char array (ASCII) to byte array.
 * @param const char* .
 * @param char . 
 * @param byte* .
 * @param int8_t . 
 * @param int8_t .  
 * @return null.
 ******************************************************************************/
void aaFormat::_parseBytes(const char* str, char sep, byte* bytes, int8_t maxBytes, int8_t base)
{
   for (int i = 0; i < maxBytes; i++) 
   {
      bytes[i] = strtoul(str, NULL, base); // Convert byte
      str = strchr(str, sep); // Find next separator
      if (str == NULL || *str == '\0') 
      {
         break; // No more separators, exit
      } //if
      str++; // Point to next character after separator
   } //for
} // aaFormat::_parseBytes()