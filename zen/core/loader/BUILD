package(default_visibility = ["//visibility:public"])

cc_library(
    name = "texture_loader",
    srcs = ["texture_loader.cc"],
    hdrs = ["texture_loader.h"],
    deps = [
        "//zen/core/base:logging",
        "//zen/core/graphic_api",
        "//zen/core/graphic_api:texture",
        "@stb//:stb_image",
    ],
)

cc_library(
    name = "model_loader",
    srcs = ["model_loader.cc"],
    hdrs = ["model_loader.h"],
    deps = [
        ":texture_loader",
        "//zen/core/base:logging",
        "//zen/core/graphic_api",
        "//zen/core/renderer:mesh",
        "//zen/core/renderer:mesh_basic_material",
        "@assimp",
    ],
)

cc_binary(
    name = "model_loader_test",
    srcs = ["model_loader_test.cc"],
    data = [
        "//:data",
    ],
    linkopts = [
        "-lGL",
    ],
    deps = [
        ":model_loader",
        "//zen/core/graphic_api:opengl_api",
    ],
)


cc_library(
    name = "gltf_model_loader",
    srcs = ["gltf_model_loader.cc"],
    hdrs = ["gltf_model_loader.h"],
    copts = [
        # gltf compile success opts
        "-Wno-error=unused-variable",
        "-Wno-error=tautological-constant-out-of-range-compare",
    ],
   deps = [
        "//zen/core/base:logging",
        "//zen/core/base:scene",
        "//zen/core/base:transform",
        "//zen/core/renderer:mesh",
        "//zen/core/renderer:material_builder",
        "@tinygltf",
    ],
)

cc_binary(
    name = "gltf_model_loader_test",
    srcs = ["gltf_model_loader_test.cc"],
    data = [
        "//:data",
    ],
    deps = [
        ":gltf_model_loader",
    ],
)
