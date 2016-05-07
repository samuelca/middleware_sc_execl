#include <VirtualWire.h>

#define transmit_pin 3

void setup()
{
    pinMode(13,OUTPUT);  
    Serial.begin(9600);	  // Debugging only
    Serial.println("setup");
    vw_set_tx_pin(transmit_pin); 
    vw_setup(2000);	 // Bits per sec
}

void loop()
{
    char msg[] = "hello";

    digitalWrite(13, true); // Flash a light to show transmitting
    vw_send((uint8_t *)msg, strlen(msg));
    vw_wait_tx(); // Wait until the whole message is gone
    digitalWrite(13, false);
    delay(5000);
}
