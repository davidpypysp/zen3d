cc_library(
    name = "texture_loader",
    srcs = ["texture_loader.cc"],
    hdrs = ["texture_loader.h"],
    deps = [
        "//zen/core/graphic_api",
        "//zen/core/renderer:texture",
        "@stb//:stb_image",
    ],
)

cc_library(
    name = "model_loader",
    srcs = ["model_loader.cc"],
    hdrs = ["model_loader.h"],
    deps = [
        ":texture_loader",
        "//zen/core/graphic_api",
        "//zen/core/renderer:mesh",
        "//zen/core/renderer:mesh_basic_material",
        "@assimp",
    ],
)
