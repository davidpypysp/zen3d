#pragma once

#include <memory>

namespace zen {

/**
 * handle contains graphic texture specific handles
 */
struct TextureHandle {};

enum TextureFormat { RED, RGB, RGBA };

enum TextureType { DIFFUSE, SPECULAR, NORMAL, HEIGHT };

/**
 * Texture info for constructing rendering data
 */
struct Texture {
  std::shared_ptr<TextureHandle> handle;
  TextureType type;
  std::string path;
};

} // namespace zen
