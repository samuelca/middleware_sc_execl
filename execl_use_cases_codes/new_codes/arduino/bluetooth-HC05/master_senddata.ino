#include <SoftwareSerial.h>
    
//Define os pinos para a serial   
SoftwareSerial master(2, 3); // RX, TX 

String command = ""; // Stores response of bluetooth device  
            // which simply allows n between each  
            // response.  98d3:31:308382

    
void setup()   
{  
  //Inicia a serial  
  Serial.begin(115200);  
  master.begin(38400); 
  
}  
    
void loop()  
{  
  command = "ola";
  master.print(command);
  delay(5000); 
}
