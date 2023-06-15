workspace(name = "zen")

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")


http_archive(
    name = "aspect_rules_js",
    sha256 = "ad666b12324bab8bc151772bb2eff9aadace7bfd4d624157c2ac3931860d1c95",
    strip_prefix = "rules_js-1.11.1",
    url = "https://github.com/aspect-build/rules_js/archive/refs/tags/v1.11.1.tar.gz",
)

load("@aspect_rules_js//js:repositories.bzl", "rules_js_dependencies")

rules_js_dependencies()

load("@rules_nodejs//nodejs:repositories.bzl", "DEFAULT_NODE_VERSION", "nodejs_register_toolchains")

nodejs_register_toolchains(
    name = "nodejs",
    node_version = DEFAULT_NODE_VERSION,
)

# Emscripten toolchain
http_archive(
    name = "emsdk",
    # TODO: Remove repo_mapping when emsdk updates to rules_nodejs 5
    repo_mapping = {"@nodejs": "@nodejs_host"},
    sha256 = "147a2d72df34227bdb4ffedc587a8cb674a42269c40458f3f69ae37e8966cdc6",
    strip_prefix = "emsdk-3.1.41/bazel",
    urls = ["https://github.com/emscripten-core/emsdk/archive/refs/tags/3.1.41.tar.gz"],
)

load("@emsdk//:deps.bzl", emsdk_deps = "deps")

emsdk_deps()

load("@emsdk//:emscripten_deps.bzl", emsdk_emscripten_deps = "emscripten_deps")

emsdk_emscripten_deps()

http_archive(
    name = "imgui",
    build_file = "imgui.BUILD",
    sha256 = "96012e5dee6db965f45b04f27df58016815ec43e3214a7973cfe501b4a71395f",
    strip_prefix = "imgui-1.89.6",
    urls = ["https://github.com/ocornut/imgui/archive/refs/tags/v1.89.6.zip"],
)

http_archive(
    name = "stb",
    build_file = "stb.BUILD",
    sha256 = "673732b215f4009f99a16d262c796870de1618dd09f25f40a31b2315b91725fd",
    strip_prefix = "stb-052dce117ed989848a950308bd99eef55525dfb1",
    urls = ["https://github.com/nothings/stb/archive/052dce117ed989848a950308bd99eef55525dfb1.zip"],
)
