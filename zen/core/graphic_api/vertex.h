#pragma once

#include "zen/core/math/math.h"

namespace zen {

struct Vertex {
  math::vec3 position;
  math::vec3 normal;
  math::vec2 tex_coords;
  math::vec3 tangent;
  math::vec3 bitangent;
};

} //  namespace zen
