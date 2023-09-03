
### Install Bazel
https://bazel.build/install

Use npm install bazelisk which contains bazel command

```
npm install -g @bazel/bazelisk

npm install -g @bazel/buildifier
```


### Local Requirement
* install gcc11 g++11
* c++17

### Debug target

```
# generate target vscode debug config in launch.json
python3 debug.py //zen/demo:gltf_model_loader_demo
```


## run wasm server with dir and port (requires python3.7)
```
python3 wasm_server.py ./bazel-bin/zen/demo/imgui_demo_wasm/ -p 8080
```