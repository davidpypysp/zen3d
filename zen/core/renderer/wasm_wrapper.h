#pragma once

#include <iostream>
#include <stdio.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

// #include <glad/glad.h>
#define GLFW_INCLUDE_ES3
#include <GLES3/gl3.h>
#include <GLFW/glfw3.h>

// Function used by c++ to get the size of the html canvas
EM_JS(int, GetCanvasWidth, (), { return Module.canvas.width; });

// Function used by c++ to get the size of the html canvas
EM_JS(int, GetCanvasHeight, (), { return Module.canvas.height; });

// Function called by javascript
EM_JS(void, ResizeCanvas, (), { js_resizeCanvas(); });

namespace zen {

struct GlobalWasmParams {
  bool success = false;
  GLFWwindow *window;
  int window_width;
  int window_height;
};

class WasmWrapper {
public:
  WasmWrapper() {}

  virtual void Setup() {}

  virtual void Render() {}

  int Init() {
    ResizeCanvas();
    UpdateWindowSize();

    InitGL();
    Setup();

    return 0;
  }

  void UpdateWindowSize() {
    int width = GetCanvasWidth();
    int height = GetCanvasHeight();

    if (width != params_.window_width || height != params_.window_height) {
      params_.window_width = width;
      params_.window_height = height;
      glfwSetWindowSize(params_.window, params_.window_width,
                        params_.window_height);
    }
  }

  void Loop() {
    UpdateWindowSize();

    // ------
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // render
    // function inject here
    Render();

    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved
    // etc.)
    // -------------------------------------------------------------------------------
    glfwSwapBuffers(params_.window);
    glfwPollEvents();
  }

  void Terminate() { glfwTerminate(); }

protected:
  int InitGL() {
    if (!glfwInit()) {
      fprintf(stderr, "Failed to initialize GLFW\n");
      return 1;
    }

    glfwWindowHint(GLFW_OPENGL_PROFILE,
                   GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL

    // Open a window and create its OpenGL context
    params_.window = glfwCreateWindow(
        params_.window_width, params_.window_height, "wasm window", NULL, NULL);
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

void WasmLoopImpl(void *manager) {
  static_cast<WasmWrapper *>(manager)->Loop();
}

void WasmSpin(WasmWrapper &manager) {
  manager.Init();
#ifdef __EMSCRIPTEN__
  emscripten_set_main_loop_arg(&WasmLoopImpl, &manager, 0, 1);
#endif
}

} // namespace zen