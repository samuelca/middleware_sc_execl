void Data::data_warning(String cipSend, String data,const int timeout, int connectionId)
{
     cipSend = "AT+CIPSEND=";
     cipSend += connectionId;
     cipSend += ",";
     cipSend +=data.length();
     cipSend +="\r\n";
     sendCommand(cipSend,timeout);
}

void Data::send_data(String data, const int timeout)
{
  sendCommand(data,timeout);
}
