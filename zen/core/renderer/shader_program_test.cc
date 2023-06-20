#include <gtest/gtest.h>

#include "zen/core/renderer/shader_program.h"

TEST(ShaderProgram, BasicAssertions) {
  zen::ShaderProgram shader_program("s1", "s1.vert", "s1.frag", "s1.geo");
}