#include "data.h"

void Data::data_warning(const int timeout, int connectionId)
{
  String cipSend = "AT+CIPSEND=";
  cipSend += connectionId;
  cipSend += ",";
  cipSend += data_value.length();
  cipSend += "\r\n";
  sendCommand(cipSend, timeout);
}

int Data::send_data(const int timeout)
{
  String resposta;
  resposta = sendCommand(data_value, timeout);
  this->check_json(resposta);
  if (this->jsonstring != "") {
    return 1;
  }
  else {
    return 0;
  }
}

int Data::get_timing() {
  return this->timing;
}

String Data::get_data() {
  return data_value;
}

void Data::set_data(String data)
{
  data_value = data;
}

bool Data::update(String metodo, int connectionId) {
  bool jsonflag = 0;
  String resposta;
  long code;

  update_url();
  create_http(metodo);
  data_warning(2000, connectionId);
  jsonflag = send_data(3000);

  // se houver conteudo json, chamar funcao para interpretar a mensagem (funcao parseJson)
  if (jsonflag == 1) {
    Serial.print("JSON STRING::::::::::: ");
    Serial.println(this->jsonstring);

    //mandar como parametro o tipo da variavel a ser analisada. s = string e n = numero.
    resposta = parseJson("\"code\": ", 'n');
    Serial.println(resposta);
    code = resposta.toInt();
    if (code == 200) {
      return 1;
    }
    else {
      return 0;
    }
  }
}

void Data::service(String metodo, int connectionId) {
  bool jsonflag = 0;
  String resposta;
  long code = 403;

  while (code != 200) {
    service_url();
    create_http(metodo);
    data_warning(2000, connectionId);
    jsonflag = send_data(3000);

    // se houver conteudo json, chamar funcao para interpretar a mensagem (funcao parseJson)
    if (jsonflag == 1) {
      Serial.print("JSON STRING::::::::::: ");
      Serial.println(this->jsonstring);

      //mandar como parametro o tipo da variavel a ser analisada. s = string e n = numero.
      resposta = parseJson("\"code\": ", 'n');
      Serial.println(resposta);
      code = resposta.toInt();
      if (code == 200) {
        resposta = parseJson("\"id_serv\": ", 'n');
        Serial.println(resposta);
        this->id_serv = resposta.toInt();

        resposta = parseJson("\"timing\": ", 'n');
        Serial.println(resposta);
        this->timing = resposta.toInt();
      }
    }
  }
}

void Data::authenticate(String metodo, int connectionId) {
  bool jsonflag = 0;
  String resposta;
  long code = 403;

  while (code != 200) {

    //fase de autenticacao
    authentication_url();
    create_http(metodo);
    data_warning(2000, connectionId);
    jsonflag = send_data(3000);

    // se houver conteudo json, chamar funcao para interpretar a mensagem (funcao parseJson)
    if (jsonflag == 1) {
      Serial.print("JSON STRING::::::::::: ");
      Serial.println(this->jsonstring);

      //mandar como parametro o tipo da variavel a ser analisada. s = string e n = numero.
      resposta = parseJson("\"code\": ", 'n');
      Serial.println(resposta);
      code = resposta.toInt();
      if (code == 200) {
        resposta = parseJson("\"id_token\": ", 'n');
        Serial.println(resposta);
        this->id_token = resposta.toInt();
      }
    }
  }


}

String Data::service_url(int id_token, int mac, String name, String inf_type, String unit, String description) {
  String URL = " /services/?id_token=";
  URL += id_token;
  URL += "&mac=";
  URL += mac;
  URL += "name=";
  URL += name;
  URL += "&inf_type=";
  URL += inf_type;
  URL += "&unit=";
  URL += unit;
  URL += "&description=";
  URL += description;
  this->url = URL;
}

String Data::update_url(int id_token, int mac, int id_serv, String value) {
  String URL = " /services/?id_token=";
  URL += id_token;
  URL += "&mac=";
  URL += mac;
  URL += "&id_serv=";
  URL += id_serv;
  URL += "&value=";
  URL += value;
  this->url = URL;
}

String Data::authentication_url(int id_chipset, int id_processor, String hd_serial, String host_name, int mac, String driver) {
  String URL = " /devices/?id_chipset=";
  URL += id_chipset;
  URL += "&id_processor=";
  URL += id_processor;
  URL += "&hd_serial=";
  URL += hd_serial;
  URL += "&host_name=";
  URL += host_name;
  URL += "&mac=";
  URL += mac;
  URL += "&driver=";
  URL += driver;
  this->url = URL;
}

void Data::create_http(String metodo)
{
  String http = metodo;
  http += this->url;
  http += " HTTP/1.1\r\n";
  //http += "Connection: close\r\n";
  //http += "Content-Lenght: ";
  //http += data.length();
  //http += "\r\n";
  http += "\r\n";
  this->set_data(http);

}



String Data::parseJson(String parametro, char tipo)
{
  int i = 0, j = 0, flag = 0, gap;
  String valor = "";
  int fim = jsonstring.length() - 1;
  char comp;

  if (tipo == 'n') {
    comp = ',';
    gap = 1;
  }
  else if (tipo == 's') {
    comp = '\"';
    gap = 2;
  }

  while (i != fim) {
    if (jsonstring[i] == parametro[j]) {
      j++;
      if (j == parametro.length()) {
        flag = 1;
        break;
      }
    }
    else {
      j = 0;
    }
    i++;
  }
  //se flag = 1, achou-se o parametro que se deseja obter a variavel
  if (flag == 1) {
    i += gap;
    while (jsonstring[i] != comp) {
      valor += jsonstring[i];
      i++;
    }
    return valor;
  }
}


String Data::get_jsonstring() {
  return jsonstring;
}

void Data::check_json(String aux) {
  //Funcao que verifica se tem conteudo json na resposta do servidor
  int initial_pos, final_pos;

  initial_pos = aux.indexOf('{');
  final_pos = aux.lastIndexOf('}');
  if ((initial_pos != -1) && (final_pos != -1)) {
    //resposta do servidor no formato json
    jsonstring = aux.substring(initial_pos, final_pos + 1);
  }
  else {
    initial_pos = aux.indexOf('[');
    final_pos = aux.lastIndexOf(']');
    if ((initial_pos != -1) && (final_pos != -1)) {
      //resposta do servidor no formato json
      jsonstring = aux.substring(initial_pos, final_pos + 1);
    }
    else {
      jsonstring = "";
    }
  }

}

