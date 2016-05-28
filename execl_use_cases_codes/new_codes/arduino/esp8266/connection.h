#ifndef CONNECTION_H
#define CONNECTION_H  

#include "AT.h"


class Connection{

  protected:
   
   String Ipadress; 
   int Modo;
   String SSID;
   String PSWD;
   int Multipleconnection;
   String Protocolo;
   int connectionId;
   int porta;
   
  public:
  
  void reset(const int timeout);
  void find_network(const int timeout);
  void set_mode(const int timeout);
  void get_ip(const int timeout);
  void set_multiple_connection(const int timeout);
  void close_connection(const int timeout);
  int get_connection();
  String get_ip();
  int get_connectionId();
  void change_baud (int, const int);
  
};

#endif
