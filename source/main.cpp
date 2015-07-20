
#include <glbinding/gl/gl.h>
#include <glbinding/Binding.h>
//dont load gl bindings from glfw
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <glm/vec3.hpp>
#include "glm/gtc/type_ptr.hpp"

#include <stdlib.h>
#include <iostream>

#include <shader_loader.hpp>

using namespace gl;

// width / height
float ratio = 0.0f;

GLuint simple_program = 0;

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
    ratio = width / (float) height;
    glViewport(0, 0, width, height);
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
  glLoadIdentity();
  glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glRotatef((float) glfwGetTime() * 50.f, 0.f, 0.f, 1.f);
  
  glBegin(GL_TRIANGLES);

  for(unsigned i = 0; i < 3; ++i) {
    glVertex3fv(glm::value_ptr(vertices[i]));
    glColor3fv(glm::value_ptr(colors[i]));
  }
  
  glEnd();
}

int main(void) {

  GLFWwindow* window;
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
  glfwSwapInterval(1);
  glfwSetKeyCallback(window, key_callback);
  glfwSetFramebufferSizeCallback(window, framebuffer_resize_callback);

  glbinding::Binding::initialize();

  int width, height;
  glfwGetFramebufferSize(window, &width, &height);
  framebuffer_resize_callback(window, width, height);

  reload_shader_programs();

  while(!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    render(window);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwDestroyWindow(window);
  glfwTerminate();
  exit(EXIT_SUCCESS);
}