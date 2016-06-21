#include "settings.h"

int connectionId;

void setup()
{
  Serial.begin(9600);

  
     
     //principal função da classe de conexão. Responsável por conectar o dispositivo na rede e configurá-lo
     esp_client->get_connection();
     esp_client->create_connection(2000);
     connectionId = esp_client->get_connectionId();

     dado->authenticate("POST", connectionId);
     dado->service("POST", connectionId);
     
     
     


     //esp_client->close_connection(2000);

}


void loop()
{
  /*toda vez que for enviar dados, criar conexão e depois fechá-la. Se quiser, pode abrir apenas 
  uma vez no SETUP e não fechar
  */
   float temp;
   int timing = dado->get_timing();

   if (!dado->update("PUT", connectionId)){
    //se der erro na hora de enviar dado, pedir para se autenticar de novo com PUT
    dado->authenticate("PUT", connectionId);
   }
   delay(timing);


}


