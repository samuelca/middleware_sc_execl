//UnB-UioT - Humidity and Temperature sensor

#include <dht.h>

#define dht_dpin A0 //A0 connected with the pin out, from the sensor

dht DHT; 

void setup()
{
  Serial.begin(9600);
  delay(1000);
}

void loop()
{
  DHT.read11(dht_dpin); //Read information from the sensor
  Serial.print("Umidade = ");
  Serial.print(DHT.humidity);
  Serial.print(" %  "); //space
  Serial.print("Temperatura = ");
  Serial.print(DHT.temperature); 
  Serial.println(" Celsius  ");

  //Measurements delay
  delay(2000);  
}
