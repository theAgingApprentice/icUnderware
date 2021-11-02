#include <aaSocMicro.h> // Header file for linking.

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
aaSocMicro::aaSocMicro()
{
   bool showLevel = true; // Prefixed logging output with a single letter level.
   int loggingLevel = LOG_LEVEL_SILENT;
   Print *output = &Serial;
   Log.begin(loggingLevel, output, showLevel); // Set logging parameters. 
   Log.verboseln("<aaSocMicro::FirstFormConstructor> Logging set to %d.", loggingLevel);
} //aaSocMicro::aaSocMicro()

/**
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
 * calling code. 
 * @param reason is the address to put the reason code.
 * @param code is the nuerica reset value reported by the CPU. 
 * @return null 
 ******************************************************************************/
void aaSocMicro::_transReasonCode(char& reason, RESET_REASON code)
{
   switch(code)
   {
      case 1: strcpy(&reason, "1. POWERON_RESET"); break; // Vbat power on reset.
      case 3: strcpy(&reason, "3. SW_RESET"); break; // Software reset digital core.
      case 4: strcpy(&reason, "4. OWDT_RESET"); break; // Legacy watch dog reset digital core.
      case 5: strcpy(&reason, "5. DEEPSLEEP_RESET"); break; // Deep Sleep reset digital core.
      case 6: strcpy(&reason, "6. SDIO_RESET"); break; // 6 = Reset by SLC module, reset digital core.
      case 7: strcpy(&reason, "7. TG0WDT_SYS_RESET"); break; // 7 = Timer Group0 Watch dog reset digital core.
      case 8: strcpy(&reason, "8. TG1WDT_SYS_RESET"); break; // 8 = Timer Group1 Watch dog reset digital core.
      case 9: strcpy(&reason, "9. RTCWDT_SYS_RESET"); break; // 9 = RTC Watch dog Reset digital core.
      case 10: strcpy(&reason, "10. INTRUSION_RESET"); break; // 10 = Instrusion tested to reset CPU.
      case 11: strcpy(&reason, "11. TGWDT_CPU_RESET"); break; // 11 = Time Group reset CPU.
      case 12: strcpy(&reason, "12. SW_CPU_RESET"); break; // 12 = Software reset CPU.
      case 13: strcpy(&reason, "13. RTCWDT_CPU_RESET"); break; // 13 = RTC Watch dog Reset CPU.
      case 14: strcpy(&reason, "14. EXT_CPU_RESET"); break; // 14 = for APP CPU, reseted by PRO CPU.
      case 15: strcpy(&reason, "15. RTCWDT_BROWN_OUT_RESET"); break; // 15 = Reset when the vdd voltage is not stable.
      case 16: strcpy(&reason, "16. RTCWDT_RTC_RESET"); break; // 16 = RTC Watch dog reset digital core and rtc module.
      default: strcpy(&reason, "UNKNOWN"); break; // Reset reason unknown.
   } // switch()
} // aaSocMicro::_translateReasonCode()

/**
 * @brief Sends human readable reset reason for both cores to the log.
 * @param null
 * @return null
 ******************************************************************************/
void aaSocMicro::logResetReason()
{
   char _reason[20]; // Text version of last reset reason code.
   for(int8_t i=0; i < NUM_CORES; i++)
   {
      _transReasonCode(*_reason, rtc_get_reset_reason(i));
      Log.noticeln("<logResetReason> new CPU%d reset reason = %s", i, _reason);
   } // for
} // aaSocMicro::logResetReason()

/**
 * @brief Sends details about the host micro controller to the log.
 * @details Inside the ESP32 chip are the following subsystems:
 * - Core and memory subsystem insde of which are two processing cores, RAM and 
 * ROM.
 * - WiFi subsystem which shares RF send/recieve, clock, switch and balun with 
 * the Bluetooth subsystem.
 * - Bluetooth subsystem which shares RF send/recieve, clock, switch and balun 
 * with the WiFi subsystem.
 * - RTC subsystem inside of which are a PMU (Phasor measurement unit) a small 
 * and ultra low power (ULP) 32-bit co-processor, and 8Kbs of RAM memory known 
 * as the recovery memory. 
 * - Crytographic Acceleration subsystem which supports SHA, RSA, AES and RNG 
 * hardware acceleration.
 * - Peripherals subsystem that handles all of the General Purpose Input/Output 
 * (GPIO) interfaces.
 * @param null
 * @return null
 ******************************************************************************/
void aaSocMicro::logSubsystemDetails()
{
   _logCoreCPU();
   _logCoreMem();
   _logIntegratedFlash();
   _logPsramMem();
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
 * @param null
 * @return null
 ******************************************************************************/
void aaSocMicro::_logCoreCPU()
{
   Log.verboseln("<aaSocMicro::_logCoreCPU> Core CPU details.");
   Log.verboseln("<aaSocMicro::_logCoreCPU> ... CPU Count = %d", ESP.getChipCores());
   Log.verboseln("<aaSocMicro::_logCoreCPU> ... CPU Model = %s", ESP.getChipModel());
   Log.verboseln("<aaSocMicro::_logCoreCPU> ... CPU Revision = %d", ESP.getChipRevision());
   Log.verboseln("<aaSocMicro::_logCoreCPU> ... CPU clock speed = %uMhz", ESP.getCpuFreqMHz());
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
 * @param null
 * @return null
 * @todo: #4 Implement monitoring of heap and stack to detect potential SRAM 
 * corruption. 
 ******************************************************************************/
void aaSocMicro::_logCoreMem()
{
   const uint32_t STATIC_DATA_SIZE = ESP.getSketchSize() + ESP.getFreeSketchSpace();
   const uint32_t SRAM_SIZE = STATIC_DATA_SIZE + ESP.getHeapSize() + uxTaskGetStackHighWaterMark(NULL);

   Log.verboseln("<aaSocMicro::_logCoreMem> Core memory details.");
   Log.verboseln("<aaSocMicro::_logCoreMem> ... ROM contains Espressif code and we do not touch that.");
   Log.verboseln("<aaSocMicro::_logCoreMem> ...... ROM size = %u bytes.", XSHAL_ROM_SIZE);
   Log.verboseln("<aaSocMicro::_logCoreMem> ... SRAM is the binarys read/write area.");
   Log.verboseln("<aaSocMicro::_logCoreMem> ...... Total SRAM size (stack + heap + static data) = %u bytes.", SRAM_SIZE);
   Log.verboseln("<aaSocMicro::_logCoreMem> ...... The Stack contains local variables, interrupt and function pointers.");
   Log.verboseln("<aaSocMicro::_logCoreMem> ......... Stack highwater mark = %u bytes", uxTaskGetStackHighWaterMark(NULL));
   Log.verboseln("<aaSocMicro::_logCoreMem> ...... Static memory (aka sketch memory) is allocated at compile time and contains global and static variables.");
   Log.verboseln("<aaSocMicro::_logCoreMem> ......... Static data size = %u bytes.", STATIC_DATA_SIZE);
   Log.verboseln("<aaSocMicro::_logCoreMem> ......... Sketch size = %u bytes.", ESP.getSketchSize());
   Log.verboseln("<aaSocMicro::_logCoreMem> ......... Free sketch space = %u bytes.", ESP.getFreeSketchSpace());
   Log.verboseln("<aaSocMicro::_logCoreMem> ...... The Heap contains dynamic data.");
   Log.verboseln("<aaSocMicro::_logCoreMem> ......... Heap size = %u bytes.", ESP.getHeapSize());
   Log.verboseln("<aaSocMicro::_logCoreMem> ......... Free heap = %u bytes.", ESP.getFreeHeap());
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
 * 4. FM_FAST_READ -
 * 5. FM_SLOW_READ -
 * 255. FM_UNKNOWN -  
 * @param null
 * @return null
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
      default: strcpy(&details, "UNKNOWN"); break; 
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
 * @param null
 * @return null
 ******************************************************************************/
void aaSocMicro::_logIntegratedFlash()
{
   char _details[80]; // Text version of flash memory mode.
   Log.verboseln("<aaSocMicro::_logIntegratedFlash> Flash memory is where the Arduino binary resides. It is accessed via the SPI bus.");
   _transFlashModeCode(*_details);
   Log.verboseln("<aaSocMicro::_logIntegratedFlash> ... Flash mode = %s", _details);
   Log.verboseln("<aaSocMicro::_logIntegratedFlash> ... Flash chip size = %u", ESP.getFlashChipSize());
   Log.verboseln("<aaSocMicro::_logIntegratedFlash> ... Flash chip speed = %u", ESP.getFlashChipSpeed());
} // aaSocMicro::_logIntegratedFlash()

/**
 * @brief Sends details about the external Pseudo Static RAM memory to the log.
 * @details Off-chip SPI memory can be mapped into the available address space 
 * as external memory. Parts of the embedded memory can be used as transparent 
 * cache for this external memory. The architecture can supports up to 8 MB 
 * off-chip SPI SRAM (PSRAM). The Huzzah32 featherboard does not come with any 
 * PSRAM.
 * @param null
 * @return null
 ******************************************************************************/
void aaSocMicro::_logPsramMem()
{
   Log.traceln("<aaSocMicro::_logPsramMem> PSRAM is optional external RAM accessed via the SPI bus.");
   if(psramFound()) // Is SPI RAM (psudo ram) available?
   {
      Log.traceln("<aaSocMicro::_logPsramMem> ... PSRAM detected.");
      Log.verboseln("<aaSocMicro::_logPsramMem> ... PSRAM size = %u", ESP.getPsramSize());
      Log.verboseln("<aaSocMicro::_logPsramMem> ... Free PSRAM = %u", ESP.getFreePsram());
   } // if
   else
   {
      Log.traceln("<aaSocMicro::_logPsramMem> ... No PSRAM detected.");
   } // else   
} // aaSocMicro::_logPsramMem()

// Still need these routines worked out.
//void _logGPIO(); // Logs GPIO details.
//void _Wireless(); // Logs radio details.
//void _Bluetooth(); // Logs bluetooth details.     

