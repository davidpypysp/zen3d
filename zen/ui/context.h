#ifndef GUI_IMGUI_CONTEXT_H_
#define GUI_IMGUI_CONTEXT_H_

#include "src/utils/ioc_container.h"

namespace kuro {

namespace gui {
class Context : public IocContainer {
 public:
  Context();
};

}  // namespace gui

}  // namespace kuro

#endif