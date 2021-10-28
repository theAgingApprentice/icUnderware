/*!
 * @file aaTemplate.h  
 ===================================================================================*/
#ifndef aaTemplate_h // Start precompiler code block. 

#define aaTemplate_h // Precompiler macro used to avoid dupicate inclusion of this code.

/************************************************************************************
 * @section aaTemplateIncludes Included libraries.
 ************************************************************************************/
#include <Arduino.h> // Arduino Core for ESP32. Comes with Platform.io.

/************************************************************************************
 * @class Read/write to/from flash RAM.
 ************************************************************************************/
class aaTemplate // Indicate that we are extending LiquidCrystal_I2C class with our class 
{
   public:
      aaTemplate(); // Default constructor for this class.
      aaTemplate(const char* var1); // Second form of class constructor.
      ~aaTemplate(); // Class destructor.
      void examplePublicFunction(int); // This is a public class.
   private: 
      bool _examplePrivateFunction(); // This is a private class.
}; //class aaTemplate

extern aaTemplate myRefVar; // Expose all public variables and methods for libraries.

#endif // End of precompiler protected code block