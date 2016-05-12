#include "connection.h"
#include "data.h"
//#include "AT.h"
//#include "settings.h"

#define SSID dlink-9FC8
#define PSWD xpqap4952
const char *serverIP = "192.16.9.70"
#define porta 8000

Connection * esp_client = new Connection(SSID, PSWD, 0, 1, TCP, serverIP, porta);
Data * dado = new Data();

void setup()
{
  Serial.begin(9600);
  esp_client->get_connection();
  Serial.print(esp_client->get_ip());

}


void loop()
{
     String data = "Codigo RFID: ";
     dado->set_data(data);
     dado->data_warning(1000, esp_client->get_connectionId());
     dado->send_data(1000);
     wait(5000);
}



void wait(const int timeout)
{
  delay(timeout);
}
