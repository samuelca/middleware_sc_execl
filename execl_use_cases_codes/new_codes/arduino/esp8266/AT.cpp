#include "AT.h"


void AT::initialize_serial(){
  esp8266->begin(115200);
}

String AT::sendCommand(String command, const int timeout)
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

char* AT::connected_client(int *tam){
  char aux[] = "-1";
  if (esp8266->available()){
       if (esp8266->find("+IPD,")){
          int i=0;
          while (esp8266->available()){
            aux[i] = esp8266->read();
            i++;
         }
         *tam = i;
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


