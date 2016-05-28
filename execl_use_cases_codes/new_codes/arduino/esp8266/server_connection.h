#ifndef SERVER_CONNECTION
#define SERVER_CONNECTION

#include "connection.h"

class Server_Connection : public Connection{
  private:


  public: 
  Server_Connection(String param1, String param2, int param3, int param4, String param5, int param6);
  void create_server(const int timeout);
  void set_connectionId(int valor);

};

#endif
