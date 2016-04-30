#include <SoftwareSerial.h>
#include "esp_connection.h"

#define SSID UIoT
#define PSWD dgKYfPFi

int connectionId=0 ; 

SoftwareSerial esp8266(2,3); // make RX Arduino pin 2, make TX Arduino pin 3.
                             
void setup()
{
  Serial.begin(9600);
  esp8266.begin(115200); // your esp's baud rate might be different
  analogReference(INTERNAL);
 
  reset(2000);
  find_network(SSID, PSWD, 2000);
  wait(5000);
  set_mode(1,2000);
  get_ip(1000);
  set_multiple_connection(1, 1000);
  create_connection(cipstart, 1000, 0);
    
}



 String sendCommand(String command, const int timeout)
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
    Serial.print(response);
    return response;
}

void loop()
{
     String cipSend;
     String data = "Codigo RFID: ";
     data += (String)temp;
     data_warning(cipSend, data, 1000, 0);
     send_data(data, 1000);
     delay(5000);
}

void reset(const int timeout)
{
  sendCommand("AT+RST\r\n",timeout); 
}

void find_network(String ssid, String psw, const int timeout)
{
  sendCommand("AT+CWJAP=ssid,psw\r\n", timeout);
}

void set_mode(int mode, const int timeout)
{
  sendCommand("AT+CWMODE=mode\r\n", timeout);
}

void get_ip(const int timeout)
{
  sendCommand("AT+CIFSR\r\n",timeout);
}

void set_multiple_connection(bool mult, const int timeout)
{
  sendCommand("AT+CIPMUX=mult\r\n",timeout);
}

void create_connection(String cipstart, const int timeout, int connectionId)
{
     cipstart = "AT+CIPSTART=";
     cipstart += connectionId;
     cipstart += ",";
     cipstart += "\"TCP\"";
     cipstart += ",";
     cipstart += "\"192.168.1.112\"";
     cipstart += ",";
     cipstart += 8000;
     cipstart +="\r\n";
    sendCommand(cipstart,timeout);
}

void wait(const int timeout)
{
  delay(timeout);
}

void data_warning(String cipSend, String data,const int timeout, int connectionId)
{
     cipSend = "AT+CIPSEND=";
     cipSend += connectionId;
     cipSend += ",";
     cipSend +=data.length();
     cipSend +="\r\n";
     sendCommand(cipSend,timeout);
}

void send_data(String data, const int timeout)
{
  sendCommand(data,timeout);
}

void close_connection(String closeConnection, const int timeout, int connectionId)
{
  closeConnection = "AT+CIPCLOSE="; 
  closeConnection+=connectionId; // append connection id
  closeConnection+="\r\n";
  sendData(closeConnection,timeout);
}
