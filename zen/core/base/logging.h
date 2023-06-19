#pragma once

#include <iostream>
#include <sstream>

namespace zen {

enum LOG_LEVEL {
  Info = 1,
  Warning = 2,
  Error = 3,
};

class Log {
public:
  Log(const LOG_LEVEL log_level = LOG_LEVEL::Info)
      : ss_(), log_level_(log_level) {}

  ~Log() { std::cout << ss_.str() << std::endl; }

  template <class T> Log &operator<<(const T &x) {
    ss_ << x;
    return *this;
  }

private:
  std::ostringstream ss_;
  LOG_LEVEL log_level_;
};

} // namespace zen
