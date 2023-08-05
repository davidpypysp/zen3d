load("//build_defs:wasm.bzl", "zen_wasm_cc_binary")

package(default_visibility = ["//visibility:public"])

zen_wasm_cc_binary(
    name = "minimal_rendering_pipeline_demo_wasm",
    srcs = [
        "minimal_rendering_pipeline_demo_wasm.cc",
    ],
    additional_linker_inputs = [
        "//:data",
        "//zen/core/shader:shader",
    ],
    linkopts = [
        "--preload-file data",
        "--preload-file zen/core/shader",
    ],
    deps = [
        "//zen/core/graphic_api:opengl_api",
        "//zen/core/renderer:cube_geometry",
        "//zen/core/renderer:mesh_flat_material",
        "//zen/core/renderer:rendering_pipeline",
        "//zen/core/renderer:simple_material",
        "//zen/core/renderer:triangle_geometry",
        "//zen/core/utils:wasm_wrapper",
    ],
)

zen_wasm_cc_binary(
    name = "minimal_renderer_demo_wasm",
    srcs = [
        "minimal_renderer_demo_wasm.cc",
    ],
    additional_linker_inputs = [
        "//:data",
        "//zen/core/shader:shader",
    ],
    linkopts = [
        "--preload-file data",
        "--preload-file zen/core/shader",
    ],
    deps = [
        "//zen/core/renderer",
        "//zen/core/renderer:cube_geometry",
        "//zen/core/renderer:mesh_flat_material",
        "//zen/core/renderer:simple_material",
        "//zen/core/renderer:triangle_geometry",
        "//zen/core/utils:wasm_wrapper",
    ],
)

cc_binary(
    name = "imgui_demo",
    srcs = [
        "imgui_demo.cc",
    ],
    data = [
        "//:data",
        "//zen/core/shader",
    ],
    deps = [
        "//zen/core/renderer",
        "//zen/core/renderer:cube_geometry",
        "//zen/core/renderer:mesh_flat_material",
        "//zen/core/renderer:simple_material",
        "//zen/core/renderer:triangle_geometry",
        "//zen/core/utils:window_wrapper",
        "//zen/ui/imgui:gui",
    ],
)

zen_wasm_cc_binary(
    name = "imgui_demo_wasm",
    srcs = [
        "imgui_demo_wasm.cc",
    ],
    additional_linker_inputs = [
        "//:data",
        "//zen/core/shader:shader",
    ],
    linkopts = [
        "--preload-file data",
        "--preload-file zen/core/shader",
    ],
    deps = [
        "//zen/core/renderer",
        "//zen/core/renderer:cube_geometry",
        "//zen/core/renderer:mesh_flat_material",
        "//zen/core/renderer:simple_material",
        "//zen/core/renderer:triangle_geometry",
        "//zen/core/utils:wasm_wrapper",
        "//zen/ui/imgui:gui",
    ],
)

cc_binary(
    name = "model_loader_demo",
    srcs = [
        "model_loader_demo.cc",
    ],
    data = [
        "//:data",
        "//zen/core/shader",
    ],
    deps = [
        "//zen/core/loader:model_loader",
        "//zen/core/renderer",
        "//zen/core/utils:window_wrapper",
        "//zen/ui/imgui:gui",
    ],
)
