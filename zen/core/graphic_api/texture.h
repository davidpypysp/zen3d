#pragma once

#include <memory>

namespace zen {

/**
 * handle contains graphic texture specific handles
 */
struct TextureHandle {
  // TODO: #if on vulkan
  unsigned int id;
};

enum TextureFormat { RED, RGB, RGBA };

enum TextureType { DIFFUSE, SPECULAR, NORMAL, HEIGHT };

/**
 * Texture info for constructing rendering data
 */
struct Texture {
  TextureHandle handle;
  TextureType type;
  std::string path;
};

} // namespace zen
