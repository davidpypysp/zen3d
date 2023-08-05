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
    srcs = ["window.cc"],
    hdrs = ["window.h"],
    deps = [
        ":gui_store",
        "@imgui",
    ],
)

cc_library(
    name = "scene_explorer",
    srcs = ["scene_explorer.cc"],
    hdrs = ["scene_explorer.h"],
    deps = [
        ":window",
        "//zen/core/base:logging",
    ],
)

cc_library(
    name = "object_inspector",
    srcs = ["object_inspector.cc"],
    hdrs = ["object_inspector.h"],
    deps = [
        ":window",
        "//zen/core/base:logging",
    ],
)

cc_library(
    name = "gui",
    srcs = ["gui.cc"],
    hdrs = ["gui.h"],
    deps = [
        ":object_inspector",
        ":scene_explorer",
    ],
)

cc_test(
    name = "gui_test",
    srcs = ["gui_test.cc"],
    deps = [
        ":gui",
        "//zen/libs:gtest_main",
    ],
)
