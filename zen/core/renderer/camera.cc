#include "zen/core/renderer/camera.h"

namespace zen {

// constructor with vectors
Camera::Camera(const math::vec3& up, const float yaw, const float pitch)
    : front_(math::vec3(0.0, 0.0, -1.0)), movement_speed_(default_speed),
      mouse_sensitivity_(default_sensitivity), zoom_(default_zoom) {
  world_up_ = up;
  yaw_ = yaw;
  pitch_ = pitch;
  UpdateCameraVectors();
}

const math::mat4 Camera::GetPerspectiveMatrix(const float ratio) const {
  return math::perspective(math::radians(zoom_), ratio, 0.1f, 100.0f);
}

const math::mat4 Camera::GetViewMatrix(const math::vec3& position) const {
  return math::lookAt(position, position + front_, up_);
}

// calculates the front vector from the CameraPack's (updated) Euler Angles
void Camera::UpdateCameraVectors() {
  // calculate the new Front vector
  math::vec3 front;
  front.x = cos(math::radians(yaw_)) * cos(math::radians(pitch_));
  front.y = sin(math::radians(pitch_));
  front.z = sin(math::radians(yaw_)) * cos(math::radians(pitch_));
  front_ = math::normalize(front);
  // also re-calculate the Right and Up vector
  right_ = math::normalize(math::cross(
      front_, world_up_)); // normalize the vectors, because their length
                           // gets closer to 0 the more you look up or
                           // down which results in slower movement.
  up_ = math::normalize(cross(right_, front_));
}

} // namespace zen
