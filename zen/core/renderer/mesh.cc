#include "zen/core/renderer/mesh.h"

namespace zen {

Mesh::Mesh(const std::string &name, std::shared_ptr<Geometry> geometry,
           std::shared_ptr<Material> material)
    : SceneNode(name), geometry_(geometry), material_(material) {
  is_renderable_ = true;
}

} // namespace zen