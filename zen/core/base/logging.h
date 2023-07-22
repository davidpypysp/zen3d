#pragma once

#include <iostream>
#include <sstream>

namespace zen {

enum LOG_LEVEL {
  Debug = 0,
  Info = 1,
  Warning = 2,
  Error = 3,
};
const std::string LOG_LEVEL_STR[] = {"Debug", "Info", "Warning", "Error"};

// Usage: LOG(Info) << "hello world";

class Log {
public:
  Log(const LOG_LEVEL log_level = LOG_LEVEL::Info)
      : ss_(), log_level_(log_level) {}

  ~Log() {
    std::cout << "[" << LOG_LEVEL_STR[log_level_] << "]: " << ss_.str()
              << std::endl;
  }

  template <class T> Log &operator<<(const T &x) {
    ss_ << x;
    return *this;
  }

private:
  std::ostringstream ss_;
  LOG_LEVEL log_level_;
};

} // namespace zen
