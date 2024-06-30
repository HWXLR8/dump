#pragma once

#include <string>

#define PORT 6666
#define IP "127.0.0.1" // server IP address

class Client {
 public:
  Client();
  void send_msg(std::string msg);
  void read_url();
  void print_url();

 private:
  std::string read_exactly(int length);

  int sock_;
  std::string url_;
  int url_size_ = 61;
};
