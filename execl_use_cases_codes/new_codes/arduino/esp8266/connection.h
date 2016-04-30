#include "AT.h"

class Connection{
  
  public:
  
  void find_network(String, String, const int);
  void set_mode(int, const int);
  void get_ip(const int);
  void set_multiple_connection(bool mult, const int timeout);
  void create_connection(String cipstart, const int timeout, int connectionId);
  void close_connection(String closeConnection, const int timeout, int connectionId);
 
};

