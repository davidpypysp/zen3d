#pragma once

#include <memory>

namespace zen {

enum TextureType { DIFFUSE, SPECULAR, NORMAL, HEIGHT };

struct Texture {
  std::shared_ptr<TextureHandle> handle;
  TextureType type;
  std::string path;
};

} // namespace zen
