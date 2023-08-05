
#include "zen/core/loader/texture_loader.h"

// Reference: https://github.com/nothings/stb/blob/master/stb_image.h#L4
// To use stb_image, add this in *one* C++ source file.
#define STB_IMAGE_IMPLEMENTATION
#include <iostream>
#include <stb_image.h>

namespace zen {

TextureLoader::TextureLoader() { stbi_set_flip_vertically_on_load(true); }

std::shared_ptr<Texture>
TextureLoader::LoadTexture(const std::string &path, const TextureType &type,
                           std::shared_ptr<GraphicAPI> graphic_api) {

  for (auto &instance : texture_instances_) {
    if (path.compare(instance->path) == 0) {
      return instance;
    }
  }

  auto texture = std::make_shared<Texture>();
  texture->handle = LoadTextureFromFile(path.c_str(), graphic_api);
  texture->type = type;
  texture->path = path;
  texture_instances_.push_back(texture);
  return texture;
};

std::shared_ptr<TextureHandle>
TextureLoader::LoadTextureFromFile(const char *path,
                                   std::shared_ptr<GraphicAPI> graphic_api) {
  std::shared_ptr<TextureHandle> texture_handle = nullptr;

  int width, height, component_num;
  unsigned char *data = stbi_load(path, &width, &height, &component_num, 0);
  if (data) {
    TextureFormat format = TextureFormat::RGB;
    if (component_num == 1) {
      format = TextureFormat::RED;
    } else if (component_num == 4) {
      format = TextureFormat::RGBA;
    }

    texture_handle =
        graphic_api->CreateTextureInstance(data, width, height, format);
  } else {
    std::cout << "Texture failed to load at path: " << path << std::endl;
  }
  stbi_image_free(data);
  return texture_handle;
}

} //  namespace zen