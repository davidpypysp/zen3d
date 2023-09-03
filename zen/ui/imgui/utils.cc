
#include "zen/ui/imgui/utils.h"

namespace zen {

void InputTextComponent(const char* label, const std::string& text) {
  ImGui::InputText(label, const_cast<char*>(text.c_str()), text.size());
}

} // namespace zen