#include "data.h"

void Data::data_warning(const int timeout, int connectionId)
{
     String cipSend = "AT+CIPSEND=";
     cipSend += connectionId;
     cipSend += ",";
     cipSend += data_value.length();
     cipSend +="\r\n";
     sendCommand(cipSend,timeout);
}

void Data::send_data(const int timeout)
{
   String resposta = sendCommand(data_value,timeout);
   delay(100);
   check_json(resposta);

}

String Data::get_data(){
  return data_value;
}

void Data::set_data(String data)
{
  data_value = data;
}

void Data::create_http(String data, String metodo, String serverip)
{
    String http = metodo + " /services/ ";
    //http += data;
    http += " HTTP/1.1\r\n";
    //http += "HOST: " + serverip + "\r\n";
    http += "Connection: close\r\n";
    http += "Content-Lenght: ";
    http += data.length();
    http += "\r\n";
    http += "\r\n";
    this->set_data(http);
            
}



char* Data::parseJson(char* jsonstring)
{
   aJsonObject* root = aJson.parse(jsonstring);
   char* resposta = "";

    if (root != NULL) {

        aJsonObject* Id = aJson.getObjectItem(root, "ID");
        //aJsonObject* response = aJson.getObjectItem(root, "message");
        
        resposta = Id->valuestring;
        
    }
    aJson.deleteItem(root);
    return resposta;
}

String Data::get_jsonstring(){
  return jsonstring;
}

void Data::check_json(String aux){
  
   int pos = aux.indexOf('{');
   if (pos != -1){
    Serial.print(pos);
    jsonstring = aux.substring(pos);
   }
   else{ 
    pos = aux.indexOf('[');
    if (pos != -1){
      jsonstring = aux.substring(pos);
    }
    else{
      jsonstring = "";
    }
     
    
   }
}

