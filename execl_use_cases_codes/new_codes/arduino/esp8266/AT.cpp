String sendCommand(String command, const int timeout)
{
   String response = "";

   esp8266.print(command); // send the read character to the esp8266

   long int time = millis();

   while( (time+timeout) > millis())
   {
     while(esp8266.available())
     {

       // The esp has data so display its output to the serial window
       char c = esp8266.read(); // read the next character.
       response+=c;
     }
   }
   Serial.print(response);
   return response;
}

void ATgenerator()
{

}
