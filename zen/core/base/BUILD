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
	name = "transform",
	hdrs = ["transform.h"],
	deps = [
		"//zen/core/math:math",
	]
)

cc_test(
	name = "transform_test",
	srcs = ["transform_test.cc"],
	deps = [
		":transform",
		"//zen/libs:gtest_main",
	],
)

cc_library(
	name = "scene_node",
	hdrs = ["scene_node.h"],
	srcs = ["scene_node.cc"],
	deps = [
		":transform",
	],
)

cc_test(
	name = "scene_node_test",
	srcs = ["scene_node_test.cc"],
	deps = [
		":scene_node",
		"//zen/libs:gtest_main",
	]
)


cc_library(
	name = "scene",
	hdrs = ["scene.h"],
	srcs = ["scene.cc"],
	deps = [
		":scene_node",
	],
)

cc_test(
	name = "scene_test",
	srcs = ["scene_test.cc"],
	deps = [
		":scene",
		"//zen/libs:gtest_main",
	]
)