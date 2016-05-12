#include "connection.h"



String Connection::get_ip(){
  return this->Ipadress;
}

int Connection::get_connectionId(){
  return connectionId;
}


void Connection::set_connectionId(int valor){
  connectionId = valor;
}

void Connection::reset(const int timeout){
  
  sendCommand("AT+RST\r\n",timeout);
}

  
int Connection::get_connection(){
  this->reset(3000);
  this->find_network(2000);
  delay(5000);
  this->set_mode(2000);
  this->get_ip(1000);
  this->set_multiple_connection(1000);
  this->create_connection(1000);
    
}


void Connection::find_network(const int timeout)
{
  sendCommand("AT+CWJAP=SSID,PSWD\r\n", timeout);

}

void Connection::set_mode(const int timeout)
{
  sendCommand("AT+CWMODE=Modo\r\n", timeout);

}
void Connection::get_ip(const int timeout)
{
  this->Ipadress = sendCommand("AT+CIFSR\r\n",timeout);
}

void Connection::set_multiple_connection(const int timeout)
{
  sendCommand("AT+CIPMUX=Multipleconnection\r\n",timeout);
 
}

void Connection::create_connection(const int timeout)
{
     if(Protocolo == "SERVER"){
        sendCommand("AT+CIPSERVER=1,porta\r\n",timeout);
     }
     else{
       String cipstart = "AT+CIPSTART=";
       cipstart += connectionId;
       cipstart += ",";
       cipstart += "\"Protocolo\"";
       cipstart += ",";
       cipstart += "\"serverip\"";
       cipstart += ",";
       cipstart += porta;
       cipstart +="\r\n";
       sendCommand(cipstart,timeout);
  }  
}


void Connection::close_connection(const int timeout)
{
  String closeConnection = "AT+CIPCLOSE=";
  closeConnection+=connectionId; // append connection id
  closeConnection+="\r\n";
  sendCommand(closeConnection,timeout);
}
