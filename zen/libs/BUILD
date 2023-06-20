

load("@rules_cc//cc:defs.bzl", "cc_library")
load("//:wasm.bzl", "zen_wasm_cc_binary")

package(default_visibility = ["//visibility:public"])


zen_wasm_cc_binary(
	name = "imgui_demo_wasm",
	srcs = ["imgui_demo_wasm.cc"],
	linkopts = [
		"--preload-file data",
	],
	additional_linker_inputs = [
		"//:data",
	],
	deps = [
		"@imgui"
	],
)

# gles + glfw + tinygltf + glm
zen_wasm_cc_binary(
    name = "triangle_demo_wasm",
    srcs = [
		"triangle_demo_wasm.cpp",
	],
  	copts = [ # gltf compile success opts
		"-Wno-error=unused-variable",
		"-Wno-error=tautological-constant-out-of-range-compare",
  	],
	deps = [
		"@glm//:glm",
		"@tinygltf//:tinygltf",
		":glog"
	],
)

cc_library(
	name = "gflag",
	deps = [
		"@com_github_google_gflag//:gflag"
	]
)

cc_library(
	name = "glog",
	deps = [
		"@com_github_google_glog//:glog"
	]
)

cc_library(
	name = "gtest_main",
	deps = [
		"@com_google_googletest//:gtest_main",
	],
)

