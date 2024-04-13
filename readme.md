
### Install Bazel
https://bazel.build/install

Use npm install bazelisk which contains bazel command

```
# Contains bazel command
sudo npm install -g @bazel/bazelisk

# Contains BUILD file linter
sudo npm install -g @bazel/buildifier
```


### Local Requirement
* local build use clang
  * ubuntu: `sudo apt install clang`
* c++17
* python3
* glfw
  * ubuntu: `sudo apt-get install libglfw3-dev`


### Test minimal build
local gltf_loader
```
bazel run //zen/demo:gltf_model_loader_demo
```

wasm renderer demo
```
bazel build //zen/demo:minimal_renderer_demo_wasm

python3 wasm_server.py ./bazel-bin/zen/demo/minimal_renderer_demo_wasm/ -p 8080
```

### Debug target

```
# generate target vscode debug config in launch.json
python3 debug.py //zen/demo:gltf_model_loader_demo
```


### clang-format
```
sudo apt install clang-format
```


## run wasm server with dir and port (requires python3.7)
```
# run this first `bazel build //zen/demo:imgui_demo_wasm`
python3 wasm_server.py ./bazel-bin/zen/demo/imgui_demo_wasm/ -p 8080
```


### Vulkan Dependencies

Ubuntu (https://vulkan-tutorial.com/Development_environment#page_Vulkan-Packages)
```
sudo apt install vulkan-tools
sudo apt install libvulkan-dev
sudo apt install vulkan-validationlayers-dev spirv-tools

```

Install glslc:

- Download linux clang version from https://github.com/google/shaderc/blob/main/downloads.md.
- Extract `bin/glslc` and copy into `/usr/local/bin`

If met "glslc: /lib/x86_64-linux-gnu/libstdc++.so.6: version `GLIBCXX_3.4.32' not found (required by glslc)":
```
sudo add-apt-repository ppa:ubuntu-toolchain-r/test
sudo apt-get update
sudo apt-get install --only-upgrade libstdc++6
```

Example usages:
```
glslc zen/core/shader/vk_shader.vert -o zen/core/shader/vk_vert.spv
```
