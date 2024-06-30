#pragma once

#include <string>

class Client {
 public:
  Client(std::string ip, int port);
  void send_msg(std::string msg);
  void read_url();
  void print_url();

 private:
  std::string read_exactly(int length);

  int sock_;
  std::string url_;
  int url_size_ = 61;
};
