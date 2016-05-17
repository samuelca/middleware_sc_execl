/* Codigo para ser usado no ESP sem comando AT, usando a IDE Arduino;
É possível fazer o esp receber dados do arduino pela porta serial, porém deve
colocar Rx -> Tx e Tx -> Rx . Vale lembrar que quando programa o esp sem comando AT,
deve colocá-lo em modo de gravação, com Rx -> Rx e Tx -> Tx. Depois da gravação, se for
receber dados do arduino, tem que inverter os pinos. */



#include <ESP8266WiFi.h>
 
const char* ssid     = "dlink-9FC8";
const char* password = "xpqap49352";
 
const char* host = "192.168.0.180";
 
void setup() {
  Serial.begin(9600);
  delay(10000);
 
  // We start by connecting to a WiFi network
 
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
 

 
void loop() {
  String resposta = "";
  int flag;
  delay(5000);
  Serial.print("connecting to ");
  Serial.println(host);
  
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int Port = 8000;
  if (!client.connect(host, Port)) {
    Serial.println("connection failed");
    return;
  }
  flag=0;
  while (Serial.available()){
    char c =   Serial.read();
    resposta += c;
    flag = 1;
  }
  //Serial.println(resposta);
  if (flag) client.print(resposta);
  delay(50);
  resposta = "";
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  
  Serial.println();
  Serial.println("closing connection");
  
}
