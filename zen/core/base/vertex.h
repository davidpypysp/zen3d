#pragma once

#include "zen/core/math/math.h"

namespace zen {
namespace core {

struct Vertex {
  math::vec3 position;
  math::vec3 normal;
  math::vec2 tex_coords;
  math::vec3 tangent;
  math::vec3 bitangent;
};

} // namespace core
} //  namespace zen
