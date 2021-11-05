#include <aaSocMicro.h> // Header file for linking.

/**
 * @fn aaSocMicro::aaSocMicro()
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
 * @param null.
 * @return null.
 ******************************************************************************/
aaSocMicro::aaSocMicro()
{
   bool showLevel = true; // Prefixed logging output with a single letter level.
   int loggingLevel = LOG_LEVEL_SILENT;
   Print *output = &Serial;
   Log.begin(loggingLevel, output, showLevel); // Set logging parameters. 
   Log.verboseln("<aaSocMicro::FirstFormConstructor> Logging set to %d.", loggingLevel);
} //aaSocMicro::aaSocMicro()

/**
 * @overload aaSocMicro::aaSocMicro(Print* output)
 * @brief This is the second constructor form for this class.
 * @details Instantiating this class using the second form results in the 
 * following default settings.
 * 
 * 1. Logging level = Silent. This means that this class will not send messages 
 * to the log.
 * 2. Logging output goes wherever you specified with the output parameter. 
 * 3. Show Logging level = TRUE. This prefixes a single letter to each log  
 * message that indicates the method used to issue it (e.g. Log.verbose() 
 * messages show up in the logs with a V prepended to them).
 * @param output class that handles bit stream input.
 * @return null
 ******************************************************************************/
aaSocMicro::aaSocMicro(Print* output)
{
   bool showLevel = true; // Prefixed logging output with a single letter level.
   int loggingLevel = LOG_LEVEL_SILENT;
   Log.begin(loggingLevel, output, showLevel); // Set logging parameters. 
   Log.traceln("<aaSocMicro::SecondFormConstructor> Logging set to %d.", loggingLevel);
} //aaSocMicro::aaSocMicro()

/**
 * @overload aaSocMicro::aaSocMicro(int loggingLevel, Print* output, bool showLevel)
 * @brief This is the third constructor form for this class.
 * @details Instantiating this class using the third form results in you
 * controlling all Logging behavior for this class.
 * @param loggingLevel is one of 6 predefined levels from the Logging library.
 * @param output is a class that can handle bit stream input (e.g. Serial).
 * @param showLevel prefixs log message with the Logging level letter when TRUE.
 * @return null
 ******************************************************************************/
aaSocMicro::aaSocMicro(int loggingLevel, Print* output, bool showLevel)
{
   Log.begin(loggingLevel, output, showLevel); // Set logging parameters. 
   Log.traceln("<aaSocMicro::ThirdFormConstructor> Logging set to %d.", loggingLevel);
} //aaSocMicro::aaSocMicro()

/**
 * @brief This is the destructor for this class.
 * @param null
 * @return null
 ******************************************************************************/
aaSocMicro::~aaSocMicro()
{
   Log.traceln("<aaSocMicro::~aaSocMicro> Destructor running.");
} //aaSocMicro::~aaSocMicro()

/**
 * @brief Translates a CPU reset reason code to a human readable string.
 * @details This class populates &reason with text that is accesible to the 
 * calling code. These codes are as follows:
 *
 * 1. POWERON_RESET. Vbat power on reset.
 * 3. SW_RESET. Software reset digital core.
 * 4. OWDT_RESET. Legacy watch dog reset digital core.
 * 5. DEEPSLEEP_RESET. Deep Sleep reset digital core.
 * 6. SDIO_RESET. Reset by SLC module, reset digital core.
 * 7. TG0WDT_SYS_RESET. Timer Group0 Watch dog reset digital core.
 * 8. TG1WDT_SYS_RESET. Timer Group1 Watch dog reset digital core.
 * 9. RTCWDT_SYS_RESET. RTC Watch dog Reset digital core.
 * 10. INTRUSION_RESET. Instrusion tested to reset CPU.
 * 11. TGWDT_CPU_RESET. Time Group reset CPU.
 * 12. SW_CPU_RESET. Software reset CPU.
 * 13. RTCWDT_CPU_RESET. RTC Watch dog Reset CPU.
 * 14. EXT_CPU_RESET. For APP CPU, reset by PRO CPU.
 * 15. RTCWDT_BROWN_OUT_RESET. Reset when the vdd voltage is not stable.
 * 16. RTCWDT_RTC_RESET. RTC Watch dog reset digital core and rtc module.
 *  
 * @param reason is the address to put the reason code.
 * @param code is the nuerica reset value reported by the CPU. 
 * @return null. 
 ******************************************************************************/
void aaSocMicro::_transReasonCode(char& reason, RESET_REASON code)
{
   switch(code)
   {
      case 1: strcpy(&reason, "1. Vbat power on reset."); break; 
      case 3: strcpy(&reason, "3. Software reset digital core."); break; 
      case 4: strcpy(&reason, "4. Legacy watch dog reset digital core."); break; 
      case 5: strcpy(&reason, "5. Deep Sleep reset digital core."); break; 
      case 6: strcpy(&reason, "6. Reset by SLC module, reset digital core."); break; 
      case 7: strcpy(&reason, "7. Reset by SLC module, reset digital core."); break; 
      case 8: strcpy(&reason, "8. Timer Group1 Watch dog reset digital core."); break; 
      case 9: strcpy(&reason, "9. RTC Watch dog Reset digital core."); break;  
      case 10: strcpy(&reason, "10. Instrusion tested to reset CPU."); break;  
      case 11: strcpy(&reason, "11. Time Group reset CPU."); break; 
      case 12: strcpy(&reason, "12. Software reset CPU."); break; 
      case 13: strcpy(&reason, "13. RTC Watch dog Reset CPU."); break; 
      case 14: strcpy(&reason, "14. For APP CPU, reset by PRO CPU."); break; 
      case 15: strcpy(&reason, "15. Reset when the vdd voltage is not stable."); break; 
      case 16: strcpy(&reason, "16. RTC Watch dog reset digital core and rtc module."); break; 
      default: strcpy(&reason, "UNKNOWN"); break; 
   } // switch()
} // aaSocMicro::_translateReasonCode()

/**
 * @brief Sends human readable reset reason for both cores to the log.
 * @param null.
 * @return null.
 ******************************************************************************/
void aaSocMicro::logResetReason()
{
   char _reason[20]; // Text version of last reset reason code.
   for(int8_t i=0; i < ESP.getChipCores(); i++)
   {
      _transReasonCode(*_reason, rtc_get_reset_reason(i));
      Log.noticeln("<logResetReason> new CPU%d reset reason = %s", i, _reason);
   } // for
} // aaSocMicro::logResetReason()

/**
 * @brief Sends details about the host micro controller to the log.
 * @details Inside the ESP32 chip is the following architecture:
 * - Core subsystem. Comprised of CPU(s), RAM and ROM.
 * - Wireless subsystem. Comprised of WiFi and Bluetooth which share a common
 * RF send/recieve, clock, switch and balun. 
 * - RTC subsystem inside of which are a PMU (Phasor measurement unit), a small 
 * and ultra low power (ULP) 32-bit co-processor, and 8Kbs of RAM memory known 
 * as the recovery memory. 
 * - Crytographic Acceleration subsystem which supports SHA, RSA, AES and RNG 
 * hardware acceleration.
 * - Peripherals subsystem that handles all of the General Purpose Input/Output 
 * (GPIO) interfaces.
 * @param null.
 * @return null.
 ******************************************************************************/
void aaSocMicro::logSubsystemDetails()
{
   _logCoreCPU();
   _logCoreMem();
   _logIntegratedFlash();
   _logPsramMem();
   _logWireless();
   /// @todo #45 add _logGpio() to aaSocMicro.
} // aaSocMicro::logSubsystemDetails()

/**
 * @brief Sends details about the core CPU(s) to the log.
 * @details The ESP32_WROOM_32E comes with 2 Xtensa 32-bit LX6 microprocessors 
 * known as core 0 and core 1. Core0 is used for RF communication. The Arduino 
 * binary runs on core 1 by default though you can pin threads to core 0 in 
 * order to run code there.
 * 
 * - Ultra Low Power (ULP) coprocessor is a simple Finite State Machine (FSM) 
 * which is designed to perform measurements using the ADC, temperature 
 * sensor, and external I2C sensors, while the main processors are in deep 
 * sleep mode. The ULP coprocessor can access the RTC_SLOW_MEM memory region, 
 * and registers in RTC_CNTL, RTC_IO, and SARADC peripherals. The ULP 
 * coprocessor uses fixed-width 32-bit instructions, 32-bit memory addressing, 
 * and has 4 general-purpose 16-bit registers.
 * - Real time  clock (RTC). The ESP32 processor has a very low power real time 
 * subsystem called RTC which remains active even when it is in standby. RTC is 
 * able to access some SRAM aswell as some GPIO pins (the ones with capacitive 
 * touch capabilities) even when the chip is in non active modes.
 * @param null.
 * @return null.
 ******************************************************************************/
void aaSocMicro::_logCoreCPU()
{
   Log.noticeln("<aaSocMicro::_logCoreCPU> Core CPU details.");
   Log.noticeln("<aaSocMicro::_logCoreCPU> ... CPU Count = %d", ESP.getChipCores());
   Log.noticeln("<aaSocMicro::_logCoreCPU> ... CPU Model = %s", ESP.getChipModel());
   Log.noticeln("<aaSocMicro::_logCoreCPU> ... CPU Revision = %d", ESP.getChipRevision());
   Log.noticeln("<aaSocMicro::_logCoreCPU> ... CPU clock speed = %uMhz", ESP.getCpuFreqMHz());
} // aaSocMicro::_logCoreCPU()

/**
 * @brief Sends details about the core memory to the log.
 * @details The ESP32 core subsystem contains ROM (Read Only Memory) and SRAM
 * (Static Random Access Memory). The ROM contains espressif magic and we 
 * cannot play with that so instead we focus on the SRAM. 
 * 
 * ## SRAM
 * 
 * The internal RAM layout of the ESP32 is made up of three memory blocks 
 * called SRAM0 (192KB), SRAM1 (128 KB) and SRAM2 (200 KB). SRAM0 and SRAM1 
 * can be used as a contiguous IRAM whereas SRAM1 and SRAM2 can be used as a 
 * contiguous DRAM address space. While SRAM1 can be used as both IRAM and 
 * DRAM, for practical purposes the Espressif IoT Development Framework 
 * (ESP-IDF) uses SRAM1 as DRAM, as it’s generally the data memory that 
 * applications fall short of.
 * 
 * The EP32 is based on a Harvard architecture meaning that there are two 
 * physically separate paths (buses) to access SRAM. 
 * 
 * 1. The first bus is used for accessing Instruction memory (IRAM). IRAM is 
 * used for code execution and text data. It contains
 *    - 32KB cache for CPU0
 *    - 32KB cache for CPU1
 *    - Interrupt vectors
 *    - Text (code binary)
 *    - Free IRAM added to the heap 
 * 2. The second bus is used for accessing Data (DRAM). DRAM handles 
 * Block started by symbol (BSS) aka the stack, data aka static data and 
 * heap aka the heap. The Memory Mapping Unit (MMU) takes the total SRAM and 
 * maps it to distinct address locations. These locations are called Static 
 * Data, the Heap and the Stack (BSS).
 * 
 * ### IRAM   
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
 * a job of placing them in IRAM. The symbols _iram_text_start and _iram_text_end 
 * are placed by the linker script at the two boundaries of this text section.
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
 * ### DRAM    
 * 
 * A typical (simplified) DRAM layout for an application. As the DRAM addresses 
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
 * ### RTC Memory
 * 
 * The RTC (Real Time Clock) memory is an area of the processor SRAM which 
 * remains powered and accessible to the RTC functions of the ESP32 
 * microcontroller and the ULP coprocessor even when standby is activated.
 * 
 * ### External Memory
 * 
 * Off-chip SPI memory can be mapped into the available address space as 
 * external memory. Parts of the embedded memory can be used as transparent 
 * cache for this external memory.
 * 
 * 1. Supports up to 16 MB off-Chip SPI Flash.
 * 2. Supports up to 8 MB off-Chip SPI SRAM.
 * 
 * @param null.
 * @return null.
 * @todo: #4 Implement monitoring of heap and stack to detect potential SRAM 
 * corruption. 
 ******************************************************************************/
void aaSocMicro::_logCoreMem()
{
   const uint32_t STATIC_DATA_SIZE = ESP.getSketchSize() + ESP.getFreeSketchSpace();
   const uint32_t SRAM_SIZE = STATIC_DATA_SIZE + ESP.getHeapSize() + uxTaskGetStackHighWaterMark(NULL);

   Log.noticeln("<aaSocMicro::_logCoreMem> Core memory details.");
   Log.noticeln("<aaSocMicro::_logCoreMem> ... ROM contains Espressif code and we do not touch that.");
   Log.noticeln("<aaSocMicro::_logCoreMem> ...... ROM size = %u bytes.", XSHAL_ROM_SIZE);
   Log.noticeln("<aaSocMicro::_logCoreMem> ... SRAM is the binarys read/write area.");
   Log.noticeln("<aaSocMicro::_logCoreMem> ...... Total SRAM size (stack + heap + static data) = %u bytes.", SRAM_SIZE);
   Log.noticeln("<aaSocMicro::_logCoreMem> ...... The Stack contains local variables, interrupt and function pointers.");
   Log.noticeln("<aaSocMicro::_logCoreMem> ......... Stack highwater mark = %u bytes", uxTaskGetStackHighWaterMark(NULL));
   Log.noticeln("<aaSocMicro::_logCoreMem> ...... Static memory (aka sketch memory) is allocated at compile time and contains global and static variables.");
   Log.noticeln("<aaSocMicro::_logCoreMem> ......... Static data size = %u bytes.", STATIC_DATA_SIZE);
   Log.noticeln("<aaSocMicro::_logCoreMem> ......... Sketch size = %u bytes.", ESP.getSketchSize());
   Log.noticeln("<aaSocMicro::_logCoreMem> ......... Free sketch space = %u bytes.", ESP.getFreeSketchSpace());
   Log.noticeln("<aaSocMicro::_logCoreMem> ...... The Heap contains dynamic data.");
   Log.noticeln("<aaSocMicro::_logCoreMem> ......... Heap size = %u bytes.", ESP.getHeapSize());
   Log.noticeln("<aaSocMicro::_logCoreMem> ......... Free heap = %u bytes.", ESP.getFreeHeap());
} // aaSocMicro::_logCoreMem()

/**
 * @brief Translates a flash memory mode code to a human readable string.
 * @details The ESP32 MCU supports the following FLASH memory modes:
 * 0. FM_QIO - SPI host uses the "Quad I/O Fast Read" command (EBh). Four SPI 
 * pins are used to write the flash address part of the command, and to read 
 * flash data out. Therefore these phases need a quarter the clock cycles 
 * compared to standard SPI.
 * 1. FM_QOUT - SPI host uses the "Quad Output Fast Read" command (6Bh). Four
 * SPI pins are used to read the flash data out. Slightly slower than QIO, 
 * because the address is written via the single MOSI data pin.
 * 2. FM_DIO - SPI host uses the "Dual I/O Fast Read" command (BBh). Two SPI 
 * pins are used to write the flash address part of the command, and to read 
 * flash data out. Therefore these phases need half the clock cycles compared 
 * to standard SPI.
 * 3. FM_DOUT - SPI host uses the "Dual Output Fast Read" command (3Bh). Two 
 * SPI pins are used to read flash data out. Slightly slower than DIO, because 
 * the address is written via the single MOSI data pin. 
 * 4. FM_FAST_READ - Have not found definition.
 * 5. FM_SLOW_READ - Have not found definition.
 * 255. FM_UNKNOWN - Unknown mode. 
 * @param null.
 * @return null.
 ******************************************************************************/
void aaSocMicro::_transFlashModeCode(char& details)
{
   switch(ESP.getFlashChipMode())
   {
      case FM_QIO: strcpy(&details, "0 (FM_QIO) - Quad I/O Fast Read. Address written via four data pins."); break;
      case FM_QOUT: strcpy(&details, "1 (FM_QOUT) - Quad I/O Fast Read. Address written via the single MOSI data pin."); break;
      case FM_DIO: strcpy(&details, "2 (FM_DIO) - Dual I/O Fast Read. Address written via two SPI pins."); break;
      case FM_DOUT: strcpy(&details, "3 (FM_DIO) - Dual I/O Fast Read. Address written via single MOSI data pin."); break;
      case FM_FAST_READ: strcpy(&details, "4 (FM_FAST_READ) - Unknown details."); break;
      case FM_SLOW_READ: strcpy(&details, "5 (FM_SLOW_READ) - Unknown details."); break;
      default: strcpy(&details, "UNKNOWN MODE."); break; 
   } // switch()
} // aaSocMicro::_transFlashModeCode()

/**
 * @brief Sends details about the integrated flash memory to the log.
 * @details Flash memory is used to store your program image and any 
 * initialized data. You can execute program code from flash, but you can't 
 * modify data in flash memory from your executing code. To modify the data, 
 * it must first be copied into SRAM. Flash memory is the same technology used 
 * for thumb-drives and SD cards. It is non-volatile, so your program will 
 * still be there when the system is powered off. Flash memory has a finite 
 * lifetime of about 100,000 write cycles. So if you upload 10 programs a day, 
 * every day for the next 27 years, you might wear it out. 
 * 
 * Off-chip SPI memory can be mapped into the available address space 
 * as external memory. Parts of the embedded memory can be used as transparent 
 * cache for this external memory. The architecture can supports up to 16 MB 
 * off-chip SPI Flash. The Huzzah32 featherboard does not come with any 
 * off-chip SPI Flash memory. 
 * @param null.
 * @return null.
 ******************************************************************************/
void aaSocMicro::_logIntegratedFlash()
{
   char _details[80]; // Text version of flash memory mode.
   Log.noticeln("<aaSocMicro::_logIntegratedFlash> Flash memory details (Arduino binary resides here).");
   _transFlashModeCode(*_details);
   Log.noticeln("<aaSocMicro::_logIntegratedFlash> ... Flash mode = %s", _details);
   Log.noticeln("<aaSocMicro::_logIntegratedFlash> ... Flash chip size = %u", ESP.getFlashChipSize());
   Log.noticeln("<aaSocMicro::_logIntegratedFlash> ... Flash chip speed = %u", ESP.getFlashChipSpeed());
} // aaSocMicro::_logIntegratedFlash()

/**
 * @brief Sends details about the external Pseudo Static RAM memory to the log.
 * @details Off-chip SPI memory can be mapped into the available address space 
 * as external memory. Parts of the embedded memory can be used as transparent 
 * cache for this external memory. The architecture can supports up to 8 MB 
 * off-chip SPI SRAM (PSRAM). The Huzzah32 featherboard does not come with any 
 * PSRAM.
 * @param null.
 * @return null.
 ******************************************************************************/
void aaSocMicro::_logPsramMem()
{
   Log.traceln("<aaSocMicro::_logPsramMem> PSRAM is optional external RAM accessed via the SPI bus.");
   if(psramFound()) // Is SPI RAM (psudo ram) available?
   {
      Log.noticeln("<aaSocMicro::_logPsramMem> ... PSRAM detected.");
      Log.noticeln("<aaSocMicro::_logPsramMem> ... PSRAM size = %u", ESP.getPsramSize());
      Log.noticeln("<aaSocMicro::_logPsramMem> ... Free PSRAM = %u", ESP.getFreePsram());
   } // if
   else
   {
      Log.noticeln("<aaSocMicro::_logPsramMem> ... No PSRAM detected.");
   } // else   
} // aaSocMicro::_logPsramMem()

/**
 * @brief Sends details about the Wireless system to the log.
 * @details The ESP32_WROOM_32E supports two Wireless connectivity options:
 * 1. WiFi: 802.11 b/g/n/e/i (802.11n @ 2.4 GHz up to 150 Mbit/s).
 * 2. Bluetooth: v4.2 BR/EDR and Bluetooth Low Energy (BLE).
 * 
 * Bluetooth and WiFi share the same radio comprised of:
 * 1. An RF reciever,
 * 2. An RF transmitter,
 * 3. A clock generator,
 * 4. A switch, and
 * 5. A Balun.    
 * @param null.
 * @return null.
 ******************************************************************************/
void aaSocMicro::_logWireless()
{
   wifi_auth_mode_t encryption = WiFi.encryptionType(_SSIDIndex);
   int8_t _dataReadings = 10; // Number of data readings to average to determine Wifi signal strength.
   long _signalStrength = rfSignalStrength(_dataReadings); // Get average signal strength reading.
   char _bluetoothAddress[30]; // Hold Bluetooth address in a character array.
   _btAddress(_bluetoothAddress); // Copy formatted Bluetooth address into the character array.
   Log.noticeln("<aaSocMicro::_logWireless> Wireless details."); 
   Log.noticeln("<aaSocMicro::_logWireless> ... WiFi."); 
   Log.noticeln("<aaSocMicro::_logWireless> ...... Access Point Name = %s.",WiFi.SSID().c_str()); 
   Log.noticeln("<aaSocMicro::_logWireless> ...... Access Point Encryption method = %X (%s).", encryption, _translateEncryptionType(WiFi.encryptionType(encryption)));
   Log.noticeln("<aaSocMicro::_logWireless> ...... Wifi signal strength = %u (%s).", _signalStrength, evalSignal(_signalStrength));
   Log.noticeln("<aaSocMicro::cfgToConsole> ...... Local Wifi MAC address: %s.", WiFi.macAddress().c_str());
   Log.noticeln(F("<aaSocMicro::cfgToConsole> ...... Local WiFi IP address: %p."), WiFi.localIP()); 
   Log.noticeln("<aaSocMicro::_logWireless> ... Bluetooth."); 
   Log.noticeln("<aaSocMicro::cfgToConsole> ...... Local bluetooth MAC address: %s.", _bluetoothAddress); 
} // aaSocMicro::_logWireless()

/**
 * @brief Report the status of the wifi connection.
 * @param null.
 * @return bool true when connected, false when any other status.
 ******************************************************************************/
bool aaSocMicro::areWeConnected()
{ 
   if(WiFi.status() == WL_CONNECTED)
   {
      return true;
   } // if
   else
   {
      return false;
   } // else
} // aaSocMicro::areWeConnected()

/**
 * @brief Construct a name that is sure to be unique on the network.
 * @details Tis function concatintes a prefix defined in the main program with
 * the MAC address of the SOC creating a unique name to be used for network
 * related activities such as prefixing MQTT broker topic names etc. 
 * @param targetArray address of char array into which we place the name.
 * @param prefix Characters that make up the first half of the name.
 * @return null.
 ******************************************************************************/
void aaSocMicro::getUniqueName(char& targetArray, const char* prefix)
{ 
   String macAdd = WiFi.macAddress(); // MAC address with colons.
   macAdd.replace(":",""); // Strip out colons.
   strcpy(&targetArray, prefix); // Copy prefix to unique name.
   strcat(&targetArray, macAdd.c_str());
} // aaSocMicro::getUniqueName()

/**
 * @brief Provide human readable text for wifi connection status codes.
 * @param wl_status_t wifi connection status code.
 * @return bool true when connected, false when any other status.
 ******************************************************************************/
const char* aaSocMicro::_connectionStatus(wl_status_t status)
{
   switch(status) 
   {
      case WL_NO_SHIELD: return "WL_NO_SHIELD"; // For WiFi Shield library.
      case WL_IDLE_STATUS: return "WL_IDLE_STATUS";
      case WL_NO_SSID_AVAIL: return "WL_NO_SSID_AVAIL";
      case WL_SCAN_COMPLETED: return "WL_SCAN_COMPLETED";
      case WL_CONNECTED: return "WL_CONNECTED";
      case WL_CONNECT_FAILED: return "WL_CONNECT_FAILED";
      case WL_CONNECTION_LOST: return "WL_CONNECTION_LOST";
      case WL_DISCONNECTED: return "WL_DISCONNECTED";
      default: return "UNKNOWN_STATUS";
   } //switch
} // aaSocMicro::_connectionStatus()

/**
 * @brief Configure the SOC.
 * @details Set up the SOC based on the configuration structure passed by 
 * reference.  
 * @param wl_status_t wifi connection status code.
 * @return bool true when connected, false when any other status.
 * @todo #43 Create config structure and pass a pointer to it during configuration.
 ******************************************************************************/
bool aaSocMicro::configure()
{
   connectWifi(); // Establish WiFi connection.
   _initBluetooth(); // Initialize Bluetooth radio.
   return true;
} // aaSocMicro::configure()

/**
 * @brief Connect to Wifi.
 * @param null.
 * @return null.
 ******************************************************************************/
void aaSocMicro::connectWifi()
{
   if(_lookForAP() == _unknownAP) // Scan the 2.4Ghz band for known Access Points and select the one with the strongest signal 
   {
      Log.verboseln("<aaSocMicro::connect> No known Access Point SSID was detected. Cannot connect to WiFi at this time.");
   } // if
   else // Found a known Access Point to connect to
   {
      WiFi.onEvent(_wiFiEvent); // Set up WiFi event handler
      WiFi.begin(_ssid, _password); // Connect too strongest AP found
      Log.verboseln("<aaSocMicro::connect> Attempting to connect to Access Point with the SSID %s." , _ssid);
      while(WiFi.waitForConnectResult() != WL_CONNECTED) // Hold boot process here until IP assigned
      {
         delay(500);
      } //while
      Log.verboseln("<aaSocMicro::connect> Connected to Access Point with the SSID %s with status code %u (%s).", _ssid, WiFi.status(), _connectionStatus(WiFi.status()));
   } //else
} // aaSocMicro::connect()

/**
 * @brief Collect an average WiFi signal strength. 
 * @param int8_t Number of datapoints to use to create average. 
 * @return long Average signal strength of AP connection in decibels (db).
 ******************************************************************************/
long aaSocMicro::rfSignalStrength(int8_t dataPoints)
{
   long rssi = 0;
   long averageRSSI = 0;
   for(int i=0; i < dataPoints; i++)
   {
      rssi += WiFi.RSSI();
      delay(20);
   } //for
   averageRSSI = rssi / dataPoints;
   return averageRSSI;
} // aaSocMicro::rfSignalStrength()

/**
 * @brief Return human readable assessment of signal strength.
 * @param int16_t Signal strength as measured in decibels (db). 
 * @return const char* Assessment of signal quality in one or two words.
 ******************************************************************************/
const char* aaSocMicro::evalSignal(int16_t signalStrength)
{
   if(signalStrength <= unusable) return "Unusable";
   if(signalStrength <= notGood) return "Not good";
   if(signalStrength <= okay) return "Okay";
   if(signalStrength <= veryGood) return "Very Good";
   return "Amazing";
} // aaSocMicro::evalSignal()

/**
 * @fn bool aaSocMicro::pingIP(IPAddress address)
 * @brief Ping IP address once and return the response.
 * @param IPAddress Address to ping. 
 * @return bool Result of ping. 
 ******************************************************************************/
bool aaSocMicro::pingIP(IPAddress address)
{
   int8_t numPings = 1; // How many pings to send to verify IP address
   IPAddress tmpIp; 
   return Ping.ping(address, numPings);
} // aaSocMicro::pingIP()

/**
 * @overload bool aaSocMicro::pingIP(IPAddress address, int8_t numPings)
 * @brief Ping IP address usert specified number of times and return response.
 * @param IPAddress Address to ping. 
 * @param int8_t Number of times to ping address. 
 * @return bool Result of pings. 
 ******************************************************************************/
bool aaSocMicro::pingIP(IPAddress address, int8_t numPings)
{
   IPAddress tmpIp; 
   return Ping.ping(address, numPings);
} // aaSocMicro::pingIP()

/**
 * @brief Scan 2.4GHz radio spectrum for known Access Point.
 * @param null.
 * @return const char* Service Set IDentifier (SSID). 
 ******************************************************************************/
const char* aaSocMicro::_lookForAP()
{
   _ssid = _unknownAP; //  At the start no known Access Point has been foundto connect to
   int numberOfNetworks = WiFi.scanNetworks(); // Used to track how many APs are detected by the scan
   int StrongestSignal = -127; // Used to find the strongest signal. Set as low as possible to start
   bool APknown; // Flag to indicate if the current AP appears in the known AP list
   Log.verboseln("<aaSocMicro::_lookForAP> Scanning the 2.4GHz radio spectrum for one of the %d known Access Points.", numberOfNetworks);

   // Loop through all detected APs
   for(int i = 0; i < numberOfNetworks; i++)
   {
      APknown = false;
   
      // Scan table of known APs to see if the current AP is known to us
      for (int j = 0; j < numKnownAPs; j++)
      {
         // If the current scanned AP appears in the known AP list note the index value and flag found
         if(WiFi.SSID(i) == SSID[j])
         {
            APknown = true;
            _SSIDIndex = j;
         } //if
      }   //for

      // If the current AP is known and has a stronger signal than the others that have been checked
      // then store it in the variables that will be used to connect to the AP later
      if((APknown == true) && (WiFi.SSID(i).toInt() > StrongestSignal))
      {
         _ssid = SSID[_SSIDIndex].c_str();
         _password = Password[_SSIDIndex].c_str();
         StrongestSignal = WiFi.SSID(i).toInt();
      } //if
   } //for
   return _ssid;
} // aaSocMicro::_lookForAP()

/**
 * @brief Provide human readable Wifi encryption method.
 * @details Wifi encryptions options are:
 * 1. OPEN
 * 2. WEP
 * 3. WPA_PSK
 * 4. WPA2_PSK
 * 5. WPA_WPA2_PSK
 * 6. WPA2_ENTERPRISE
 * @param wifi_auth_mode_t Wifi encryption type code.
 * @return const char* Encryption type in one word. 
 ******************************************************************************/
const char* aaSocMicro::_translateEncryptionType(wifi_auth_mode_t encryptionType)
{
   switch (encryptionType)
   {
      case (WIFI_AUTH_OPEN): return "Open";
      case (WIFI_AUTH_WEP): return "WEP";
      case (WIFI_AUTH_WPA_PSK): return "WPA_PSK";
      case (WIFI_AUTH_WPA2_PSK): return "WPA2_PSK";
      case (WIFI_AUTH_WPA_WPA2_PSK): return "WPA_WPA2_PSK";
      case (WIFI_AUTH_WPA2_ENTERPRISE): return "WPA2_ENTERPRISE";
      default: return "UNKNOWN";
   } //switch
} // aaSocMicro::_translateEncryptionType()

/**
 * @brief Event handler for wifi.
 * @details Tracks all wifi event activity even though we do not act on any of 
 * it at this time. At the very least the logs help us trouble shoot wifi issues 
 * but this routine also acts as a reminder of what functional possibilities 
 * exist for future consideration.
 * @param WiFiEvent_t Type of event that triggered this handler.
 * @param WiFiEventInfo_t Additional information about the triggering event.
 ******************************************************************************/
void aaSocMicro::_wiFiEvent(WiFiEvent_t event, WiFiEventInfo_t info)
{
   switch(event) 
   {
      case SYSTEM_EVENT_AP_START:
//         WiFi.softAP(AP_SSID, AP_PASS); //can set ap hostname here   
//         WiFi.softAPenableIpV6(); //enable ap ipv6 here
         Log.verboseln("<aaSocMicro::WiFiEvent> Detected SYSTEM_EVENT_AP_START");            
         break;
      case SYSTEM_EVENT_STA_START:         
//         WiFi.setHostname(AP_SSID); //set sta hostname here
         Log.verboseln("<aaSocMicro::WiFiEvent> Detected SYSTEM_EVENT_STA_START");            
         break;
      case SYSTEM_EVENT_STA_CONNECTED:         
//         WiFi.enableIpV6(); //enable sta ipv6 here
         Log.verboseln("<aaSocMicro::WiFiEvent> Detected SYSTEM_EVENT_STA_CONNECTED");            
         break;
      case SYSTEM_EVENT_AP_STA_GOT_IP6:
         Log.verboseln("<aaSocMicro::WiFiEvent> Detected SYSTEM_EVENT_AP_STA_GOT_IP6");            
         break;
      case SYSTEM_EVENT_STA_GOT_IP:
//         wifiOnConnect(); // Call function to do things dependant upon getting wifi connected
         Log.verboseln("<aaSocMicro::WiFiEvent> Detected SYSTEM_EVENT_STA_GOT_IP");            
         break;
      case SYSTEM_EVENT_STA_DISCONNECTED:
         Log.verboseln("<aaSocMicro::WiFiEvent> Detected SYSTEM_EVENT_STA_DISCONNECTED");            
         break;
      case WL_NO_SSID_AVAIL:
         Log.verboseln("<aaSocMicro::WiFiEvent> WL_NO_SSID_AVAIL");            
         break;
      case WL_IDLE_STATUS: 
         Log.verboseln("<aaSocMicro::WiFiEvent> Detected WL_IDLE_STATUS");            
         break;
      default:
         Log.verboseln(F("<aaSocMicro::WiFiEvent> ERROR - UNKNOW SYSTEM EVENT %p."), event); 
         break;
   } //switch
} // aaSocMicro::_wiFiEvent()

/**
 * @brief Sends details about the GPIO pins to the log.
 * @details Peripherals connect to the SOC via the GPIO pins that are exposed
 * for use by the development board it is mounted to. These pin definitions are
 * defined in the include file included file 
 * The ESP32_WROOM_32E supports two Wireless connectivity options:
 * 1. WiFi: 802.11 b/g/n/e/i (802.11n @ 2.4 GHz up to 150 Mbit/s).
 * 2. Bluetooth: v4.2 BR/EDR and Bluetooth Low Energy (BLE).
 * 
 * Bluetooth and WiFi share the same radio comprised of:
 * 1. An RF reciever,
 * 2. An RF transmitter,
 * 3. A clock generator,
 * 4. A switch, and
 * 5. A Balun.    
 * @param null.
 * @return null.
 ******************************************************************************/
void aaSocMicro::_logGPIO()
{
} // aaSocMicro::_logGPIO()
 
/**
 * @brief Initialize Bluetooth system.
 * @details Initializing the Bluetooth system involves the following 3 steps:
 * 1. Initialize the contrller.
 * 2. Initialize Bluedroid.
 * 3. Enable Bluedroid.
 * 
 * # Esp32 Bluetooth Architecture
 * Bluetooth is a wireless technology standard for exchanging data over short 
 * distances, with advantages including robustness, low power consumption and 
 * low cost. The Bluetooth system can be divided into two different categories: 
 * Classic Bluetooth and Bluetooth Low Energy (BLE). ESP32 supports dual-mode 
 * Bluetooth, meaning that both Classic Bluetooth and BLE are supported by 
 * ESP32. Basically, the Bluetooth protocol stack is split into two parts: a 
 * “controller stack” and a “host stack”. The controller stack contains the 
 * PHY, Baseband, Link Controller, Link Manager, Device Manager, HCI and 
 * other modules, and is used for the hardware interface management and link 
 * management. The host stack contains L2CAP, SMP, SDP, ATT, GATT, GAP and 
 * various profiles, and functions as an interface to the application layer, 
 * thus facilitating the application layer to access the Bluetooth system. The 
 * Bluetooth Host can be implemented on the same device as the Controller, or 
 * on different devices. Both approaches are supported by ESP32.
 * 
 * # Bluedroid
 * The BLUEDROID Bluetooth Stack communicates with Bluetooth Controller over 
 * VHCI (Virtual Host Controller Interface) and at the same time provides APIs 
 * for user application. Bluetooth Profiles determine the functions of each 
 * layer of the Bluetooth from PHY to L2CAP while the Bluetooth Protocols 
 * define message formats and procedures for data transport, link control etc.
 * 
 * The following is a list of Classic Bluetooth Profiles and Protocols 
 * supported by BLUEDROID Bluetooth Stack of ESP32.
 * 
 * ## Classic Bluetooth Profiles
 * 
 * 1. GAP
 * 2. A2DP (SNK)
 * 3. AVRCP (CT)
 * 
 * ## Classic Bluetooth Protocols
 * L2CAP
 * SDP
 * AVDTP
 * AVCTP
 * 
 * The communication between ESP32’s Processor and Bluetooth Controller is 
 * based on Serial Interface. 
 * 
 * @param null.
 * @return null.
 ******************************************************************************/
bool aaSocMicro::_initBluetooth()
{
   if (!btStart()) 
   {
      Log.verboseln("Failed to initialize controller");
      return false;
   } // if
   if (esp_bluedroid_init() != ESP_OK) 
   {
      Log.verboseln("Failed to initialize bluedroid");
      return false;
   } // if
   if (esp_bluedroid_enable() != ESP_OK) 
   {
      Log.verboseln("Failed to enable bluedroid");
      return false;
   } //  if
   return true;
} // aaSocMicro::_initBluetooth()
 
/**
 * @brief Initialize Bluetooth.
 * @details The Bluetooth address consists of six integers. In this function
 * we concatinate these 6 integers as two-digit hex char* values separate by 
 * an additional 1 colon character. This results in a 15 character long 
 * address in a character array. 
 * @param null.
 * @return null.
 ******************************************************************************/
void aaSocMicro::_btAddress(char* targetArray) 
{
   const uint8_t* point = esp_bt_dev_get_address(); // Retrieve address.
   strcpy(targetArray, ""); // Clear array.
   for (int i = 0; i < 6; i++) // Loop through address one integer at a time.
   {
      char str[3]; // Build address 3 characters at a time.
      sprintf(str, "%02X", (int)point[i]); // Convert integer into a 2-digit hex value.
      strcat(targetArray, str); // Concatinate each hex value into the target array.
      if(i < 5) // Insert colon every 3 characters for the firt 5 groups. 
      {
         strcat(targetArray, ":"); // Concatinate a colon into the target array.
      } // if
   } // for
} // aaSocMicro::_btAddress()