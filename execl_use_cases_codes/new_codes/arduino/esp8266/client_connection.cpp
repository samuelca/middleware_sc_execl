#include "client_connection.h" 
       

Client_Connection::Client_Connection(String param1, String param2, int param3, int param4, String param5, String param6, int param7)
{
  this->SSID = param1;
  this->PSWD = param2;
  this->Modo = param3;
  this->Multipleconnection = param4;
  this->Protocolo = param5;
  this->serverip = param6;
  this->porta = param7;
  this->connectionId = 0;
  this->Ipadress = "";
      
}

void Client_Connection::create_connection(const int timeout)  {     
       String cipstart = "AT+CIPSTART=";
       cipstart += connectionId;
       cipstart += ",";
       cipstart += "\"" + Protocolo + "\"";
       cipstart += ",";
       cipstart += "\"" + serverip + "\"";
       cipstart += ",";
       cipstart += porta;
       cipstart +="\r\n";
       sendCommand(cipstart,timeout);
}      
