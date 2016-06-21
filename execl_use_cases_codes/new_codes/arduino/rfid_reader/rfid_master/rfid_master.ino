#include "rfid_manipulation_library.h"
#include "rfid_sensor_library.h"

// Identification Blink Phase
int identificationPhase = 0;

// Environment Configuration
void setup()
{  
  // Start Serial listener
  Serial.begin(receiveBaudRate);

  // Relé
  pinMode(pinPositions[2], OUTPUT);

  // Ativa Relé
  digitalWrite(pinPositions[2], HIGH);

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
  if(!rfidReader->available()) {   
    // Print Pointers
    identificationPhase = showInitialMessage(messageConfiguration[0], messageConfiguration[1], identificationPhase);
  }

  // Check if Receiving Data
  while(rfidReader->available()) {
    
    showTag(rfidReader->readString());

    identificationPhase = 0;
  }

  if(digitalRead(pinPositions[2]) == LOW) {
    // Delay De Porta
    delay(openPortaInterval);

    // Ativa Relé
    digitalWrite(pinPositions[2], HIGH);
  }

  if(!rfidReader->available()) {   
    // Sub Message Delay
    delay(initialMessageShowInterval);
  }
}

