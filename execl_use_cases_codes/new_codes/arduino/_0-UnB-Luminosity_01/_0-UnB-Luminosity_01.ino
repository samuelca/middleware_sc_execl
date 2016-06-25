/* UnB-UioT - Luminosity sensor, if dark so it lights, else lamp continue in low state */

#define ANALOG_SENSOR_PIN  A0 
#define DIGITAL_SENSOR_PIN 7
#define LEDPIN    13  // LED connected with the pin #

int  digitalValue;  /* Last digital value from module */
int  analogValue; /* Last analogical value from module */

void setup()
{
  pinMode(LEDPIN, OUTPUT);
  Serial.begin(9600);          // Enable the Serial data output
}


void loop()
/* If the digital value is HIGH (which means that is dark) then the light comes ON */
{
  digitalValue = digitalRead(DIGITAL_SENSOR_PIN);  
  if (digitalValue == HIGH)
  {
    digitalWrite(LEDPIN, HIGH);
    Serial.println("Digital Signal = ON ");
  }  
  else
  {
    digitalWrite(LEDPIN, LOW);
  }

  analogValue = analogRead(ANALOG_SENSOR_PIN);  //Read the voltage from sensor
  Serial.print("Analog Value (from 0 to 1023): "); 
  Serial.println(analogValue,DEC);      // Send result to Serial Monitor
  delay(500);
}
