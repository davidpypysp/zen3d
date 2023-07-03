#pragma once

#include "zen/core/math/math.h"

namespace zen {

class Transform {
public:
  Transform(const math::vec3 &position = {0.0, 0.0, 0.0},
            const math::vec3 &eular_rotation = {0.0, 0.0, 0.0},
            const math::vec3 &scale = {1.0, 1.0, 1.0})
      : position_(position), eular_rotation_(eular_rotation), scale_(scale),
        is_dirty_(true) {}

  void ComputeModelMatrix() {
    model_matrix_ = GetLocalModelMatrix();
    is_dirty_ = false;
  }

  void ComputeModelMatrix(const math::mat4 &parent_global_model_matrix) {
    model_matrix_ = parent_global_model_matrix * GetLocalModelMatrix();
    is_dirty_ = false;
  }

  const math::mat4 &ModelMatrix() {
    if (is_dirty_) {
      ComputeModelMatrix();
    }
    return model_matrix_;
  }

  void SetLocalPosition(const math::vec3 &position) {
    position_ = position;
    is_dirty_ = true;
  }

  const math::vec3 &WorldPosition() const { return position_; }

  void SetWorldPosition(const math::vec3 &position) {
    position_ = position;
    is_dirty_ = true;
  }

  bool is_dirty() { return is_dirty_; }

protected:
  math::mat4 GetLocalModelMatrix() {
    const math::mat4 transform_x =
        math::rotate(math::mat4(1.0f), math::radians(eular_rotation_.x),
                     math::vec3(1.0f, 0.0f, 0.0f));
    const math::mat4 transform_y =
        math::rotate(math::mat4(1.0f), math::radians(eular_rotation_.y),
                     math::vec3(0.0f, 1.0f, 0.0f));
    const math::mat4 transform_z =
        math::rotate(math::mat4(1.0f), math::radians(eular_rotation_.z),
                     math::vec3(0.0f, 0.0f, 1.0f));

    // Y * X * Z
    const math::mat4 rotation_matrix = transform_y * transform_x * transform_z;

    // translation * rotation * scale (also know as TRS matrix)
    return math::translate(math::mat4(1.0f), position_) * rotation_matrix *
           math::scale(math::mat4(1.0f), scale_);
  }

  math::vec3 position_ = {0.0, 0.0, 0.0};
  math::vec3 eular_rotation_ = {0.0, 0.0, 0.0}; // In degrees
  math::vec3 scale_ = {1.0, 1.0, 1.0};

  math::mat4 model_matrix_ = math::mat4(1.0);
  bool is_dirty_ = true;
};

} // namespace zen
