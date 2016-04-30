#include <SoftwareSerial.h>
#include "esp_connection.h"
#include "esp_data.h"
#include "AT.h"

#define SSID UIoT
#define PSWD dgKYfPFi
#define DEBUG true
int connectionId=0 ;

SoftwareSerial esp8266(2,3); // make RX Arduino pin 2, make TX Arduino pin 3.

void setup()
{
  Serial.begin(9600);
  esp8266.begin(115200); // your esp's baud rate might be different
  analogReference(INTERNAL);

  reset(2000);
  find_network(SSID, PSWD, 2000);
  wait(5000);
  set_mode(1,2000);
  get_ip(1000);
  set_multiple_connection(1, 1000);
  create_connection(cipstart, 1000, 0);

}


void loop()
{
     String cipSend;
     String data = "Codigo RFID: ";
     data += (String)temp;
     data_warning(cipSend, data, 1000, 0);
     send_data(data, 1000);
     delay(5000);
}

void reset(const int timeout)
{
  sendCommand("AT+RST\r\n",timeout);
}

void wait(const int timeout)
{
  delay(timeout);
}
