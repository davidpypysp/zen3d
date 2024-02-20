#pragma once

namespace zen {

/**
 * handle contains graphic geometry specific handles
 */
struct GeometryHandle {
  unsigned int vertex_size;

  // TODO: #if on vulkan
  unsigned int vao;
  unsigned int vbo;
  unsigned int ebo;
};

} // namespace zen