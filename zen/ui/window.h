#ifndef GUI_IMGUI_WINDOW_H_
#define GUI_IMGUI_WINDOW_H_

#include <string>

#include <imgui.h>

namespace kuro {

namespace gui {

class Window {
 public:
  explicit Window(const std::string &name);
  void RenderFrame();
  virtual void Render() = 0;

 protected:
  std::string name_;
};

}  // namespace gui

}  // namespace kuro

#endif  // GUI_IMGUI_WINDOW_H_
