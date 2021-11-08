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
 * Compiler substitution macros.
 ******************************************************************************/
//#define 

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

/**
 * The aaEsp32Wroom32v3 class provides a single object of authority regarding 
 * the ESP32Wroom32 version 3 SOC. Details are collected from both FreeRTOS and 
 * the ESP32 Arduino framework. 
 * 
 * The EP32 is based on a Harvard architecture meaning that there are 
 * two physically separate paths (buses) to access SRAM. The first bus is used 
 * for accessing Instruction Memory (IRAM). IRAM is used for code execution and 
 * text data. It contains:
 * - 32KB cache for CPU0
 * - 32KB cache for CPU1
 * - Interrupt vectors
 * - Text (code binary)
 * - Free IRAM added to the heap 
 * 
 * The second bus is used for accessing Data Memory (DRAM). DRAM handles Block 
 * Started by Symbol (BSS) aka the stack, data aka static data and heap aka the 
 * heap. The Memory Mapping Unit (MMU) takes the total SRAM and maps it to 
 * distinct address locations. These locations are called Static Data, the Heap 
 * and the Stack.
 * 
 * The ESP32 chip's architecture consists of five subsystems.
 * 
 * # The Core subsystem
 * 
 * The ESP32_WROOM_32E core subsystem is comprised of two CPU(s), RAM and ROM.
 * 
 * ## The Core CPUs
 * 
 * The CPUs are Xtensa 32-bit LX6 microprocessors known as core 0 and core 1. 
 * Core0 is used for RF communication. The Arduino binary runs on core 1 by 
 * default though you can pin threads to core 0 in order to run code there.
 *  
 * ## The Core memory
 * 
 * The Core memory comes as both ROM (Read Only Memory) and SRAM
 * (Static Random Access Memory). The ROM contains espressif magic and we 
 * cannot play with that so instead we focus on the SRAM. 
 * 
 * ### SRAM
 * 
 * The internal Core RAM is divided into three memory blocks called SRAM0 
 * (192KB), SRAM1 (128 KB) and SRAM2 (200 KB). SRAM0 and SRAM1 can be used as a 
 * contiguous IRAM whereas SRAM1 and SRAM2 can be used as a contiguous DRAM 
 * address space. While SRAM1 can be used as both IRAM and DRAM, for practical 
 * purposes the Espressif IoT Development Framework (ESP-IDF) uses SRAM1 as 
 * DRAM, as it’s generally the data memory that applications fall short of.
 * 
 * The 192 KB of available IRAM in ESP32 is used for code execution, as well as 
 * part of it is used as a cache memory for flash (and PSRAM) access. 
 * 
 * 1. First 32KB IRAM is used as a CPU0 cache. This is statically configured in 
 * the hardware and can’t be changed.
 * 2. The next 32KB is used as CPU1 cache memory. This is statically configured 
 * in the hardware and can’t be changed.
 * 3. After the first 64KB, the linker script starts placing the text region in 
 * IRAM. It first places all the interrupt vectors and then all the text in the 
 * compiled application that is marked to be placed in IRAM. While in common 
 * case, majority of the application is executed out of the flash (XiP), there 
 * are some portions of the applications which are time critical, or that 
 * operate on flash itself. They need to be placed in IRAM and that is achieved 
 * using a special attribute to these functions or files and linker script doing 
 * a job of placing them in IRAM. The symbols _iram_text_start and 
 * _iram_text_end are placed by the linker script at the two boundaries of this 
 * text section.
 * 4. The IRAM after the text section remains unused and is added to the heap.
 *  
 * _iram_text_start and _iram_text_end symbols are placed by the linker script 
 * at the two boundaries of this text section. The IRAM after the text section 
 * remains unused and is added to the heap. Also, when the application is 
 * configured in a single-core mode, the CPU1 is not functional and CPU1 cache 
 * is unused. In that case, CPU1 cache memory (0x40078000–0x4007FFFF ) is added 
 * to the heap. The unused IRAM, that is placed in the heap, can be accessed 
 * through dynamic allocations. It can be used to place any code in IRAM if the 
 * application has such a requirement. However this is quite uncommon.
 * 
 * The IRAM can also be used for data, but with two important limitations.
 * 1. The address used for access to the data in IRAM has to be 32-bit aligned.
 * 2. The size of data accessed too has to be 32-bit aligned.
 * 
 * If the application has such data that can obey these two rules of accesses, 
 * it can make use of IRAM memory for that data.
 * 
 *  * A typical (simplified) DRAM layout for an application. As the DRAM addresses 
 * start at the end of SRAM2, increasing in backward direction, the link time 
 * segments allocation happens starting at the end of SRAM2.
 * 
 * 1.  The first 8KB (0x3FFA_E000–0x3FFA_FFFF) are used as a data memory for 
 * some of the ROM functions.
 * 2. The linker then places initialised data segment after this first 8KB 
 * memory.
 * 3. Zero initialised BSS segment (the stack) comes next. The memory remaining 
 * after allocating static data and BSS segments (the stack), is configured to 
 * be used as a heap. This is where typical dynamic memory allocations go.
 * 
 * Please note that the size of data and BSS segments (the stack) depend on the 
 * application. So each application, based on the components that it uses and 
 * APIs it calls has a different available heap size to begin with. 
 * 
 * There are two regions within the heap (0x3FFE_0000–0x3FFE_0440 — 1088 bytes) 
 * and (0x3FFE_3F20–0x3FFE_4350–1072 bytes) that are used by ROM code for its 
 * data. These regions are marked reserved and the heap allocator does not 
 * allocate memory from these regions.
 * 
 * Static Data segment is a block of reserved space in SRAM for all the global 
 * and static variables from your program. For variables with initial values, 
 * the runtime system copies the initial value from Flash when the program 
 * starts.
 * 
 * The heap segment is for dynamically allocated data items. The heap grows 
 * from the top of the static data area up as data items are allocated.
 * 
 * The stack (BSS segment) is used for local variables and for maintaining a 
 * record of interrupts and function calls. The stack grows from the top of 
 * memory down towards the heap. Every interrupt, function call and/or local 
 * variable allocation causes the stack to grow. Returning from an interrupt or 
 * function call will reclaim all stack space used by that interrupt or 
 * function. See more at 
 * [this link](https://blog.espressif.com/esp32-programmers-memory-model-259444d89387).
 * 
 * ```
 * NOTE: Most memory problems occur when the stack and the heap collide. When 
 * this happens, one or both of these memory areas will be corrupted with 
 * unpredictable results. In some cases it will cause an immediate crash. In 
 * others, the effects of the corruption may not be noticed until much later.
 * ```
 * 
 * # The Wireless subsystem 
 * 
 * The Wireless subsystem is comprised of WiFi and Bluetooth which share the 
 * following common components:
 *  
 * 1. An RF reciever,
 * 2. An RF transmitter,
 * 3. A clock generator,
 * 4. A switch, and
 * 5. A Balun.    
 *
 * The WiFi standards supported are 802.11 b/g/n/e/i (802.11n @ 2.4 GHz up to 
 * 150 Mbit/s). The Bluetooth standards  supported is v4.2 BR/EDR and Bluetooth 
 * Low Energy (BLE).
 * 
 * ## The RTC
 * 
 * The Real Time Clock (RTC) is comprised of three things:
 * 1. The Phasor measurement unit (PMU), 
 * 2. An Ultra Low Power (ULP) 32-bit co-processor, and 
 * 3. Recovery memory.
 * 
 * The Real Time Clock (RTC) is a minimally viable very low power system that 
 * remains active even when the ESP32 is in hybernation or standby mode. It is
 * comprised of a Phasor Measurement Unit (PMU), a small ultra low power (ULP) 
 * 32-bit co-processor, and 8Kbs of RAM memory known as the recovery memory.  
 * 
 * RTC is able to access some SRAM as well as some GPIO pins (the ones with 
 * capacitive touch capabilities) even when the chip is in non active modes.
 * 
 * ### The ULP coprocessor 
 * 
 * The Ultra Low Power (ULP) coprocessor is a simple Finite State Machine (FSM) 
 * which is designed to perform measurements using the ADC, temperature 
 * sensor, and external I2C sensors, while the main processors are in deep 
 * sleep mode. The ULP coprocessor can access the RTC_SLOW_MEM memory region, 
 * and registers in RTC_CNTL, RTC_IO, and SARADC peripherals. The ULP 
 * coprocessor uses fixed-width 32-bit instructions, 32-bit memory addressing, 
 * and has 4 general-purpose 16-bit registers.
 * 
 * ### Recovery memory
 * 
 * The RTC memory is 8Kbs of RAM known as the recovery memory. The recovery RAM 
 * is area of SRAM which remains powered and accessible to the RTC functions of 
 * the ESP32 microcontroller and the ULP coprocessor even when standby is activated.
 * 
 * ### The PMU
 * 
 * The Phasor measurement unit (PMU) monitors for system events which will wake up 
 * the ESP32 when required.
 *  
 * # The Crytographic Acceleration subsystem 
 * 
 * The crytographic hardware acceleration subsystem supports four hardware 
 * acceleration algorithms:
 * 1. SHA, 
 * 2. RSA, 
 * 3. AES, and
 * 4. RNG.  
 * 
 * # The Peripherals subsystem 
 * 
 * The Peripherals subsystem covers external devices on either the SPI or I2C 
 * bus as well as all of the General Purpose Input/Output (GPIO) pins. Off-chip 
 * SPI memory can be mapped into the available address space as external memory. 
 * Parts of the embedded memory can be used as transparent cache for this 
 * external memory.
 * 
 * 1. Supports up to 16 MB off-Chip SPI Flash.
 * 2. Supports up to 8 MB off-Chip SPI SRAM.
 * 
 * ## Off-chip Flash memory 
 * 
 * Flash memory is used to store your program image and any 
 * initialized data. You can execute program code from flash, but you can't 
 * modify data in flash memory from your executing code. To modify the data, 
 * it must first be copied into SRAM. Flash memory is the same technology used 
 * for thumb-drives and SD cards. It is non-volatile, so your program will 
 * still be there when the system is powered off. Flash memory has a finite 
 * lifetime of about 100,000 write cycles. So if you upload 10 programs a day, 
 * every day for the next 27 years, you might wear it out. The Huzzah32 
 * featherboard does not come with any off-chip Flash memory. 
 * 
 * ## Off-chip PSRAM memory
 * 
 * Off-chip SPI memory can be mapped into the available address space 
 * as external memory. Parts of the embedded memory can be used as transparent 
 * cache for this external memory. The architecture can supports up to 8 MB 
 * off-chip SPI SRAM (PSRAM). The Huzzah32 featherboard does not come with any 
 * PSRAM.
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
   private:
      void _transReasonCode(char&, RESET_REASON); // Translate reset reason codes.
      void _transFlashModeCode(char&); // Translate flash memory mode code.
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
