#pragma once

#include <string>

std::string text() { return "abcdefg text"; }

class Greet {
public:
  /*
   * Greets the name
   */
  static std::string SayHello(const std::string &name) {
    return "greet: " + name;
  }
};