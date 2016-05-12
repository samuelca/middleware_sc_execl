#include "data.h"



void Data::data_warning(const int timeout, int connectionId)
{
     
     String cipSend = "AT+CIPSEND=";
     cipSend += connectionId;
     cipSend += ",";
     cipSend +=data_value.length();
     cipSend +="\r\n";
     sendCommand(cipSend,timeout);
}

void Data::send_data(const int timeout)
{
  sendCommand(data_value,timeout);
}

String Data::get_data(){
  return data_value;
}

void Data::set_data(String data){
  data_value = data
}

