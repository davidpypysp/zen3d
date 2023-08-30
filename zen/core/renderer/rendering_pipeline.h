#pragma once

#include <memory>

#include "zen/core/base/scene_graph.h"
#include "zen/core/base/transform.h"
#include "zen/core/graphic_api/graphic_api.h"
#include "zen/core/renderer/camera.h"
#include "zen/core/renderer/mesh.h"

namespace zen {

class RenderingPipeline {
public:
  RenderingPipeline(std::shared_ptr<GraphicAPI> graphic_api);

  void InitMeshes(SceneGraph& scene_graph);

  void RenderMeshes(SceneGraph& scene_graph);

  void PrepareDraw(const Material& material, const Camera& camera,
                   const math::mat4& world_transform,
                   Transform& camera_transform);

  void DrawMesh(const Mesh& mesh);

  std::shared_ptr<GraphicAPI> graphic_api() { return graphic_api_; }

protected:
  std::shared_ptr<GraphicAPI> graphic_api_;
};

} //  namespace zen
