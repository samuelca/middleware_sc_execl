#ifndef AT_H
#define AT_H  

#include <SoftwareSerial.h>
#include <Arduino.h>

class AT{

  private:
    SoftwareSerial * esp8266 = new SoftwareSerial(2,3);
  
  public:
  
    void initialize_serial();
    String sendCommand(String command, const int timeout);
    char* connected_client(int *tam);
    
};

#endif
