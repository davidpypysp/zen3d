#pragma once

#include <memory>

#include "zen/core/base/handle.h"

namespace zen {

enum TextureType { DIFFUSE, SPECULAR, NORMAL, HEIGHT };

enum TextureFormat { RED, RGB, RGBA };

struct Texture {
  std::shared_ptr<Handle> handle;
  TextureType type;
  std::string path;
};

} // namespace zen
