#pragma once

#include <math.h>

// glm dependencies
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/euler_angles.hpp"
#include "glm/gtx/matrix_decompose.hpp"
#include "glm/gtx/string_cast.hpp"

namespace zen {

namespace math {
using namespace glm;

constexpr float r2d = 180.0 / M_PI;
constexpr float d2r = M_PI / 180.0;

} // namespace math

} // namespace zen
