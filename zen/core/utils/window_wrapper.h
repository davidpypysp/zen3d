#pragma once

#include <iostream>

#define GLFW_INCLUDE_ES3
#include <GLES3/gl3.h>
#include <GLFW/glfw3.h>

namespace zen {

struct GlobalWasmParams {
  bool success = false;
  GLFWwindow *window;
  int window_width = 1280;
  int window_height = 720;
};

/**
 * @brief Wrapper for local window creation and rendering
 */
class WindowWrapper {
public:
  WindowWrapper() {}

  virtual void Setup() {}

  virtual void Render() {}

  int Init() {
    UpdateWindowSize();

    if (InitGL()) {
      exit(1);
    }
    Setup();

    return 0;
  }

  void UpdateWindowSize() {
    // int width = GetCanvasWidth();
    // int height = GetCanvasHeight();

    // if (width != params_.window_width || height != params_.window_height) {
    //   params_.window_width = width;
    //   params_.window_height = height;
    //   glfwSetWindowSize(params_.window, params_.window_width,
    //                     params_.window_height);
    // }
  }

  void Loop() {
    while (!glfwWindowShouldClose(params_.window)) {
      UpdateWindowSize();

      // ------
      glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);

      // render
      // function inject here
      Render();

      // glfw: swap buffers and poll IO events (keys pressed/released, mouse
      // moved etc.)
      // -------------------------------------------------------------------------------
      glfwSwapBuffers(params_.window);
      glfwPollEvents();
    }
  }

  void Terminate() { glfwTerminate(); }

protected:
  int InitGL() {
    if (!glfwInit()) {
      fprintf(stderr, "Failed to initialize GLFW\n");
      return 1;
    }

    // need hints for local glfw initialization
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(
        GLFW_OPENGL_PROFILE,
        GLFW_OPENGL_CORE_PROFILE); // 3.2+
                                   // only
                                   // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,
                                   // GL_TRUE); // 3.0+ only

    glfwWindowHint(GLFW_OPENGL_PROFILE,
                   GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL

    // Open a window and create its OpenGL context
    params_.window = glfwCreateWindow(
        params_.window_width, params_.window_height, "zen3d", NULL, NULL);
    if (params_.window == NULL) {
      fprintf(stderr, "Failed to open GLFW window.\n");
      glfwTerminate();
      return 1;
    }
    glfwMakeContextCurrent(params_.window); // Initialize GLEW
    return 0;
  }

  GlobalWasmParams params_;
};

} // namespace zen