#ifndef CONNECTION_H
#define CONNECTION_H  

#include "AT.h"

class Connection{

  private:

   String Ipadress; 
   int Modo;
   String SSID;
   String PSWD;
   int Multipleconnection;
   String Protocolo;
   String serverip;
   int connectionId;
   int porta;
   

  public:

  Connection(String param1, String param2, int param3, int param4, String param5, String param6, int param7)
  
  {
      SSID = param1;
      PSWD = param2;
      Modo = param3;
      Multipleconnection = param4;
      Protocolo = param5;
      serverip = param6;
      porta = param7;
      connectionId = 0;
      Ipadress = "";



  }





  void reset(const int timeout);
  void find_network(const int timeout);
  void set_mode(const int timeout);
  void get_ip(const int timeout);
  void set_multiple_connection(const int timeout);
  void create_connection(const int timeout);
  void close_connection(const int timeout);
  int get_connection();
  String get_ip();
  int get_connectionId();
  void set_connectionId(int valor);



};

#endif

