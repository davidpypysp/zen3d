#include <stdio.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#define GLFW_INCLUDE_ES3
#include <GLES3/gl3.h>
#include <GLFW/glfw3.h>

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/string_cast.hpp"

#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "tiny_gltf.h"

#include <iostream>

GLFWwindow *g_window;
bool show_demo_window = true;
bool show_another_window = false;
int g_width;
int g_height;
unsigned int g_shader_program;
unsigned int g_VAO;

// Function used by c++ to get the size of the html canvas
EM_JS(int, canvas_get_width, (), { return Module.canvas.width; });

// Function used by c++ to get the size of the html canvas
EM_JS(int, canvas_get_height, (), { return Module.canvas.height; });

// Function called by javascript
EM_JS(void, resizeCanvas, (), { js_resizeCanvas(); });

void on_size_changed() { glfwSetWindowSize(g_window, g_width, g_height); }

const char *vertexShaderSource =
    "# version 300 es\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
const char *fragmentShaderSource =
    "# version 300 es\n"
    "precision mediump float;\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

void loop() {
  int width = canvas_get_width();
  int height = canvas_get_height();

  if (width != g_width || height != g_height) {
    g_width = width;
    g_height = height;
    on_size_changed();
  }

  // render
  // ------
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  // draw our first triangle
  glUseProgram(g_shader_program);
  glBindVertexArray(g_VAO); // seeing as we only have a single g_VAO there's no
                            // need to bind it every time, but we'll do so to
                            // keep things a bit more organized
  // draw 1 triangle
  glDrawArrays(GL_TRIANGLES, 0, 6);
  // draw 2 triangle -> cube
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  // glBindVertexArray(0); // no need to unbind it every time

  // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved
  // etc.)
  // -------------------------------------------------------------------------------
  glfwSwapBuffers(g_window);

  glfwPollEvents();

  // int display_w, display_h;
  // glfwMakeContextCurrent(g_window);
  // glfwGetFramebufferSize(g_window, &display_w, &display_h);
  // glViewport(0, 0, display_w, display_h);
  // glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
  // glClear(GL_COLOR_BUFFER_BIT);

  // ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  // glfwMakeContextCurrent(g_window);
}

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

void init_world() {
  glm::vec3 pos(1, 2, 3);
  std::cout << "pos: " << glm::to_string(pos) << std::endl;

  tinygltf::Model model;
  tinygltf::TinyGLTF loader;
  std::cout << model.meshes.size() << std::endl;

  // build and compile our shader program
  // ------------------------------------
  // vertex shader
  unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);
  // check for shader compile errors
  int success;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
              << infoLog << std::endl;
  }
  // fragment shader
  unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);
  // check for shader compile errors
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
              << infoLog << std::endl;
  }
  // link shaders
  g_shader_program = glCreateProgram();
  glAttachShader(g_shader_program, vertexShader);
  glAttachShader(g_shader_program, fragmentShader);
  glLinkProgram(g_shader_program);
  // check for linking errors
  glGetProgramiv(g_shader_program, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(g_shader_program, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
              << infoLog << std::endl;
  }
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  // set up vertex data (and buffer(s)) and configure vertex attributes
  // ------------------------------------------------------------------
  float vertices[] = {
      0.5f,  0.5f,  0.0f, // top right
      0.5f,  -0.5f, 0.0f, // bottom right
      -0.5f, -0.5f, 0.0f, // bottom left
      -0.5f, 0.5f,  0.0f  // top left
  };
  unsigned int indices[] = {
      // note that we start from 0!
      0, 1, 3, // first Triangle
      1, 2, 3  // second Triangle
  };
  unsigned int VBO, EBO;
  glGenVertexArrays(1, &g_VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);
  // bind the Vertex Array Object first, then bind and set vertex buffer(s), and
  // then configure vertex attributes(s).
  glBindVertexArray(g_VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
               GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  // note that this is allowed, the call to glVertexAttribPointer registered VBO
  // as the vertex attribute's bound vertex buffer object so afterwards we can
  // safely unbind
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  // remember: do NOT unbind the EBO while a g_VAO is active as the bound
  // element buffer object IS stored in the g_VAO; keep the EBO bound.
  // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  // You can unbind the g_VAO afterwards so other g_VAO calls won't accidentally
  // modify this g_VAO, but this rarely happens. Modifying other VAOs requires a
  // call to glBindVertexArray anyways so we generally don't unbind VAOs (nor
  // VBOs) when it's not directly necessary.
  glBindVertexArray(0);

  // uncomment this call to draw in wireframe polygons.
  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

int init() {
  init_gl();
  init_world();
  return 0;
}

void quit() { glfwTerminate(); }

extern "C" int main(int argc, char **argv) {
  g_width = canvas_get_width();
  g_height = canvas_get_height();
  if (init() != 0)
    return 1;

  std::cout << "something!!!" << std::endl;

  auto a = loop;
  auto b = []() {};
  auto c = &b;

#ifdef __EMSCRIPTEN__
  emscripten_set_main_loop(b, 0, 1);
#endif

  quit();

  return 0;
}
