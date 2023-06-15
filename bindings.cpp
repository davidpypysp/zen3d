#include <emscripten/bind.h>

#include "func.h"

using namespace emscripten;

EMSCRIPTEN_BINDINGS(Hello_World) {
  emscripten::class_<Greet>("Greet").constructor<>().class_function(
      "SayHello", &Greet::SayHello);
}