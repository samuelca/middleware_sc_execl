//codigo ainda em teste! Não é possível usar duas portas 
//software serial ao mesmo tempo 

#include <SoftwareSerial.h>
    
//Define os pinos para a serial   
SoftwareSerial slave(2, 3); // RX, TX 
SoftwareSerial master(4,5); 
String command = ""; // Stores response of bluetooth device  
            // which simply allows n between each  
            // response.  98d3:31:308382

    
void setup()   
{  
  //Inicia a serial  
  Serial.begin(115200);  
  slave.begin(38400); 
  master.begin(38400); 
}  
    
void loop()  
{  
  float temp = analogRead(A0)*0.1;  
  master.write((byte)temp);
  if (slave.available()) 
  {  
     while(slave.available()) 
     { // While there is more to be read, keep reading.  
       command += (char)slave.read();  
       delay(10);
     }  
   Serial.println(command);  
   command = ""; // No repeats  
  }  
   
  /*if (Serial.available())
  {  
    delay(10); // The DELAY!  
    master.write(Serial.read());  
  } */
  delay(5000); 
}
