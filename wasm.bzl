load("@emsdk//emscripten_toolchain:wasm_rules.bzl", "wasm_cc_binary")

def zen_wasm_cc_binary(name, linkopts = [], **kwargs):
    native.cc_binary(
        name = "zen_cc_" + name,
        linkopts = [
            "--std=c++11",
            "-lGL",
            "-s USE_WEBGL2=1",
            "-s USE_GLFW=3",
            "-s FULL_ES3=1",
            "-s WASM=1",
            "-O2",
            "-sASSERTIONS",
            # "-fwasm-exceptions",
            # "-fexceptions",
        ] + linkopts,
        **kwargs,
    )
    wasm_cc_binary(
        name = name,
        cc_target = "zen_cc_" + name,
    )

