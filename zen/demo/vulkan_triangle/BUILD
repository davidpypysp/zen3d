load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_binary(
    name = "triangle",
    srcs = glob(["*.cpp"]),
    data = [
        "//zen/demo/vulkan_triangle/shaders:vert_shader",
        "//zen/demo/vulkan_triangle/shaders:frag_shader",
    ],
    linkopts = [
        "-lX11",
        "-ldl",
        "-lpthread",
        "-lglfw",
    ],
    deps = [
        "@glm//:glm",
        "@rules_vulkan//vulkan:vulkan_cc_library"
    ],
)
