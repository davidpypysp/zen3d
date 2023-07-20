load("//:wasm.bzl", "zen_wasm_cc_binary")

package(default_visibility = ["//visibility:public"])

cc_library(
	name = "vertex",
	hdrs = ["vertex.h"],
	deps = [
		"//zen/core/math:math",
	]
)

cc_binary(
	name = "vertex_test",
	srcs = ["vertex_test.cc"],
	deps = [
		":vertex",
		"//zen/core/base:logging",
	]
)

cc_library(
	name = "geometry",
	hdrs = ["geometry.h"],
	deps = [
		"//zen/core/base:handle",
		":vertex",
	]
)

cc_test(
	name = "geometry_test",
	srcs = ["geometry_test.cc"],
	deps = [
		":geometry",
		"//zen/libs:gtest_main",
	]
)

cc_library(
	name = "triangle_geometry",
	hdrs = ["triangle_geometry.h"],
	deps = [
		":geometry",
	]
)

cc_library(
	name = "cube_geometry",
	hdrs = ["cube_geometry.h"],
	deps = [
		":geometry",
	]
)

cc_test(
	name = "cube_geometry_test",
	srcs = ["cube_geometry_test.cc"],
	deps = [
		":cube_geometry",
		"//zen/libs:gtest_main",
	]
)

cc_library(
	name = "texture",
	hdrs = ["texture.h"],
	deps = [
		"//zen/core/base:handle",
	]
)

cc_test(
	name = "texture_test",
	srcs = ["texture_test.cc"],
	deps = [
		":texture",
		"//zen/libs:gtest_main",
	]
)

cc_library(
	name = "shader_program",
	hdrs = ["shader_program.h"],
	deps = [
		"//zen/core/math:math",
	]
)

cc_test(
	name = "shader_test",
	srcs = ["shader_test.cc"],
	deps = [
		":shader_program",
		"//zen/libs:gtest_main",
	]
)

cc_library(
	name = "material",
	hdrs = ["material.h"],
	deps = [
		":shader_program",
		":camera",
		":render_api",
	]
)

cc_library(
	name = "simple_material",
	hdrs = ["simple_material.h"],
	srcs = ["simple_material.cc"],
	deps = [
		":material",
	]
)

cc_library(
	name = "mesh_flat_material",
	hdrs = ["mesh_flat_material.h"],
	srcs = ["mesh_flat_material.cc"],
	deps = [
		":material",
	]
)

cc_test(
	name = "mesh_flat_material_test",
	srcs = ["mesh_flat_material_test.cc"],
	deps = [
		":mesh_flat_material",
		"//zen/libs:gtest_main",
	]
)

cc_library(
	name = "mesh",
	hdrs = ["mesh.h"],
	srcs = ["mesh.cc"],
	deps = [
		":material",
		":geometry",
		"//zen/core/base:scene_node",
	]
)

cc_test(
	name = "mesh_test",
	srcs = ["mesh_test.cc"],
	deps = [
		":mesh",
		":simple_material",
		":triangle_geometry",
		"//zen/libs:gtest_main",
	]
)

cc_library(
	name = "camera",
	hdrs = ["camera.h"],
	srcs = ["camera.cc"],
	deps = [
		"//zen/core/math:math",
		"//zen/core/base:scene_node",
	]
)

cc_test(
	name = "camera_test",
	srcs = ["camera_test.cc"],
	deps = [
		":camera",
		"//zen/libs:gtest_main",
	]
)


cc_library(
	name = "render_api",
	srcs = ["render_api.h"],
	deps = [
		":shader_program",
		":texture",
		":vertex",
	]
)

cc_library(
	name = "gl_render_api",
	srcs = ["gl_render_api.cc"],
	hdrs = ["gl_render_api.h"],
	deps = [
		":render_api",
		":material",
	]
)

cc_library(
	name = "wasm_wrapper",
	hdrs = ["wasm_wrapper.h"],
)

cc_test(
	name = "gl_render_api_test",
	srcs = ["gl_render_api_test.cc"],
	deps = [
		":gl_render_api",
		"//zen/libs:gtest_main",
	]
)

zen_wasm_cc_binary(
    name = "gl_render_api_wasm_test",
    srcs = [
		"gl_render_api_wasm_test.cc",
	],
	deps = [
		":gl_render_api",
	]
)

cc_test(
	name = "shader_manager_test",
	srcs = ["shader_manager_test.cc"],
	deps = [
		":shader_manager",
		"//zen/libs:gtest_main",
	]
)

cc_library(
	name = "rendering_pipeline",
	srcs = ["rendering_pipeline.cc"],
	hdrs = ["rendering_pipeline.h"],
	deps = [
		":render_api",
		":mesh",
	]
)

cc_test(
	name = "rendering_pipeline_test",
	srcs = ["rendering_pipeline_test.cc"],
	deps = [
		":rendering_pipeline",
		":gl_render_api",
		"//zen/libs:gtest_main",
	]
)

cc_library(
	name = "renderer",
	srcs = ["renderer.cc"],
	hdrs = ["renderer.h"],
	deps = [
		":rendering_pipeline",
		":gl_render_api",
		":camera",
		"//zen/core/base:scene",
	]
)
