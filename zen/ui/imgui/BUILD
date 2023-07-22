package(default_visibility = ["//visibility:public"])

cc_library(
	name = "gui_store",
	hdrs = ["gui_store.h"],
	deps = [
		"//zen/core/base:scene",
	],
)

cc_library(
	name = "window",
	hdrs = ["window.h"],
	srcs = ["window.cc"],
	deps = [
		":gui_store",
		"@imgui",
	],
)

cc_library(
	name = "scene_explorer",
	hdrs = ["scene_explorer.h"],
	srcs = ["scene_explorer.cc"],
	deps = [
		":window",
		"//zen/core/base:logging",
	]
)

cc_library(
	name = "object_inspector",
	hdrs = ["object_inspector.h"],
	srcs = ["object_inspector.cc"],
	deps = [
		":window",
	]
)

cc_library(
	name = "gui",
	hdrs = ["gui.h"],
	srcs = ["gui.cc"],
	deps = [
		":object_inspector",
		":scene_explorer",
	]
)

cc_test(
	name = "gui_test",
	srcs = ["gui_test.cc"],
	deps = [
		":gui",
		"//zen/libs:gtest_main",
	]
)




