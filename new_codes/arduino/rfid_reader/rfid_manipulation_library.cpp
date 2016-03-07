#include "rfid_manipulation_library.h"

// Repeat String Function (Formerly Str_Repeat)
String repeatString(String character, int times)
{
  String characterRepeated;
  
  for(int i = 0; i < times; i++) {
    characterRepeated += character;
  }

  return characterRepeated;
}

// Identification Message Loop
int identificationLoop(int idPhase)
{ 
  if(idPhase < (lcdWaitMaxPointerNumber - 1)) {
    return idPhase + 1;
  }
  
  return 0;
}
