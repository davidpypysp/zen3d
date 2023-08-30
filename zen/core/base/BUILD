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
        ":handle",
        ":transform",
        "@entt",
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
        ":resource_manager",
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

cc_library(
    name = "handle",
    hdrs = ["handle.h"],
)

cc_library(
    name = "resource_manager",
    hdrs = ["resource_manager.h"],
    deps = [
        ":handle",
    ],
)

cc_test(
    name = "resource_manager_test",
    srcs = ["resource_manager_test.cc"],
    deps = [
        ":resource_manager",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_library(
    name = "entity",
    hdrs = ["entity.h"],
    srcs = ["entity.cc"],
    deps = [
        "@entt",
    ],
)

cc_test(
    name = "entity_test",
    srcs = ["entity_test.cc"],
    deps = [
        ":entity",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_library(
    name = "scene_graph",
    hdrs = ["scene_graph.h"],
    srcs = ["scene_graph.cc"],
    deps = [
        ":entity",
    ],
)

cc_test(
    name = "scene_graph_test",
    srcs = ["scene_graph_test.cc"],
    deps = [
        ":scene_graph",
        "@com_google_googletest//:gtest_main",
    ],
)

