#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "client.h"

#define PORT 6666
#define IP "127.0.0.1" // server IP address

Client::Client(std::string ip, int port) {
  sock_ = 0;
  struct sockaddr_in serv_addr;

  // create socket fd
  if ((sock_ = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("create socket");
    exit(EXIT_FAILURE);
  }

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(PORT);

  // convert addr to binary
  if (inet_pton(AF_INET, IP, &serv_addr.sin_addr) <= 0) {
    perror("address conversion");
    exit(EXIT_FAILURE);
  }

  // connect to server
  if (connect(sock_, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
    perror("server connection");
    exit(EXIT_FAILURE);
  }
}

void Client::send_msg(std::string msg) {
  // send msg to server
  send(sock_, msg.c_str(), msg.size(), 0);
}

void Client::read_url() {
  url_ = read_exactly(url_size_);
}

void Client::print_url() {
  std::cout << "\n\nYour log has been uploaded to: " << std::endl;
  std::cout << url_ << std::endl;
}

std::string Client::read_exactly(int length) {
  std::string buff(url_size_, '\0');
  int total_read = 0;
  int bytes_read = 0;

  while (total_read < length) {
    bytes_read = read(sock_, &buff[total_read], length - total_read);
    total_read += bytes_read;
  }

  return buff;
}

int main() {
  Client client = Client(IP, PORT);

  client.read_url();

  while (true) {
    std::string line;
    std::getline(std::cin, line);
    line += '\n';
    std::cout << line;;
    client.send_msg(line);
    if (std::cin.eof()) {
      break;
    }
  }

  client.print_url();

  return 0;
}
