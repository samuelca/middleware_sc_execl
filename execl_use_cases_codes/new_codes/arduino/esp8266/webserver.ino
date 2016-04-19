#include <SoftwareSerial.h>
float temp, luminosidade;
#define DEBUG true
#define SSID UIoT
#define SENHA

SoftwareSerial esp8266(2,3); // make RX Arduino pin 2, make TX Arduino pin 3.
                             
void setup()
{
  Serial.begin(9600);
  esp8266.begin(19200); // your esp's baud rate might be different
  analogReference(INTERNAL);
 
  
  sendData("AT+RST\r\n",2000,DEBUG); // reset module
  sendData("AT+CWMODE=3\r\n", 1000, DEBUG);
  sendData("AT+CWSAP=\"Rede_esp\",\"esp123456789\",3,4\r\n", 2000, DEBUG);
  delay(3000);
  sendData("AT+CWJAP=SSID,SENHA\r\n", 2000, DEBUG);
  delay(5000);
  sendData("AT+CIFSR\r\n",1000,DEBUG); // get ip address
  sendData("AT+CIPMUX=1\r\n",1000,DEBUG); // configure for multiple connections
  sendData("AT+CIPSERVER=1,1200\r\n",1000,DEBUG); // turn on server on port 80
}
 
void loop()
{
  temp = analogRead(A0) * 0.1;
  //luminosidade = analogRead(A1)* 0.09775171;
  if(esp8266.available()) // check if the esp is sending a message 
  {
    
    if(esp8266.find("+IPD,"))
    {
     delay(1000);
 
     int connectionId = esp8266.read()-48; // subtract 48 because the read() function returns 
                                           // the ASCII decimal value and 0 (the first decimal number) starts at 48
     
      String webpage = "<head><meta http-equiv=\"refresh\" content=\"5\">";
      webpage += "</head><h1><u>ESP8266 - Web Server</u></h1>";
      webpage += "<h2>Temperatura do escritorio : ";
      webpage += temp;
      webpage += "*C";
      webpage += "</h2>";
      webpage += "<h2>Luminosidade do escritorio : ";
      webpage += luminosidade;
      webpage += "%";
      webpage += "</h2>"; 
 
     String cipSend = "AT+CIPSEND=";
     cipSend += connectionId;
     cipSend += ",";
     cipSend +=webpage.length();
     cipSend +="\r\n";
     
     sendData(cipSend,1000,DEBUG);
     sendData(webpage,1000,DEBUG);
     
     String closeCommand = "AT+CIPCLOSE="; 
     closeCommand+=connectionId; // append connection id
     closeCommand+="\r\n";
     
     sendData(closeCommand,3000,DEBUG);
    }
  }
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
}
