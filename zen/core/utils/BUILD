load("//build_defs:wasm.bzl", "zen_wasm_cc_binary")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "wasm_wrapper",
    hdrs = ["wasm_wrapper.h"],
)

cc_library(
    name = "window_wrapper",
    hdrs = ["window_wrapper.h"],
    linkopts = [
        "-lGL",
        "-ldl",
        "-lglfw",
    ],
)
