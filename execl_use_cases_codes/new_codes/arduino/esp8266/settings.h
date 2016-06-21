#ifndef SETTINGS_H
#define SETTINGS_H


#include "client_connection.h"
#include "data.h"

//#define SSID "UIoT"
//#define PSWD "161S9PQ1"
//String serverip = "172.16.6.159";


#define SSID "UIoT"
#define PSWD "161S9PQ1"
#define porta 80
#define protocolo "TCP"
String serverip = "172.16.6.159";


//declarar se for cliente
Client_Connection * esp_client = new Client_Connection(SSID, PSWD, 1, 1, protocolo, serverip, porta);

//declarar se for servidor
//Server_Connection * esp_client = new Server_Connection(SSID, PSWD, 1, 1, protocolo, porta);

Data * dado = new Data();

#endif
