
#include <VirtualWire.h>

#define receive_pin 3

void setup()
{
    Serial.begin(9600);	// Debugging only
    Serial.println("setup");

    // Initialise the IO and ISR
    vw_set_rx_pin(receive_pin);
    vw_setup(2000);	 // Bits per sec
    vw_rx_start();       // Start the receiver PLL running
}

void loop()
{
    uint8_t buflen = VW_MAX_MESSAGE_LEN;
    uint8_t buf[VW_MAX_MESSAGE_LEN];
    
    if (vw_have_message()){
      delay(100);    
      if (vw_get_message(buf, &buflen)) // Non-blocking
      {
      	int i;
      
      	Serial.print("Recebido: ");
      	
      	for (i = 0; i < buflen; i++)
      	{
      	    Serial.print((char)buf[i]);
      	    
      	}
       Serial.println();
      }
   } 
}
