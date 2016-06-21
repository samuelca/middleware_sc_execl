#include "AT.h"

void initialize_serial()
{
  esp8266->begin(19200);
}

String sendCommand(String command, const int timeout)
{
  
   String response = "";
   esp8266->print(command);
   esp8266->setTimeout(timeout);
   response = esp8266->readString();

   Serial.print(response);
   return response;
   
}

String client_available()
{
  String aux = "-1";
  if (esp8266->available()){
       if (esp8266->find("+IPD,")){
          aux = "";
          aux = esp8266->readString();
          return aux;
       }
       else{
          return aux;
       }
       
  }
  else{
    return aux;
  }
}

