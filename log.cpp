#include "log.h"

Log::Log(std::string name) {
  log_file_ = std::ofstream(name);
}

Log::~Log() {
  log_file_.close();
}

void Log::write(char* text) {
  log_file_ << text;
}
