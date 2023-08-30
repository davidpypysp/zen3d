#pragma once

#include <iostream>
#include <memory>
#include <unordered_map>

#include "zen/core/base/handle.h"

namespace zen {

template <typename T, typename Handle = ResourceHandle> class ResourceManager {
public:
  ResourceManager() {}

  template <typename... Args> inline Handle Create(Args... args) {
    Handle handle = GenerateHandle();
    resources_.insert({handle, Entity(args...)});
    return handle;
  }

  inline T *Get(const Handle handle) const {
    if (resources_.find(handle) == resources_.end()) {
      return nullptr;
    }
    return resources_.at(handle).get();
  }

  inline void Remove(const Handle handle) { resources_.erase(handle); }

protected:
  inline Handle GenerateHandle() { return ++created_resource_count_; }

  uint32_t created_resource_count_ = 0;
  std::unordered_map<Handle, T> resources_;
};

} // namespace zen