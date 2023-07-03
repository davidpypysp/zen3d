#include "src/gui/imgui/gui_system.h"

#include <stdio.h>
// [Win32] Our example includes a copy of glfw3.lib pre-compiled with VS2010 to
// maximize ease of testing and compatibility with old VS compilers. To link
// with VS2010-era libraries, VS2015+ requires linking with
// legacy_stdio_definitions.lib, which we do using this pragma. Your own project
// should not be affected, as you are likely to link with a newer binary of GLFW
// that is adequate for your version of Visual Studio.
#if defined(_MSC_VER) && (_MSC_VER >= 1900) && \
    !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>

#include "src/core/io/rect_window.h"

namespace kuro {

namespace gui {

using RectWindow = core::RectWindow;

static void glfw_error_callback(int error, const char *description) {
  fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

GuiSystem::GuiSystem() {
  context_ = std::make_shared<Context>();
  engine_ = context_->Resolve<Engine>();
  gui_manager_ = context_->Resolve<GuiManager>();
}

int GuiSystem::Init() {
  const unsigned int window_width = 3600, window_height = 1800;

  glfwSetErrorCallback(glfw_error_callback);
  if (!glfwInit()) return 1;

    // Decide GL+GLSL versions
#if __APPLE__
  // GL 3.2 + GLSL 150
  const char *glsl_version = "#version 150";
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);  // Required on Mac
#else
  const char *glsl_version = "#version 330";
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(
      GLFW_OPENGL_PROFILE,
      GLFW_OPENGL_CORE_PROFILE);  // 3.2+
                                  // only
                                  // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,
                                  // GL_TRUE); // 3.0+ only
#endif

  // Create window with graphics context
  gl_window_ =
      glfwCreateWindow(window_width, window_height, "kuro3d", NULL, NULL);
  if (gl_window_ == NULL) {
    return 1;
  }
  glfwMakeContextCurrent(gl_window_);
  glfwSwapInterval(1);  // Enable vsync

  auto engine_window = engine_->GetInstance<RectWindow>();
  glfwSetFramebufferSizeCallback(
      gl_window_, [](GLFWwindow *window, int width, int height) {
        // Do Something
        std::cout << "framebuffer size = "
                  << "width=" << width << "height=" << height << std::endl;
        // TODO: figure out how to pass variable into this lambda
        auto engine_window = Engine::Instance()->GetInstance<RectWindow>();
        engine_window->SetSize(width, height);
        glViewport(0, 0, width, height);
      });

  // Initialize OpenGL loader
  bool err = gladLoadGL() == 0;

  //     glbinding::initialize([](const char *name) { return
  //     (glbinding::ProcAddress)glfwGetProcAddress(name); });
  if (err) {
    fprintf(stderr, "Failed to initialize OpenGL loader!\n");
    return 1;
  }

  engine_->Init();
  engine_window->SetSize(window_width, window_height);

  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  (void)io;
  io.FontGlobalScale = 2.5f;
  // io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable
  // Keyboard Controls io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad; //
  // Enable Gamepad Controls

  // Setup Dear ImGui style
  ImGui::StyleColorsDark();
  // ImGui::StyleColorsClassic();

  // Setup Platform/Renderer bindings
  ImGui_ImplGlfw_InitForOpenGL(gl_window_, true);
  ImGui_ImplOpenGL3_Init(glsl_version);
}

int GuiSystem::Run() {
  Init();
  gui_manager_->Init();

  // Main loop
  while (!glfwWindowShouldClose(gl_window_)) {
    glfwPollEvents();

    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // 1. Show the big demo window (Most of the sample code is in
    // ImGui::ShowDemoWindow()! You can browse its code to learn more about
    // Dear ImGui!).
    bool show_demo_window = true;
    ImGui::ShowDemoWindow(&show_demo_window);

    Loop();

    // Rendering
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(gl_window_);
  }

  glfwTerminate();
  return 0;
}

void GuiSystem::Loop() {
  engine_->Draw();
  gui_manager_->Draw();
}

GuiSystem::~GuiSystem() {
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
}
}  // namespace gui

}  // namespace kuro
