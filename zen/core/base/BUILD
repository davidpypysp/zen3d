package(default_visibility = ["//visibility:public"])

cc_library(
	name = "handle",
	hdrs = ["handle.h"],

)

cc_library(
	name = "logging",
	hdrs = ["logging.h"],

)

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
		":logging",
	]
)

cc_library(
	name = "geometry",
	hdrs = ["geometry.h"],
	deps = [
		":handle",
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
	name = "texture",
	hdrs = ["texture.h"],
	deps = [
		":handle",
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
	name = "shader",
	hdrs = ["shader.h"],
	srcs = ["shader.cc"],
	deps = [
		"//zen/core/math:math",
	]
)

cc_test(
	name = "shader_test",
	srcs = ["shader_test.cc"],
	deps = [
		":shader",
		"//zen/libs:gtest_main",
	]
)

cc_library(
	name = "material",
	hdrs = ["material.h"],
	deps = [
		":shader",
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


cc_library(
	name = "camera",
	hdrs = ["camera.h"],
	srcs = ["camera.cc"],
	deps = [
		"//zen/core/math:math",
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
