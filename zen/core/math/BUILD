package(default_visibility = ["//visibility:public"])

cc_library(
	name = "math",
	hdrs = ["math.h"],
	deps = [
		"@glm//:glm",
	]
)

cc_test(
	name = "math_test",
	srcs = ["math_test.cc"],
	# copts = ["-std=c++14"],
	deps = [
		":math",
		"//zen/libs:gtest_main",
	]
)