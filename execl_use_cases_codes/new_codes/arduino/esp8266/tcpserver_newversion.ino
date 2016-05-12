#include "connection.h"
#include "data.h"

//#include "AT.h"
//#include "settings.h"

#define SSID dlink-9FC8
#define PSWD xpqap4952
#define porta 8000

Connection * esp_server = new Connection(SSID, PSWD, 0, 1, SERVER, 0, porta);
Data * dado = new Data();

void setup()
{
  Serial.begin(9600);
  esp_server->get_connection();
  Serial.print(esp_server->get_ip());

}


void loop()
{
   int tam;
   char requisicao[] = connected_client(&tam);
   if (requisicao[0] =! -1){
      set_connectionId(requisicao[0] - 48);
      int i=0;
      while (i<tam){
        Serial.print(requisicao[i]);
      }
      //falta avaliar a requisicao
     String data = "CONEXAO OK";
     dado->set_data(data);
     dado->data_warning(1000, esp_server->get_connectionId());
     dado->send_data(1000);
     esp_server->close_connection(3000);
   }

}



void wait(const int timeout)
{
  delay(timeout);
}
