package(default_visibility = ["//visibility:public"])

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