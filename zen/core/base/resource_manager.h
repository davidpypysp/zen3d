#pragma once

#include <iostream>
#include <memory>
#include <unordered_map>

namespace zen {

typedef uint32_t ResourceHandle;

template <typename T> class ResourceManager {
public:
  ResourceManager() {}

  template <typename... Args> inline ResourceHandle Create(Args... args) {
    ResourceHandle handle = GenerateHandle();
    resources_[handle] = std::make_unique<T>(args...);
    return handle;
  }

  inline T *Get(const ResourceHandle handle) const {
    if (resources_.find(handle) == resources_.end()) {
      return nullptr;
    }
    return resources_.at(handle).get();
  }

  inline void Remove(const ResourceHandle handle) { resources_.erase(handle); }

protected:
  inline ResourceHandle GenerateHandle() { return created_resource_count_++; }

  uint32_t created_resource_count_ = 0;
  std::unordered_map<ResourceHandle, std::unique_ptr<T>> resources_;
};

} // namespace zen