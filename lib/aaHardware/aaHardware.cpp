#include <aaHardware.h> // Header file for linking.

/**
 * @fn aaHardware::aaHardware()
 * @brief This is the first constructor form for this class.
 * @details Instantiating this class using the first form results in the 
 * following default settings.
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
aaHardware::aaHardware()
{
   bool showLevel = true; // Prefixed logging output with a single letter level.
   int loggingLevel = LOG_LEVEL_SILENT;
   Print *output = &Serial;
   Log.begin(loggingLevel, output, showLevel); // Set logging parameters. 
   Log.verboseln("<aaHardware::FirstFormConstructor> Logging set to %d.", loggingLevel);
} //aaHardware::aaHardware()

/**
 * @overload aaHardware::aaHardware(Print* output)
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
aaHardware::aaHardware(Print* output)
{
   bool showLevel = true; // Prefixed logging output with a single letter level.
   int loggingLevel = LOG_LEVEL_SILENT;
   Log.begin(loggingLevel, output, showLevel); // Set logging parameters. 
   Log.traceln("<aaHardware::SecondFormConstructor> Logging set to %d.", loggingLevel);
} //aaHardware::aaHardware()

/**
 * @overload aaHardware::aaHardware(int loggingLevel, Print* output, bool showLevel)
 * @brief This is the third constructor form for this class.
 * @details Instantiating this class using the third form results in you
 * controlling all Logging behavior for this class.
 * @param loggingLevel is one of 6 predefined levels from the Logging library.
 * @param output is a class that can handle bit stream input (e.g. Serial).
 * @param showLevel prefixs log message with the Logging level letter when TRUE.
 * @return null
 ******************************************************************************/
aaHardware::aaHardware(int loggingLevel, Print* output, bool showLevel)
{
   Log.begin(loggingLevel, output, showLevel); // Set logging parameters. 
   Log.traceln("<aaHardware::ThirdFormConstructor> Logging set to %d.", loggingLevel);
} //aaHardware::aaHardware()

/**
 * @brief This is the destructor for this class.
 * @param null
 * @return null
 ******************************************************************************/
aaHardware::~aaHardware()
{
   Log.traceln("<aaHardware::~aaHardware> Destructor running.");
} //aaHardware::~aaHardware()

/**
 * @brief Initialize the applications underlying hardware.
 * @details The application's hardware is controlled through the 
 * @param null
 * @return null
 ******************************************************************************/
void aaHardware::start()
{
   Log.traceln("<aaHardware::start> Initializing underlying hardware platform.");
   MCU.logResetReason(); // Report on reason for last CPU reset.
   MCU.configure(); // Configure robot.
   MCU.logSubsystemDetails(); // Log microprocessor details.
} //aaHardware::start()