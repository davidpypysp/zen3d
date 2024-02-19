load("//build_defs:wasm.bzl", "zen_wasm_cc_binary")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "geometry",
    hdrs = ["geometry.h"],
    deps = [
        "//zen/core/graphic_api:geometry_handle",
        "//zen/core/graphic_api:vertex",
    ],
)

cc_test(
    name = "geometry_test",
    srcs = ["geometry_test.cc"],
    deps = [
        ":geometry",
        "//zen/libs:gtest_main",
    ],
)

cc_library(
    name = "geometry_builder",
    hdrs = ["geometry_builder.h"],
    deps = [
        ":geometry",
    ],
)

cc_library(
    name = "material",
    hdrs = ["material.h"],
    deps = [
        "//zen/core/graphic_api:shader",
        "//zen/core/graphic_api:graphic_api",
        ":camera",
    ],
)

cc_library(
    name = "mesh_basic_material",
    hdrs = ["mesh_basic_material.h"],
    deps = [
        ":material",
        "//zen/core/graphic_api:texture",
    ],
)

cc_library(
    name = "material_builder",
    hdrs = ["material_builder.h"],
    deps = [
        "mesh_basic_material",
        ":material",
    ],
)

cc_library(
    name = "mesh",
    hdrs = ["mesh.h"],
    deps = [
        ":geometry",
        ":material",
    ],
)

cc_test(
    name = "mesh_test",
    srcs = ["mesh_test.cc"],
    deps = [
        ":mesh",
        "//zen/libs:gtest_main",
    ],
)

cc_library(
    name = "camera",
    srcs = ["camera.cc"],
    hdrs = ["camera.h"],
    deps = [
        "//zen/core/math",
    ],
)

cc_test(
    name = "camera_test",
    srcs = ["camera_test.cc"],
    deps = [
        ":camera",
        "//zen/libs:gtest_main",
    ],
)

cc_library(
    name = "rendering_pipeline",
    srcs = ["rendering_pipeline.cc"],
    hdrs = ["rendering_pipeline.h"],
    deps = [
        ":camera",
        ":mesh",
        "//zen/core/base:logging",
        "//zen/core/base:scene",
        "//zen/core/base:transform",
        "//zen/core/graphic_api",
    ],
)

cc_test(
    name = "rendering_pipeline_test",
    srcs = ["rendering_pipeline_test.cc"],
    linkopts = [
        "-lGL",
    ],
    deps = [
        ":rendering_pipeline",
        "//zen/core/graphic_api:opengl_api",
        "//zen/libs:gtest_main",
    ],
)

cc_library(
    name = "renderer",
    srcs = ["renderer.cc"],
    hdrs = ["renderer.h"],
    deps = [
        ":rendering_pipeline",
        "//zen/core/base:logging",
        "//zen/core/graphic_api:opengl_api",
    ],
)
