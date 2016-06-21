#ifndef RFID_SENSOR_LIBRARY
#define RFID_SENSOR_LIBRARY

#include "rfid_codes.h"
#include "rfid_settings.h"
  
  void showTag(String receivedTag);
  
  void checkTag(String receivedTag);
  
  void flushData();
  
  void resetLCD();
  
  void showWelcomeMessage(String userName, bool accessValid);
  
  int showInitialMessage(String firstLine, String secondLine, int identificationPhase);

#endif
