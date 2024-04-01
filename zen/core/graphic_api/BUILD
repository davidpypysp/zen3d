load("//build_defs:wasm.bzl", "zen_wasm_cc_binary")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "geometry_handle",
    hdrs = ["geometry_handle.h"],
)

cc_library(
    name = "texture",
    hdrs = ["texture.h"],
)

cc_library(
    name = "shader",
    hdrs = ["shader.h"],
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
        ":shader",
        "//zen/libs:gtest_main",
    ],
)

cc_library(
    name = "graphic_api",
    srcs = ["graphic_api.h"],
    deps = [
        ":geometry_handle",
        ":shader",
        ":texture",
        ":vertex",
    ],
)

cc_library(
    name = "opengl_api",
    srcs = ["opengl_api.cc"],
    hdrs = ["opengl_api.h"],
    deps = [
        ":graphic_api",
        "//zen/core/base:logging",
    ],
)

cc_test(
    name = "opengl_api_test",
    srcs = ["opengl_api_test.cc"],
    linkopts = ["-lGL"],
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

cc_library(
    name = "vulkan_api",
    srcs = ["vulkan_api.cc"],
    hdrs = ["vulkan_api.h"],
    linkopts = [
        "-lX11",
        "-ldl",
        "-lpthread",
        "-lglfw",
    ],
    deps = [
        ":graphic_api",
        "//zen/core/base:logging",
        "@rules_vulkan//vulkan:vulkan_cc_library",
    ],
)

cc_test(
    name = "vulkan_api_test",
    srcs = ["vulkan_api_test.cc"],
    data = [
        "//zen/core/shader:shader_spv",
    ],
    deps = [
        ":vulkan_api",
        "//zen/libs:gtest_main",
    ],
)

cc_binary(
    name = "vulkan_main",
    srcs = ["vulkan_main.cc"],
    linkopts = [
        "-lX11",
        "-ldl",
        "-lpthread",
        "-lglfw",
    ],
    deps = [
        "@rules_vulkan//vulkan:vulkan_cc_library",
    ],
)
