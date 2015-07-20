
#include <glbinding/gl/gl.h>
#include <glbinding/Binding.h>
//dont load gl bindings from glfw
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "glm/gtc/type_ptr.hpp"

#include <stdlib.h>
#include <iostream>

#include <shader_loader.hpp>

using namespace gl;

// the rendering window
GLFWwindow* window;
// the main shader program
GLuint simple_program = 0;
// variables for fps computation
double last_second_time = 0;
unsigned frames_per_second = 0;
// camera matrices
glm::mat4 camera_projection;
glm::mat4 camera_view;
// model matrices
glm::mat4 model_matrix;

void reload_shader_programs() {
  try {
    GLuint new_program = shader_loader::program("../resources/shaders/simple.vert", "../resources/shaders/simple.frag");
    simple_program = new_program;
  }
  catch(std::exception& e) {
  }
}

void error_callback(int error, const char* description) {
  std::cerr << description << std::endl;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, 1);
  }
  else if(key == GLFW_KEY_R && action == GLFW_PRESS) {
    reload_shader_programs();
  }
}

void framebuffer_resize_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    // use smaller dimension as reference
    float smaller = width < height ? width : height;
    camera_projection = glm::ortho(-width / smaller, width / smaller, -height / smaller, height / smaller, 1.0f, -1.0f);
    camera_view = glm::mat4{};
}

void show_fps() {
  ++frames_per_second;
  double current_time = glfwGetTime();
  if(current_time - last_second_time >= 1.0) {
    std::string title{"OpenGL Framework - "};
    title += std::to_string(frames_per_second) + " fps";

    glfwSetWindowTitle(window, title.c_str());
    frames_per_second = 0;
    last_second_time = current_time;
  }

}

void render(GLFWwindow* window) {

  static glm::vec3 vertices[] =
  {
    {-0.6f, -0.4f, 0.f},
    {0.6f, -0.4f, 0.f},
    {0.f, 0.6f, 0.0f}
  };  

  static glm::vec3 colors[] =
  {
    {1.f, 0.f, 0.f},
    {0.f, 1.f, 0.f},
    {0.f, 0.f, 1.f}
  };  

  glMatrixMode(GL_PROJECTION);
  glLoadMatrixf(glm::value_ptr(camera_projection));

  glMatrixMode(GL_MODELVIEW);
  model_matrix = glm::rotate(glm::mat4{}, float(glfwGetTime()), glm::vec3{0.0f, 0.0f, 1.0f});
  glLoadMatrixf(glm::value_ptr(model_matrix));

  glBegin(GL_TRIANGLES);

  for(unsigned i = 0; i < 3; ++i) {
    glVertex3fv(glm::value_ptr(vertices[i]));
    glColor3fv(glm::value_ptr(colors[i]));
  }
  
  glEnd();
}

int main(void) {

  glfwSetErrorCallback(error_callback);

  if(!glfwInit()) {
    exit(EXIT_FAILURE);  
  }

  window = glfwCreateWindow(640, 480, "OpenGL Framework", NULL, NULL);

  if(!window) {
      glfwTerminate();
      exit(EXIT_FAILURE);
  }

  glfwMakeContextCurrent(window);
  // disable vsync
  glfwSwapInterval(0);
  glfwSetKeyCallback(window, key_callback);
  glfwSetFramebufferSizeCallback(window, framebuffer_resize_callback);

  // initialize glindings in this context
  glbinding::Binding::initialize();

  // initialize projection
  int width, height;
  glfwGetFramebufferSize(window, &width, &height);
  framebuffer_resize_callback(window, width, height);

  reload_shader_programs();

  // rendering loop
  while(!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    render(window);

    glfwSwapBuffers(window);
    glfwPollEvents();

    show_fps();
  }

  // free resources
  glfwDestroyWindow(window);
  glfwTerminate();
  exit(EXIT_SUCCESS);
}