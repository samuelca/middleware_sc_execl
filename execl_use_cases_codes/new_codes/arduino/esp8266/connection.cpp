void Connection::find_network(String ssid, String psw, const int timeout)
{
  sendCommand("AT+CWJAP=ssid,psw\r\n", timeout);
}

void Connection::set_mode(int mode, const int timeout)
{
  sendCommand("AT+CWMODE=mode\r\n", timeout);
}

void Connection::get_ip(const int timeout)
{
  sendCommand("AT+CIFSR\r\n",timeout);
}

void Connection::set_multiple_connection(bool mult, const int timeout)
{
  sendCommand("AT+CIPMUX=mult\r\n",timeout);
}

void Connection::create_connection(String cipstart, const int timeout, int connectionId)
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


void Connection::close_connection(String closeConnection, const int timeout, int connectionId)
{
  closeConnection = "AT+CIPCLOSE="; 
  closeConnection+=connectionId; // append connection id
  closeConnection+="\r\n";
  sendData(closeConnection,timeout);
}
