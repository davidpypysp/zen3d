load("@emsdk//emscripten_toolchain:wasm_rules.bzl", "wasm_cc_binary")

# https://github.com/emscripten-core/emsdk/blob/61c35abc7aa63d83341f47effeea69dacd8b41b7/bazel/README.md

def zen_wasm_cc_binary(name, linkopts = [], **kwargs):
    native.cc_binary(
        name = "zen_cc_" + name,
        linkopts = [
            "-lGL",
            "-s USE_WEBGL2=1",
            "-s USE_GLFW=3",
            "-s FULL_ES3=1",
            "-s WASM=1",
            "-O2",
            "-sASSERTIONS",
            "--profiling-funcs",
        ] + linkopts,
        **kwargs
    )
    wasm_cc_binary(
        name = name,
        cc_target = "zen_cc_" + name,
    )
