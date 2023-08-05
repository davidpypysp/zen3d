
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include <iostream>

void loop() {}

extern "C" int main(int argc, char **argv) {
  std::cout << "something!!!" << std::endl;

#ifdef __EMSCRIPTEN__
  emscripten_set_main_loop(loop, 0, 1);
#endif

  return 0;
}