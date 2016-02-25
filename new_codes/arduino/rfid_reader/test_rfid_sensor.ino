#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
#include <SPI.h>

// Data Transmission TX.
// observation.: RDM6300 runs at 9600 bp/s
#define receiveBaudRate 9600

// LED Blink Interval
#define ledBlinkTime 1000

// Acceptable (VALID) RFID Card Codes. (RADIO FREQUENCY IDENTIFICATION)
PGM_P const acceptableRfidCodes[] PROGMEM =
{   
  "05004D947FA3",
  "000000000001"
};

// Card User Names (in same order of acceptableRfidCodes)
const String codeNames[] =
{   
  "Caldio",
  "Buceta"
};

// Arduino Board Pin and RDM6300 Digital Pins
const int pinPositions[] = 
{
  2, // First Digital Pin
  3 // Second Digital Pin
};

// RDM6300 Serial
SoftwareSerial rfidReader(pinPositions[0], pinPositions[1]);

// LiquidCrystal Serial
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);  

// Environment Configuration
void setup() 
{
  // Start Serial listener
  Serial.begin(receiveBaudRate);

  // Start RFID listener
  rfidReader.begin(receiveBaudRate);

  // Configure LCD
  lcd.begin(16, 2); 
  
  Serial.println("RFID Reader...ready!");
}

// Main Loop
void loop() 
{  
  // Tag Code (Need be 15 Characters)
  char receivedTagCode[14];

  // Initial Message
  showInitialMessage();

  // Check if Receiving Data
  while(rfidReader.available()) {

    rfidReader.readBytesUntil(3, receivedTagCode, 15);  

    showTag(receivedTagCode);
  }

  // Reset Buffer from Tag Code
  memset(receivedTagCode, 0, sizeof(receivedTagCode));
}

// Show Tag
void showTag(char* receivedTag)
{
  // Convert to String
  String finalTagCode = receivedTag;

  // Show TAG Number
  Serial.println("Tag Number: " + finalTagCode);

  // Check Tag Validate
  checkTag(finalTagCode);

  // Flush Data
  flushData();
}

// Check Tag Validation
void checkTag(String receivedTag)
{
  // Reset LCD
  resetLCD();

  // Check if Exists TAG Code
  for(int i = 0; i < sizeof(acceptableRfidCodes) / 2; i++) {

    // Found a Match
    if(receivedTag.indexOf(acceptableRfidCodes[i]) >= 0) {

      Serial.println("Access Granted!");

      // Show Welcome Message
      showWelcomeMessage(codeNames[i], true);
      
      return;
    }
  }

  Serial.println("Access Not Granted!");

  // Show Welcome Message
  showWelcomeMessage("Visitante", false);
}

// Flush Environment Data
void flushData()
{
  // Delay of LCD
  delay(ledBlinkTime);

  resetLCD();

  // Flush RDM6300
  rfidReader.flush();
}

// Reset LCD Data
void resetLCD()
{
  // Clear LCD
  lcd.clear();

  // Reset Cursor Position
  lcd.setCursor(0,0);
}

// Show Welcome Message
void showWelcomeMessage(String userName, bool accessValid)
{
  lcd.print("Ola " + userName + "!");
  
  lcd.setCursor(0,1);
  
  lcd.print(accessValid ? "Acesso Liberado!" : "Acesso Fechado!");
}

// Show Initial Welcome Message
void showInitialMessage()
{
  lcd.setCursor(0,0);  
  
  lcd.print("Bom Dia!");
  
  lcd.setCursor(0,1);  
  
  lcd.print("Mostre o Cartao");
}

