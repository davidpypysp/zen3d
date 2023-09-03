
#include "zen/ui/imgui/utils.h"

namespace zen {

void InputTextComponent(const char* label, const std::string& text) {
  ImGui::InputText(label, const_cast<char*>(text.c_str()), text.size());
}

void Vector3Component(const char* label, math::vec3& v, const float min,
                      const float max) {
  ImGui::SliderFloat3(label, &v[0], min, max);
}

} // namespace zen