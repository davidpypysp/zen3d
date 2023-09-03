#pragma once

#include <string>

#include "imgui.h"

#include "zen/core/math/math.h"

namespace zen {

void InputTextComponent(const char* label, const std::string& text);

void Vector3Component(const char* label, math::vec3& v, const float min,
                      const float max);

} // namespace zen
