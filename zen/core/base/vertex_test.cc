#include <iostream>

#include "zen/core/base/logging.h"
#include "zen/core/base/vertex.h"

namespace zen {

void test_vertex() {
  core::Vertex vertex;
  Log(Info) << "zen vertex"
            << " " << 13;
  Log(aInfo) << "zen vertex 2";
}

} // namespace zen

int main(int argc, char *argv[]) { zen::test_vertex(); }
