#ifndef RFID_SETTINGS
#define RFID_SETTINGS

  #include <SoftwareSerial.h>
  #include <LiquidCrystal.h>
  #include <SPI.h>
  
  // Data Transmission TX.
  // observation.: RDM6300 runs at 9600 bp/s
  #define receiveBaudRate 9600
  
  // LED Blink Interval
  #define ledBlinkTime 1000

  // Delay do Relé Trancar
  #define openPortaInterval 4000
  
  // LCD Change Delay Time
  #define messageShowInterval 2000

  // Initial LCD Message Delay Time
  #define initialMessageShowInterval 1000

  // Max Amount of Pointers
  #define lcdWaitMaxPointerNumber 8
  
  // LCD Message Configuration
  const String messageConfiguration[] =
  {
    "UIoT RFID 1.0",
    "Waiting",
    "Ola, ",
    "Acesso Liberado!",
    "Acesso Negado!"
  };
  
  // LCD Screen Size Configuration
  const int lcdConfiguration[] = 
  {
    16, // Number of Columns
    2  // Number of Lines
  };
  
  // Arduino Board Pin and RDM6300 Digital Pins
  const int pinPositions[] = 
  {
    2, // First Digital Pin
    3, // Second Digital Pin
    13 // Relé
  };

  // LiquidCrystal Serial
  static LiquidCrystal * lcd = new LiquidCrystal(8, 9, 4, 5, 6, 7);

  // RDM6300 Serial
  static SoftwareSerial * rfidReader = new SoftwareSerial(pinPositions[0], pinPositions[1]);

#endif
 
