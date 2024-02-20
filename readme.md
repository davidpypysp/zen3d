
### Install Bazel
https://bazel.build/install

Use npm install bazelisk which contains bazel command

```
npm install -g @bazel/bazelisk

npm install -g @bazel/buildifier
```


### Local Requirement
* local build use clang
  * ubuntu: `apt install clang` 
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


## run wasm server with dir and port (requires python3.7)
```
python3 wasm_server.py ./bazel-bin/zen/demo/imgui_demo_wasm/ -p 8080
```