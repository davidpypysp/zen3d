#if __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#endif

#include <cmath>
#include <iostream>
#include <string>

void loop() { std::cout << "emsd hello" << std::endl; }

int main() {
  std::cout << "working" << std::endl;
  emscripten_set_main_loop(loop, -1, 1);

  return 0;
}