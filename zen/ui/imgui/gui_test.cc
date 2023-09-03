#include <gtest/gtest.h>

#include "zen/core/base/logging.h"
#include "zen/ui/imgui/gui.h"

namespace zen {

TEST(GuiTest, BasicAssertions) {
  LOG(Info) << "Gui Test";
  Gui gui;
}

} // namespace zen