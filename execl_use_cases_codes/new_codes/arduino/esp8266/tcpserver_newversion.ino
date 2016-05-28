#include "settings.h"


void setup()
{
  Serial.begin(9600);
  
  //configura o modulo e conecta o mesmo na rede
  esp_server->get_connection();
  
  //inicializa o servidor
  esp_server->create_connection(2000);
}


void loop()
{
   String requisicao;
   //verifica se houve alguma requisicao para o servidor
   requisicao = esp_server->connected_client();
   
   if (requisicao != "-1"){
     
     esp_server->set_connectionId(requisicao[0] - 48);     // connectionId é um inteiro, entao pela tabela ASCII subtrai 48
     Serial.print(requisicao);
     
     //falta avaliar a requisicao
     String data = "CONEXAO OK";

     //envio de dados
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
