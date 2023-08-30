#pragma once

#include <vector>

#include "zen/core/math/math.h"

namespace zen {

// Default camera values
const float default_yaw = -90.0;
const float default_pitch = 0.0;
const float default_speed = 2.5;
const float default_sensitivity = 0.1;
const float default_zoom = 45.0;

// An abstract camera class that processes input and calculates the
// corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class Camera {
public:
  // camera Attributes
  math::vec3 front_;
  math::vec3 up_;
  math::vec3 right_;
  math::vec3 world_up_;

  // euler Angles
  float yaw_;
  float pitch_;

  // camera options
  float movement_speed_;
  float mouse_sensitivity_;
  float zoom_;

  float zoom() const { return zoom_; }

  // constructor with vectors
  Camera(const math::vec3& up = math::vec3(0.0, 1.0, 0.0),
         const float yaw = default_yaw, const float pitch = default_pitch);

  const math::mat4 GetPerspectiveMatrix(const float ratio) const;

  // returns the view matrix calculated using Euler Angles and the LookAt Matrix
  const math::mat4 GetViewMatrix(const math::vec3& position) const;

private:
  // calculates the front vector from the Camera's (updated) Euler Angles
  void UpdateCameraVectors();
};

} //  namespace zen
