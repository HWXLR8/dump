#pragma once

#include <string>

#define PORT 6666
#define IP "127.0.0.1"
#define DOMAIN "http://xxxxxxxxx.xxx.com/"

class Server {
 public:
  Server();
  void send_url(std::string domain);
  void accept_conn();
  void read_msg();

 private:
  std::string gen_uuid();

  int server_;
  int sock_;
  std::string uuid_;
  struct sockaddr_in address_;
};
