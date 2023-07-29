load("//build_defs:wasm.bzl", "zen_wasm_cc_binary")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "handle",
    hdrs = ["handle.h"],
)

cc_library(
    name = "shader_program",
    hdrs = ["shader_program.h"],
)

cc_library(
    name = "vertex",
    hdrs = ["vertex.h"],
    deps = [
        "//zen/core/math",
    ],
)

cc_test(
    name = "shader_program_test",
    srcs = ["shader_program_test.cc"],
    deps = [
        ":shader_program",
        "//zen/libs:gtest_main",
    ],
)

cc_library(
    name = "graphic_api",
    srcs = ["graphic_api.h"],
    deps = [
        ":handle",
        ":shader_program",
        ":vertex",
    ],
)

cc_library(
    name = "opengl_api",
    srcs = ["opengl_api.cc"],
    hdrs = ["opengl_api.h"],
    deps = [
        ":graphic_api",
    ],
)

cc_test(
    name = "opengl_api_test",
    srcs = ["opengl_api_test.cc"],
    deps = [
        ":opengl_api",
        "//zen/libs:gtest_main",
    ],
)

zen_wasm_cc_binary(
    name = "opengl_api_wasm_test",
    srcs = [
        "opengl_api_wasm_test.cc",
    ],
    deps = [
        ":opengl_api",
    ],
)
