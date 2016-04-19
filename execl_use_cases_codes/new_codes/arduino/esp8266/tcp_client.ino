#include <SoftwareSerial.h>
float temp, luminosidade;
int entrou=1;
#define DEBUG true
int connectionId=0 ; 
SoftwareSerial esp8266(2,3); // make RX Arduino pin 2, make TX Arduino pin 3.
                             
void setup()
{
  Serial.begin(9600);
  esp8266.begin(19200); // your esp's baud rate might be different
  analogReference(INTERNAL);
  
  sendData("AT+RST\r\n",2000,DEBUG); // reset module
  sendData("AT+CWJAP=\"TDDQ\",\"1A7699BE11\"\r\n", 2000, DEBUG);
  delay(5000);
  sendData("AT+CWMODE=1\r\n", 1000, DEBUG);
  sendData("AT+CIFSR\r\n",1000,DEBUG); // get ip address
  sendData("AT+CIPMUX=1\r\n",1000,DEBUG); // configure for multiple connections
  //sendData("AT+CIPSTART=connectionId,\"TCP\",\"192.168.1.112\",8000\r\n",1000,DEBUG);
  String cipstart = "AT+CIPSTART=";
     cipstart += connectionId;
     cipstart += ",";
     cipstart += "\"TCP\"";
     cipstart += ",";
     cipstart += "\"192.168.1.112\"";
     cipstart += ",";
     cipstart += 8000;
     cipstart +="\r\n";
     sendData(cipstart,1000,DEBUG);
}



 String sendData(String command, const int timeout, boolean debug)
{
    String response = "";
    
    esp8266.print(command); // send the read character to the esp8266
    
    long int time = millis();
    
    while( (time+timeout) > millis())
    {
      while(esp8266.available())
      {
        
        // The esp has data so display its output to the serial window 
        char c = esp8266.read(); // read the next character.
        response+=c;
      }  
    }
    
    if(debug)
    {
      Serial.print(response);
    }
    
    return response;
}

void loop()
{
  temp = analogRead(A0) * 0.1;
  Serial.println(temp);
     String webpage = "Temperatura: ";
     webpage += (String)temp;
     String cipSend = "AT+CIPSEND=";
     cipSend += connectionId;
     cipSend += ",";
     cipSend +=webpage.length();
     cipSend +="\r\n";
     sendData(cipSend,1000,DEBUG);
     sendData(webpage,1000,DEBUG);
      delay(5000);

  
}
 
 
