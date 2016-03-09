#include "rfid_manipulation_library.h"
#include "rfid_sensor_library.h"

// Identification Blink Phase
int identificationPhase = 0;

// Environment Configuration
void setup() 
{
  // LED Blink Output
  pinMode(pinPositions[3], OUTPUT);
  
  // Start Serial listener
  Serial.begin(receiveBaudRate);

  // Configure LCD
  lcd->begin(lcdConfiguration[0], lcdConfiguration[1]); 

  // Start RFID listener
  rfidReader->begin(receiveBaudRate);

  // Print Ready Message
  Serial.println("RFID Reader...ready!");
}

// Main Loop
void loop() 
{
  // Tag Code (Need be 15 Characters)
  char receivedTagCode[14];

  if(!rfidReader->available()) {   
    // Print Pointers
    identificationPhase = showInitialMessage(messageConfiguration[0], messageConfiguration[1], identificationPhase);
  }

  // Check if Receiving Data
  while(rfidReader->available()) {

    rfidReader->readBytesUntil(3, receivedTagCode, 15);

    showTag(receivedTagCode);

    identificationPhase = 0;
  }

  // Reset Buffer from Tag Code
  memset(receivedTagCode, 0, sizeof(receivedTagCode));

  if(!rfidReader->available()) {   
    // Sub Message Delay
    delay(initialMessageShowInterval);
  }
}

