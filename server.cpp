#include <cstring>
#include <iostream>
#include <fstream>
#include <random>
#include <sstream>

#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include "server.h"

#define PORT 6666
#define IP "127.0.0.1"
#define DOMAIN "http://xxxxxxxxx.xxx.com/"

Server::Server(std::string ip, int port) {
  // create socket
  if ((server_ = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
    std::cout << "FAILED TO CREATE SOCKET" << std::endl;
    exit(EXIT_FAILURE);
  }

  // attach socket to port
  int opt = 1;
  if (setsockopt(server_, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
    perror("setsockopt");
    exit(EXIT_FAILURE);
  }

  address_.sin_family = AF_INET;
  address_.sin_addr.s_addr = inet_addr(IP);
  address_.sin_port = htons(PORT);

  // bind socket to address and port
  if (bind(server_, (struct sockaddr *)&address_, sizeof(address_)) < 0) {
    close(server_);
    perror("bind failed");
    exit(EXIT_FAILURE);
  }

  // listen for incoming connections
  if (listen(server_, 3) < 0) {
    close(server_);
    perror("listen");
    exit(EXIT_FAILURE);
  }
}

void Server::send_url(std::string domain) {
  uuid_ = gen_uuid();
  std::string url = domain + uuid_;
  send(sock_, url.c_str(), url.length(), 0);
}

void Server::accept_conn() {
  // accept an incoming connection
  int addrlen = sizeof(sock_);
  if ((sock_ = accept(server_, (struct sockaddr *)&address_, (socklen_t*)&addrlen)) < 0) {
    close(server_);
    perror("accept connection");
    exit(EXIT_FAILURE);
  }
}

void Server::read_msg() {
  Log log(uuid_);
  char buffer[1024] = {0};
  while (true) {
    if (read(sock_, buffer, 1024) == 0) {
      return;
    } else {
      std::cout << buffer << std::endl;
      log.write(buffer);
    }
  }
}

// courtesy of SO
// TODO replace this
std::string Server::gen_uuid() {
  static std::random_device dev;
  static std::mt19937 rng(dev());

  std::uniform_int_distribution<int> dist(0, 15);

  const char *v = "0123456789abcdef";
  const bool dash[] = { 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0 };

  std::string id;
  for (int i = 0; i < 16; i++) {
    if (dash[i]) id += "-";
    id += v[dist(rng)];
    id += v[dist(rng)];
  }
  return id;
}

Log::Log(std::string name) {
  log_file_ = std::ofstream(name);
}

Log::~Log() {
  log_file_.close();
}

void Log::write(char* text) {
  log_file_ << text;
}

int main() {
  Server s = Server(IP, PORT);
  s.accept_conn();
  s.send_url(DOMAIN);
  s.read_msg();

  return 0;
}
