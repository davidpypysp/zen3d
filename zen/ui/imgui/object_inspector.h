#pragma once

#include "zen/ui/imgui/window.h"

namespace zen {

class ObjectInspector : public Window {
public:
  explicit ObjectInspector(const std::string& name);

  void Render(GuiStore& gui_store) override;
};

} // namespace zen
