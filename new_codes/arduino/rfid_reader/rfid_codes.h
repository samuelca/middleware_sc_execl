#ifndef RFID_CODES
#define RFID_CODES

  #include <Arduino.h>
  
  // Acceptable (VALID) RFID Card Codes. (RADIO FREQUENCY IDENTIFICATION)
  const String acceptableRfidCodes[] =
  {   
    "05004D947FA3",
    "05005DFA70D2",
    "05005EC1A53F",
    "05004D9C1ACE"
  };
  
  // Card User Names (in same order of acceptableRfidCodes)
  const String codeNames[] =
  {   
    "Guria",
    "Caio",
    "Timoteo",
    "Claudio"
  };

#endif
