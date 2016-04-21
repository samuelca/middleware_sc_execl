/*
codigo que possibilita a configuração do modulo bluetooth. Para ele entrar no modo que 
recebe comando at, é necessário seguir os passos abaixo:

-ligue o arduino e retire o jumper de alimentação do modulo bluetooth
-segure o botão do modulo, e enquanto faz isso, ligue o modulo conectando
o jumper responsavel pela alimentação.
-após ligar, basta soltar o botão e ele estará em modo de configuração
*/

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
  Serial.println("Digite os comandos AT :");  
  slave.begin(38400); 
  master.begin(38400); 
}  
    
void loop()  
{  
  // Read device output if available.  
  if (master.available()) 
  {  
     while(master.available()) 
     { // While there is more to be read, keep reading.  
       command += (char)master.read();  
       delay(10);
     }  
   Serial.println(command);  
   command = ""; // No repeats  
  }  
   
  // Read user input if available.  
  if (Serial.available())
  {  
    delay(10); // The DELAY!  
    master.write(Serial.read());  
  }  
}
