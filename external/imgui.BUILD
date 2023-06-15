cc_library(
    name = "imgui",
    srcs = glob(
        include = [
            "*.cpp",
            "*.h",
            "backends/*.h",
            "backends/imgui_impl_glfw.*",
            "backends/imgui_impl_opengl3.*",
        ],
    ),
	includes = [
		"backends",
	],
    visibility = ["//visibility:public"],
    alwayslink = 1,
    # linkopts = ["-lGL -lGLU -lglfw -ldl"],
)
