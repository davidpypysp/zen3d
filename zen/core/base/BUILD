package(default_visibility = ["//visibility:public"])

cc_library(
    name = "logging",
    hdrs = ["logging.h"],
)

cc_library(
    name = "transform",
    hdrs = ["transform.h"],
    deps = [
        "//zen/core/math",
    ],
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
    srcs = ["scene_node.cc"],
    hdrs = ["scene_node.h"],
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
    ],
)

cc_library(
    name = "scene",
    srcs = ["scene.cc"],
    hdrs = ["scene.h"],
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
    ],
)

cc_binary(
    name = "model_loader_test",
    srcs = ["model_loader_test.cc"],
    deps = [
        "@assimp",
        # "//zen/libs:gtest_main",
    ],
)
