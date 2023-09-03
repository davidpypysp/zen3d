#include <gtest/gtest.h>

#include "zen/core/base/logging.h"
#include "zen/ui/imgui/gui.h"

namespace zen {

TEST(GuiManagerTest, BasicAssertions) {
  LOG(Info) << "Gui Test";
  Gui gui;
}

} // namespace zen