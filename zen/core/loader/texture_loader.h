#pragma once

#include <string>
#include <vector>

#include "zen/core/graphic_api/graphic_api.h"

namespace zen {

class TextureLoader {
public:
  TextureLoader();

  std::shared_ptr<Texture> LoadTexture(const std::string &path,
                                       const TextureType &type,
                                       std::shared_ptr<GraphicAPI> graphic_api);

private:
  std::shared_ptr<TextureHandle>
  LoadTextureFromFile(const char *path,
                      std::shared_ptr<GraphicAPI> graphic_api);

  std::vector<std::shared_ptr<Texture>> texture_instances_;
};

} // namespace zen
