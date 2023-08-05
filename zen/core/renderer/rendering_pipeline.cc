#include "zen/core/renderer/rendering_pipeline.h"

// TODO: refactor initialization of this
#include "zen/core/renderer/mesh.h"

#include <iostream>
#include <memory>

namespace zen {

/**
 * @brief Construct a new Rendering Pipeline:: Rendering Pipeline object
 */
RenderingPipeline::RenderingPipeline(std::shared_ptr<GraphicAPI> graphic_api)
    : graphic_api_(graphic_api) {}

void RenderingPipeline::InitGeometry(std::shared_ptr<Geometry> geometry) {
  geometry->Setup(graphic_api_);
}

void RenderingPipeline::InitMaterial(std::shared_ptr<Material> material) {
  material->Setup(graphic_api_);
}

void RenderingPipeline::InitNode(std::shared_ptr<SceneNode> scene_node) {
  if (scene_node->is_renderable()) {
    // TODO: check if it is a mesh
    auto mesh = std::static_pointer_cast<Mesh>(scene_node);
    InitGeometry(mesh->geometry());
    InitMaterial(mesh->material());
  }

  for (auto &child : scene_node->children()) {
    InitNode(child);
  }
}

void RenderingPipeline::DrawNodes(std::shared_ptr<SceneNode> scene_node,
                                  std::shared_ptr<Camera> camera) {
  if (scene_node->is_renderable()) {
    // TODO: check if it is a mesh
    auto mesh = std::static_pointer_cast<Mesh>(scene_node);
    const auto &world_transform = mesh->transform().ModelMatrix();
    PrepareDraw(mesh->material(), camera, world_transform);
    DrawMesh(mesh->geometry(), mesh->material());
  }

  for (auto &child : scene_node->children()) {
    DrawNodes(child, camera);
  }
}

void RenderingPipeline::PrepareDraw(std::shared_ptr<Material> material,
                                    std::shared_ptr<Camera> camera,
                                    const math::mat4 &world_transform) {
  graphic_api_->EnableShaderProgram(material->shader_program);
  material->PrepareRender(graphic_api_, camera, world_transform);
}

void RenderingPipeline::DrawMesh(std::shared_ptr<Geometry> geometry,
                                 std::shared_ptr<Material> material) {
  graphic_api_->DrawMeshInstance(geometry->handle);
}

} //  namespace zen