#include <iostream>

#include "zen/core/base/logging.h"
#include "zen/core/renderer/vertex.h"

namespace zen {

void test_vertex() {
  Vertex vertex;
  Log(Info) << "zen vertex"
            << " " << 13;
  Log(Info) << "zen vertex 2";
}

} // namespace zen

int main(int argc, char *argv[]) { zen::test_vertex(); }
