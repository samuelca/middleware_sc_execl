#include "rfid_sensor_library.h"
#include "rfid_manipulation_library.h"

// Show Tag
void showTag(String receivedTag)
{ 
  // Show TAG Number
  Serial.println("Tag Number: " + receivedTag.substring(1, 13));

  // Check Tag Validate
  checkTag(receivedTag.substring(1, 13));

  // Flush Data
  flushData();
}

// Check Tag Validation
void checkTag(String receivedTag)
{
  // Reset LCD
  resetLCD();

  // Check if Exists TAG Code
  for(int i = 0; i < sizeof(acceptableRfidCodes) / sizeof(String); i++) {
    
    // Found a Match
    if(receivedTag.equalsIgnoreCase(acceptableRfidCodes[i])) {

      Serial.println("Access Granted!");

      // Relé
      digitalWrite(pinPositions[2], LOW);

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
  delay(messageShowInterval);

  resetLCD();

  // Flush RDM6300
  rfidReader->flush();
}

// Reset LCD Data
void resetLCD()
{
  // Clear LCD
  lcd->clear();

  // Set Cursor to First line
  lcd->setCursor(0, 0);
}

// Show Welcome Message
void showWelcomeMessage(String userName, bool accessValid)
{
  // Configure LCD
  lcd->begin(lcdConfiguration[0], lcdConfiguration[1]); 
  
  // Set Cursor to First line
  lcd->setCursor(0, 0);

  // Print User Name
  lcd->print(messageConfiguration[2] + userName);

  // Set Cursor Second Line
  lcd->setCursor(0, 1);

  // Print if is Valid
  lcd->print(accessValid == true ? messageConfiguration[3] : messageConfiguration[4]);
}

// Show Initial Welcome Message
int showInitialMessage(String firstLine, String secondLine, int idPhase)
{
  // Configure LCD
  lcd->begin(lcdConfiguration[0], lcdConfiguration[1]); 
  
  // Set Cursor to First line
  lcd->setCursor(0, 0);

  // Print First Line
  lcd->print(firstLine);

  // Set Cursor to Second Line
  lcd->setCursor(0, 1);

  // Print Second Line
  lcd->print(secondLine + repeatString(".", idPhase + 1));

  // Return ID Loop
  return identificationLoop(idPhase);
}

