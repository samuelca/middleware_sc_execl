#include <Ethernet.h>
#include <SPI.h>


byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[] = { 192, 168, 1, 102 };
byte server[] = { 192, 168, 1, 109 };
char dado[] = "123"; //dado a enviar para servidor
//int tamanho_dado = dado.length();
EthernetClient client;

void setup()
{
  Ethernet.begin(mac, ip);
  Serial.begin(9600);

  delay(1000);

  Serial.println("connecting...");

  if (client.connect(server, 8000)) { //porta a se conectar
    Serial.println("connected");
    client.println("GET /search?q=arduino HTTP/1.0");
    client.println();
    Serial.println("Enviando dado...");
    client.write(dado);
    delay(5000);
  } else {
    Serial.println("connection failed");
  }
}

void loop()
{
  if (client.available()) {
    char c = client.read();
    Serial.print(c);
  }

  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();
    for(;;)
      ;
  }
}
