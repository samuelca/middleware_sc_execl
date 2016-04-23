#include <SoftwareSerial.h>
    
//Define os pinos para a serial   
SoftwareSerial slave(2, 3); // RX, TX 

String command = ""; // Stores response of bluetooth device  
            // which simply allows n between each  
            // response.  98d3:31:308382

    
void setup()   
{  
  //Inicia a serial  
  Serial.begin(115200);  
  slave.begin(38400); 
  
}  
    
void loop()  
{  
  if (slave.available()) 
  {  
     while(slave.available()) 
     { // While there is more to be read, keep reading.  
       command += (char)slave.read();  
       delay(10);
     }
   Serial.print("Mensagem recebida: ");    
   Serial.println(command);  
   command = ""; // No repeats  
  }  
  
}
