package(default_visibility = ["//visibility:public"])

stb_libraries = {
	"stb_image": "STB_IMAGE_IMPLEMENTATION",
}

[genrule(
	name = lib_name + "_c",
	outs = [lib_name + ".c"],
	cmd = "echo \"#define " + stb_libraries[lib_name] + "\n#include <" + lib_name + ".h>\" > $@",
) for lib_name in stb_libraries]

genrule(
	name = "nop_c",
	outs = ["nop.c"],
	cmd = "touch $@"
)

[cc_library(
	name = lib_name,
	srcs = [lib_name + ".c"],
	hdrs = [lib_name + ".h"],
	copts = [
		"-Wno-misleading-indentation",
		"-Wno-shift-negative-value",
		"-Wno-type-limits",
		"-Wno-unused-function",
	],
	includes = ["."],
) for lib_name in stb_libraries]