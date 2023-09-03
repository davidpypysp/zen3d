#pragma once

#include <string>

#include "imgui.h"

#include "zen/ui/imgui/gui_store.h"

namespace zen {

class Window {
public:
  explicit Window(const std::string& name);

  void RenderFrame(GuiStore& gui_store);

  virtual void Render(GuiStore& gui_store) = 0;

  virtual ~Window() = default;

  const std::string& name() const { return name_; }

protected:
  std::string name_;
};

} // namespace zen
