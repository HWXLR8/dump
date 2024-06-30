#pragma once

#include <string>

class Server {
 public:
  Server(std::string ip, int port);
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

class Log {
 public:
  Log(std::string name);
  ~Log();

  void write(char* text);

 private:
  std::ofstream log_file_;
};
