#ifndef DATA_H
#define DATA_H

#include "AT.h" 
//#include "settings.h"


class Data
{
  private:
  String data_value;
  String jsonstring;    
  String url;
  long id_token;
  long id_serv;
  long timing;
  
  public:

  String get_data();
  void set_data(String data);
  void data_warning(const int timeout, int connectionId);
  int send_data(const int timeout);
  void create_http(String metodo);
  String parseJson(String, char);
  String get_jsonstring();
  void check_json(String);
  String authentication_url(int id_chipset,int id_processor,String hd_serial,String host_name,int mac,String driver);
  void authenticate(String metodo, int connectionId);
  void service(String metodo, int connectionId);
  bool update(String metodo, int connectionId);
  int get_timing();
};

#endif
