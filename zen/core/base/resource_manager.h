#pragma once

#include <iostream>
#include <memory>
#include <unordered_map>

namespace zen {

template <typename T> class ResourceManager {
public:
  ResourceManager() {}

  template <typename... Args> uint32_t Create(Args... args) {
    uint32_t handle = created_resource_count_++;
    resources_[handle] = std::make_unique<T>(args...);
    return handle;
  }

  T *Get(const uint32_t handle) const {
    if (resources_.find(handle) == resources_.end()) {
      return nullptr;
    }
    return resources_.at(handle).get();
  }

  void Remove(const uint32_t handle) { resources_.erase(handle); }

protected:
  uint32_t created_resource_count_ = 0;
  std::unordered_map<uint32_t, std::unique_ptr<T>> resources_;
};

} // namespace zen