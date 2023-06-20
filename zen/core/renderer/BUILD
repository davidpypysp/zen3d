load("//:wasm.bzl", "zen_wasm_cc_binary")

package(default_visibility = ["//visibility:public"])

cc_library(
	name = "shader_program",
	hdrs = ["shader_program.h"],
)

cc_test(
	name = "shader_program_test",
	srcs = ["shader_program_test.cc"],
	deps = [
		"shader_program",
		"//zen/libs:gtest_main",
	]
)

cc_library(
	name = "render_api",
	srcs = ["render_api.h"],
	deps = [
		":shader_program",
		"//zen/core/base:geometry",
		"//zen/core/base:texture",
	]
)

cc_library(
	name = "gl_render_api",
	srcs = ["gl_render_api.cc"],
	hdrs = ["gl_render_api.h"],
	deps = [
		":render_api",
	]
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