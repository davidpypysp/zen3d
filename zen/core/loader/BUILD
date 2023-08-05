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
