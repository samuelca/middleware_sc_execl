#include "settings.h"

void setup()
{
  Serial.begin(9600);
  
  //principal função da classe de conexão. Responsável por conectar o dispositivo na rede e configurá-lo
  esp_client->get_connection();
  
}


void loop()
{
  /*toda vez que for enviar dados, criar conexão e depois fechá-la. Se quiser, pode abrir apenas 
  uma vez no SETUP e não fechar
  */
     esp_client->create_connection(2000);
     String jsonstring;
     String data = "Codigo RFID: ";
     String nome = "Bruno";
     String URL = "/raise/services/rfidcode=" + data + "&name=" + nome + "\r\n";

     //envio de dados - http
     dado->create_http(URL, "GET", serverip);
     dado->data_warning(3000, esp_client->get_connectionId());
     dado->send_data(3000);
          
     //resposta do servidor no formato json
     jsonstring = dado->get_jsonstring();
     Serial.println(jsonstring);
     /*
     // se houver conteudo json, chamar funcao para interpretar a mensagem (funcao parseJson)
     if (jsonstring != ""){
        char jsonChar[jsonstring.length()];
        jsonstring.toCharArray(jsonChar, jsonstring.length() + 1);
        Serial.println(dado->parseJson(jsonChar));
     }
     */
     esp_client->close_connection(2000);
     wait(10000);
}

void wait(const int timeout)
{
  delay(timeout);
}
