#include "zen/core/base/mesh_flat_material.h"

namespace zen {

std::shared_ptr<Shader> MeshFlatMaterial::shader =
    std::make_shared<Shader>("mesh_flat_shader", "mesh.vert", "mesh_flat.frag");

} //  namespace zen