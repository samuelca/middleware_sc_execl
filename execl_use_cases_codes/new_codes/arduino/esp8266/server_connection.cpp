#include "server_connection.h"

Server_Connection::Server_Connection(String param1, String param2, int param3, int param4, String param5, int param6)
{
  //pq nao da para chamar initialize_serial na funcao construtora?
  this->SSID = param1;
  this->PSWD = param2;
  this->Modo = param3;
  this->Multipleconnection = param4;
  this->Protocolo = param5;
  this->porta = param6;
  this->connectionId = 0;
  this->Ipadress = "";
      
}


void Server_Connection::create_server(const int timeout){
        String cipserver = "AT+CIPSERVER=1,";
        cipserver += this->porta;
        cipserver += "\r\n";
        sendCommand(cipserver,timeout);
}

void Server_Connection::set_connectionId(int valor){
  connectionId = valor;
}
