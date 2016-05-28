#include "AT.h"

void initialize_serial()
{
  esp8266->begin(19200);
}

String sendCommand(String command, const int timeout)
{
   String response = "";
   esp8266->print(command);

   long int time = millis();

   while( (time+timeout) > millis())
   {
     while(esp8266->available())
     {
         char c = esp8266->read();
         response+=c;
      
     }
   }
   
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
