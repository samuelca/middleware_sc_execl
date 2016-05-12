#ifndef DATA_H
#define DATA_H

#include "AT.h"

class Data
{
  private:

  String data_value;
      
  public:

  Data();
  String get_data();
  void set_data(String data);
  void data_warning(const int timeout, int connectionId);
  void send_data(const int timeout);
};

#endif
