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
const std::string LOG_LEVEL_STR[] = {"DEBUG", "INFO", "WARNING", "ERROR"};

// Usage: LOG(Info) << "hello world";
#define LOG(level) zen::Logging(level, __FILE__, __LINE__)

class Logging {
public:
  Logging(const LOG_LEVEL log_level = LOG_LEVEL::Info,
          const char *file = __FILE__, const int line = __LINE__)
      : ss_(), log_level_(log_level), file_(file), line_(line) {}

  ~Logging() {
    std::cout << "[" << LOG_LEVEL_STR[log_level_] << "][" << file_ << ":"
              << line_ << "] " << ss_.str() << std::endl;
  }

  template <class T> Logging &operator<<(const T &x) {
    ss_ << x;
    return *this;
  }

private:
  std::ostringstream ss_;
  const LOG_LEVEL log_level_;
  const char *file_;
  const int line_;
};

} // namespace zen
