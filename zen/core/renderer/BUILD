load("//build_defs:wasm.bzl", "zen_wasm_cc_binary")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "geometry",
    hdrs = ["geometry.h"],
    deps = [
        "//zen/core/graphic_api",
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
    name = "triangle_geometry",
    hdrs = ["triangle_geometry.h"],
    deps = [
        ":geometry",
    ],
)

cc_library(
    name = "cube_geometry",
    hdrs = ["cube_geometry.h"],
    deps = [
        ":geometry",
    ],
)

cc_test(
    name = "cube_geometry_test",
    srcs = ["cube_geometry_test.cc"],
    deps = [
        ":cube_geometry",
        "//zen/libs:gtest_main",
    ],
)

cc_library(
    name = "material",
    hdrs = ["material.h"],
    deps = [
        ":camera",
        "//zen/core/graphic_api",
    ],
)

cc_library(
    name = "simple_material",
    srcs = ["simple_material.cc"],
    hdrs = ["simple_material.h"],
    deps = [
        ":material",
    ],
)

cc_library(
    name = "mesh_flat_material",
    srcs = ["mesh_flat_material.cc"],
    hdrs = ["mesh_flat_material.h"],
    deps = [
        ":material",
    ],
)

cc_test(
    name = "mesh_flat_material_test",
    srcs = ["mesh_flat_material_test.cc"],
    deps = [
        ":mesh_flat_material",
        "//zen/libs:gtest_main",
    ],
)

cc_library(
    name = "mesh_basic_material",
    srcs = ["mesh_basic_material.cc"],
    hdrs = ["mesh_basic_material.h"],
    deps = [
        ":material",
    ],
)

cc_library(
    name = "mesh",
    srcs = ["mesh.cc"],
    hdrs = ["mesh.h"],
    deps = [
        ":geometry",
        ":material",
        "//zen/core/base:scene_node",
    ],
)

cc_test(
    name = "mesh_test",
    srcs = ["mesh_test.cc"],
    deps = [
        ":mesh",
        ":simple_material",
        ":triangle_geometry",
        "//zen/libs:gtest_main",
    ],
)

cc_library(
    name = "camera",
    srcs = ["camera.cc"],
    hdrs = ["camera.h"],
    deps = [
        "//zen/core/base:scene_node",
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
        ":mesh",
        "//zen/core/base:logging",
        "//zen/core/graphic_api",
    ],
)

cc_test(
    name = "rendering_pipeline_test",
    srcs = ["rendering_pipeline_test.cc"],
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
        ":camera",
        ":rendering_pipeline",
        "//zen/core/base:logging",
        "//zen/core/base:scene",
        "//zen/core/graphic_api:opengl_api",
    ],
)
