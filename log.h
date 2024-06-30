#pragma once

#include <fstream>
#include <string>

class Log {
 public:
  Log(std::string name);
  ~Log();

  void write(char* text);

 private:
  std::ofstream log_file_;
};
