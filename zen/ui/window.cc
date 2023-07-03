#include "src/gui/imgui/window.h"

namespace kuro {

namespace gui {

Window::Window(const std::string &name) : name_(name) {}

void Window::RenderFrame() {
  ImGui::Begin(name_.c_str());  // Create a window called "Hello, world!"
                                // and append into it.

  Render();

  ImGui::End();
}

}  // namespace gui

}  // namespace kuro
