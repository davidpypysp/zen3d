load("//:wasm.bzl", "zen_wasm_cc_binary")

package(default_visibility = ["//visibility:public"])

zen_wasm_cc_binary(
    name = "minimal_rendering_pipeline_demo_wasm",
    srcs = [
		"minimal_rendering_pipeline_demo_wasm.cc",
	],
	deps = [
		"//zen/core/renderer:rendering_pipeline",
		"//zen/core/renderer:gl_render_api",
		"//zen/core/renderer:triangle_geometry",
		"//zen/core/renderer:simple_material",
		"//zen/core/renderer:mesh_flat_material",
		"//zen/core/renderer:cube_geometry",
		"//zen/core/renderer:wasm_wrapper",
	],
	linkopts = [
		"--preload-file data",
	],
	additional_linker_inputs = [
		"//:data",
	],
	data = [
		"//zen/core/shader:shader",
	]
)


zen_wasm_cc_binary(
    name = "minimal_renderer_demo_wasm",
    srcs = [
		"minimal_renderer_demo_wasm.cc",
	],
	deps = [
		"//zen/core/renderer:renderer",
		"//zen/core/renderer:triangle_geometry",
		"//zen/core/renderer:simple_material",
		"//zen/core/renderer:mesh_flat_material",
		"//zen/core/renderer:cube_geometry",
		"//zen/core/renderer:wasm_wrapper",
	],
	linkopts = [
		"--preload-file data",
	],
	additional_linker_inputs = [
		"//:data",
	],
	data = [
		"//zen/core/shader:shader",
	]
)

zen_wasm_cc_binary(
    name = "imgui_demo_wasm",
    srcs = [
		"imgui_demo_wasm.cc",
	],
	deps = [
		"//zen/core/renderer:renderer",
		"//zen/core/renderer:triangle_geometry",
		"//zen/core/renderer:simple_material",
		"//zen/core/renderer:mesh_flat_material",
		"//zen/core/renderer:cube_geometry",
		"//zen/core/renderer:wasm_wrapper",
		"//zen/ui/imgui:gui",
	],
	linkopts = [
		"--preload-file data",
	],
	additional_linker_inputs = [
		"//:data",
	],
)

