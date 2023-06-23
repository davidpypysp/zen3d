#include "src/core/renderer/rendering_pipeline.h"

#include <memory>

// #include "src/core/base/mesh_basic_material.h"
// #include "src/core/base/mesh_flat_material.h"

namespace zen {

RenderingPipeline::RenderingPipeline() {}

void RenderingPipeline::Setup() {
  // auto mesh_flat_shader =
  //     render_api_->CreateShaderProgram(MeshFlatMaterial::shader_handle);
  // shader_manager_->SetShaderProgram(MeshFlatMaterial::shader_handle,
  //                                   mesh_flat_shader);
  // auto mesh_basic_shader =
  //     render_api_->CreateShaderProgram(MeshBasicMaterial::shader_handle);
  // shader_manager_->SetShaderProgram(MeshBasicMaterial::shader_handle,
  //                                   mesh_basic_shader);
}

void RenderingPipeline::PrepareDraw(const Camera &camera) {
  auto shader_program =
      shader_manager_->GetShaderProgram(MeshBasicMaterial::shader_handle);
  render_api_->EnableShaderProgram(shader_program);

  // TODO: turn ratio to window height/width
  constexpr float kRatio = 3600.0 / 1800.0;

  render_api_->SetShaderMat4Param(shader_program, "projection",
                                  camera.GetPerspectiveMatrix(kRatio));
  render_api_->SetShaderMat4Param(
      shader_program, "view", camera_comp->GetViewMatrix(camera.translation()));
}

void RenderingPipeline::DrawMesh(const Geometry &geometry,
                                 const Material &material) {
  auto shader_program =
      shader_manager_->GetShaderProgram(material->GetShaderHandle());

  // TODO: refactor material selection pipeline
  if (auto mesh_basic_material =
          std::dynamic_pointer_cast<MeshBasicMaterial>(material)) {
    // use material
    unsigned int texture_num = 0;
    if (mesh_basic_material->diffuse_map) {
      render_api_->SetShaderIntParam(shader_program, "texture_diffuse",
                                     texture_num);
      render_api_->EnableTextureUnit(texture_num++,
                                     mesh_basic_material->diffuse_map->handle);
    }
    if (mesh_basic_material->specular_map) {
      render_api_->SetShaderIntParam(shader_program, "texture_specular",
                                     texture_num);
      render_api_->EnableTextureUnit(texture_num++,
                                     mesh_basic_material->specular_map->handle);
    }
    if (mesh_basic_material->normal_map) {
      render_api_->SetShaderIntParam(shader_program, "texture_normal",
                                     texture_num);
      render_api_->EnableTextureUnit(texture_num++,
                                     mesh_basic_material->normal_map->handle);
    }
    if (mesh_basic_material->height_map) {
      render_api_->SetShaderIntParam(shader_program, "texture_height",
                                     texture_num);
      render_api_->EnableTextureUnit(texture_num++,
                                     mesh_basic_material->height_map->handle);
    }
  }

  render_api_->DrawMeshInstance(geometry.handle);
}

void RenderingPipeline::DrawSceneNode(std::shared_ptr<SceneNode> scene_node) {
  scene_node->UpdateTransforms();
  auto shader_program =
      shader_manager_->GetShaderProgram(MeshBasicMaterial::shader_handle);
  render_api_->SetShaderMat4Param(shader_program, "model",
                                  scene_node->WorldTransform());

  for (auto component : scene_node->GetComponents()) {
    if (auto mesh_comp = std::dynamic_pointer_cast<MeshComp>(component)) {
      // visual comp pass data to pipeline
      DrawMesh(mesh_comp->mesh_data());
    }
  }

  // recursively pass child nodes
  for (auto child_node : scene_node->child_nodes()) {
    DrawSceneNode(child_node);
  }
}

void RenderingPipeline::DrawFrame(std::shared_ptr<SceneNode> root_node,
                                  std::shared_ptr<SceneNode> camera_node) {
  PrepareDraw(camera_node);
  DrawSceneNode(root_node);
}

} //  namespace zen