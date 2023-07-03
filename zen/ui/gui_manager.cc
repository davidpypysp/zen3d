#include "src/gui/imgui/gui_manager.h"

#include <iostream>

namespace kuro {

namespace gui {

GuiManager::GuiManager() {}

void GuiManager::Init() { InitWindows(); }

void GuiManager::Draw() {
  for (auto window : windows_) {
    window->RenderFrame();
  }
}

void GuiManager::InitWindows() {
  auto scene_explorer = AddWindow<SceneExplorer>("Scene Explorer");
  scene_explorer->RegisterGuiStore(gui_store_);
  auto scene_manager = engine_->GetInstance<SceneManager>();
  scene_explorer->RegisterSceneManager(scene_manager);

  auto object_inspector = AddWindow<ObjectInspector>("Object Inspector");
  object_inspector->RegisterGuiStore(gui_store_);
}

}  // namespace gui

}  // namespace kuro
