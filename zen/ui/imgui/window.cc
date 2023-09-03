#include "zen/ui/imgui/window.h"

namespace zen {

Window::Window(const std::string& name) : name_(name) {}

void Window::RenderFrame(GuiStore& gui_store) {
  ImGui::Begin(name_.c_str()); // Create a window called "Hello, world!"
                               // and append into it.

  Render(gui_store);

  ImGui::End();
}

} // namespace zen
