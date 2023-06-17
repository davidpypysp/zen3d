

load("@emsdk//emscripten_toolchain:wasm_rules.bzl", "wasm_cc_binary")

package(default_visibility = ["//visibility:public"])

DEFAULT_EMSCRIPTEN_LINKOPTS = [
    # LTO broken when using hermetic emsdk
    # "-flto",                            # Specify lto (has to be set on for compiler as well)
    "--bind",                           # Compiles the source code using the Embind bindings to connect C/C++ and JavaScript
    "--closure 1",                      # Run the closure compiler
    "-s MALLOC=emmalloc",               # Switch to using the much smaller implementation
    "-s ALLOW_MEMORY_GROWTH=0",         # Our example doesn't need memory growth
    "-s USE_PTHREADS=0",                # Disable pthreads
    "-s ASSERTIONS=0",                  # Turn off assertions
    "-s EXPORT_ES6=1",                  # Export as es6 module, used for rollup
    "-s MODULARIZE=1",                  # Allows us to manually invoke the initializatio of wasm
    "-s EXPORT_NAME=createModule",      # Not used, but good to specify
    "-s USE_ES6_IMPORT_META=0",         # Disable loading from import meta since we use rollup
    "-s SINGLE_FILE=1",                 # Pack all webassembly into base64
    "-s DISABLE_EXCEPTION_CATCHING=1",  # Disable all exception catching
    "-s NODEJS_CATCH_EXIT=0",           # We don't have a 'main' so disable exit() catching
]

WASM_LINKOPTS = [
    "-s WASM=1",                    # Specify wasm output
]

load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "func",
    hdrs = ["func.h"],
)



cc_binary(
    name = "hello-world-wasm.js",
    srcs = ["bindings.cpp"],
    # linkopts = DEFAULT_EMSCRIPTEN_LINKOPTS + WASM_LINKOPTS,
    linkopts = [
		"--std=c++11",
		"-Wall",
		"-Wextra",
		"-s WASM=1",
		"-s USE_SDL=2",
	],
    deps = [
        ":func",
    ],
)

wasm_cc_binary(
    name = "hello-world-wasm",
    cc_target = ":hello-world-wasm.js",
)

cc_binary(
    name = "app_main",
    srcs = ["app.cpp"],
    linkopts = [
		"--std=c++11",
		"-Wall",
		"-Wextra",
		"-s WASM=1",
		# "-s USE_SDL=2",
	],

)

wasm_cc_binary(
    name = "app_wasm",
    cc_target = ":app_main",
)

cc_binary(
    name = "imgui_demo",
    srcs = ["imgui_demo.cpp",
	],
    linkopts = [
		"--std=c++11",
		"-lGL",
		"-s USE_WEBGL2=1",
		"-s USE_GLFW=3",
		"-s FULL_ES3=1",
		"-s WASM=1",
		"-O2",
		"-sAssertion",
		"--preload-file data",
	],
	additional_linker_inputs = [
		"data",
	],
	deps = [
		"@imgui",
	],
)

wasm_cc_binary(
    name = "imgui_demo_wasm",
    cc_target = ":imgui_demo",
)

cc_binary(
	name = "stb_test",
	srcs = [
		"stb_test.cpp",
	],
    linkopts = [
		"--std=c++11",
		"-Wall",
		"-Wextra",
		"-s WASM=1",
		"-O2",
		"-sAssertion",
		"--preload-file data",
	],
	additional_linker_inputs = [
		"data",
	],
	deps = [
		"@stb//:stb_image",
	]
)

wasm_cc_binary(
    name = "stb_test_wasm",
    cc_target = ":stb_test",
)

cc_binary(
    name = "triangle_demo",
    srcs = [
		"triangle_demo.cpp",
	],
    linkopts = [
		"--std=c++11",
		"-lGL",
		"-s USE_WEBGL2=1",
		"-s USE_GLFW=3",
		"-s FULL_ES3=1",
		"-s WASM=1",
		"-Wextra",
		"-Wno-error=unused-variable",
		"-O2",
		"-sAssertion",
	],
  	copts = [
		"-Wno-error=unused-variable",
		"-Wno-error=tautological-constant-out-of-range-compare",
  	],
	deps = [
		"@glm//:glm",
		"@tinygltf//:tinygltf",
	],
)

wasm_cc_binary(
    name = "triangle_demo_wasm",
    cc_target = ":triangle_demo",
)