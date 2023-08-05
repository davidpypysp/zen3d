#pragma once

#include <memory>

#include "zen/core/graphic_api/graphic_api.h"
#include "zen/core/renderer/camera.h"
#include "zen/core/renderer/geometry.h"
#include "zen/core/renderer/material.h"

namespace zen {

class RenderingPipeline {
public:
  RenderingPipeline(std::shared_ptr<GraphicAPI> graphic_api);

  void InitGeometry(std::shared_ptr<Geometry> geometry);

  void InitMaterial(std::shared_ptr<Material> material);

  void InitNode(std::shared_ptr<SceneNode> scene_node);

  void DrawNodes(std::shared_ptr<SceneNode> scene_node,
                 std::shared_ptr<Camera> camera);

  void PrepareDraw(std::shared_ptr<Material> material,
                   std::shared_ptr<Camera> camera,
                   const math::mat4 &world_transform);

  void DrawMesh(std::shared_ptr<Geometry> geometry,
                std::shared_ptr<Material> material);

  std::shared_ptr<GraphicAPI> graphic_api() { return graphic_api_; }

protected:
  std::shared_ptr<GraphicAPI> graphic_api_;
};

} //  namespace zen
