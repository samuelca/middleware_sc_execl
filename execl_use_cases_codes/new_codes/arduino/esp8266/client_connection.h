#ifndef CLIENT_CONNECTION
#define CLIENT_CONNECTION

#include "connection.h"

class Client_Connection : public Connection {
  private:
  String serverip;

  public:
  Client_Connection(String param1, String param2, int param3, int param4, String param5, String param6, int param7);
  void create_connection(const int timeout);      

};

#endif
