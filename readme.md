
### Install Bazel
https://bazel.build/install

Use npm install bazelisk which contains bazel command

```
npm install -g @bazel/bazelisk
```


## run wasm server with dir and port (requires python3.7)
python3 wasm_server.py ./bazel-bin/zen/demo/imgui_demo_wasm/ -p 8080