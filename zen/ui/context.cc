#include "src/gui/imgui/context.h"

#include "src/core/engine.h"
#include "src/gui/imgui/gui_manager.h"
#include "src/gui/imgui/gui_system.h"
#include "src/gui/imgui/gui_store.h"

namespace kuro {

namespace gui {

Context::Context() {
  std::shared_ptr<Engine> engine = Engine::Instance();
  Register<Engine>(engine);

  auto gui_store = Register<GuiStore>();

  auto gui_manager = Register<GuiManager>();
  gui_manager->RegisterEngine(engine);
  gui_manager->RegisterGuiStore(gui_store);
}

}  // namespace gui

}  // namespace kuro