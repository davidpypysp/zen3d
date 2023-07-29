#include <stdio.h>

#ifdef __EMSCRIPTEN__
#define EM_LOG_CONSOLE 0
#include <emscripten.h>
#endif

#define GLFW_INCLUDE_ES3
#include <GLES3/gl3.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "zen/core/graphic_api/opengl_api.h"

GLFWwindow *g_window;
bool show_demo_window = true;
bool show_another_window = false;
int g_width;
int g_height;

// Function used by c++ to get the size of the html canvas
EM_JS(int, canvas_get_width, (), { return Module.canvas.width; });

// Function used by c++ to get the size of the html canvas
EM_JS(int, canvas_get_height, (), { return Module.canvas.height; });

// Function called by javascript
EM_JS(void, resizeCanvas, (), { js_resizeCanvas(); });

void on_size_changed() { glfwSetWindowSize(g_window, g_width, g_height); }

int init_gl() {
  if (!glfwInit()) {
    fprintf(stderr, "Failed to initialize GLFW\n");
    return 1;
  }

  glfwWindowHint(GLFW_OPENGL_PROFILE,
                 GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL

  // Open a window and create its OpenGL context
  int canvasWidth = g_width;
  int canvasHeight = g_height;
  g_window =
      glfwCreateWindow(canvasWidth, canvasHeight, "WebGui Demo", NULL, NULL);
  if (g_window == NULL) {
    fprintf(stderr, "Failed to open GLFW window.\n");
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(g_window); // Initialize GLEW

  return 0;
}

int init() { return 0; }

void quit() { glfwTerminate(); }

extern "C" int main(int argc, char **argv) {

  g_width = canvas_get_width();
  g_height = canvas_get_height();
  if (init_gl() != 0) {
    return 1;
  }

  zen::OpenGLAPI gl_render_api;

  quit();

  return 0;
}
