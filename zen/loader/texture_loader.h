#pragma once

#include <string>
#include <vector>

#include "src/core/renderer/graphic_api.h"
#include "src/core/renderer/texture.h"

namespace zen {
namespace core {

class TextureLoader {
public:
  TextureLoader();

  std::shared_ptr<Texture> LoadTexture(const std::string &path,
                                       const TextureType &type);

private:
  std::shared_ptr<TextureHandle> LoadTextureFromFile(const char *path);

  std::vector<std::shared_ptr<Texture>> texture_instances_;
};

} // namespace core
} // namespace zen
