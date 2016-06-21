#include "connection.h"

  
String Connection::get_ip(){
  return this->Ipadress;
}

int Connection::get_connectionId(){
  return connectionId;
}


void Connection::reset(const int timeout){
   sendCommand("AT+RST\r\n",timeout);
}

  
int Connection::get_connection()
{
  initialize_serial();
  this->reset(3000);
  this->set_mode(2000);
  delay(1000);
  this->find_network(2000);
  delay(5000);
  this->get_ip(1000);
  delay(2000);
  this->set_multiple_connection(1000);
  delay(2000);
}

void Connection::find_network(const int timeout)
{
  String rede = "AT+CWJAP=\"" + this->SSID + "\",\"" + this->PSWD + "\"\r\n";
  sendCommand(rede, timeout);
}

void Connection::set_mode(const int timeout)
{

  String modo = "AT+CWMODE=";
  modo += this->Modo;
  modo += "\r\n";
  sendCommand(modo, timeout);

}
void Connection::get_ip(const int timeout)
{
  this->Ipadress = sendCommand("AT+CIFSR\r\n",timeout);
}

void Connection::set_multiple_connection(const int timeout)
{
  String mux = "AT+CIPMUX=";
  mux += Multipleconnection;
  mux += "\r\n"; 
  sendCommand(mux,timeout);
 
}

void Connection::change_baud(int baud,const int timeout){
  String rate = "AT+CIOBAUD=";
  rate += baud;
  rate += "\r\n";
  sendCommand(rate,timeout);
}


void Connection::close_connection(const int timeout)
{
  String closeConnection = "AT+CIPCLOSE=";
  closeConnection+=connectionId; 
  closeConnection+="\r\n";
  sendCommand(closeConnection,timeout);
}


