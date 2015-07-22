
#include <glbinding/gl/gl.h>
// load glbinding extensions
#include <glbinding/Binding.h>
// load meta info extension
#include <glbinding/Meta.h>

//dont load gl bindings from glfw
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "glm/gtc/type_ptr.hpp"

#include <stdlib.h>
#include <iostream>

#include <shader_loader.hpp>

// use glbinding functions
using namespace gl;
using glbinding::Meta;

// the rendering window
GLFWwindow* window;
// the main shader program
GLuint simple_program = 0;
// variables for fps computation
double last_second_time = 0;
unsigned frames_per_second = 0;
// camera matrices
GLuint model_vertex_AO = 0;
GLuint model_vertex_BO = 0;
// uniform locations
GLint location_model_matrix = -1;
GLint location_view_matrix = -1;
GLint location_projection_matrix = -1;


// output current error
void query_gl_error() {
  auto error = glGetError();

  if(error != GL_NONE) {
    std::cerr << "OpenGL Error: " << Meta::getString(error) << std::endl;
  }
}

GLint get_current_VAO() {
  GLint array = -1;
  glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &array);

  return array;
}

void update_uniform_locations() {
  location_model_matrix = glGetUniformLocation(simple_program, "ModelMatrix");
  location_view_matrix = glGetUniformLocation(simple_program, "ViewMatrix");
  location_projection_matrix = glGetUniformLocation(simple_program, "ProjectionMatrix");
}

// load shaders and update uniform locations
void update_shader_programs() {
  try {
    GLuint new_program = shader_loader::program("../resources/shaders/simple.vert", "../resources/shaders/simple.frag");
    simple_program = new_program;
  }
  catch(std::exception& e) {
    // dont crash, allow another try
  }

  // after shader is recompiled uniform locations may change
  update_uniform_locations();

  // bind shader
  glUseProgram(simple_program);
}

// GLSLS error callback
void error_callback(int error, const char* description) {
  std::cerr << "GLSL Error: "<< description << std::endl;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, 1);
  }
  else if(key == GLFW_KEY_R && action == GLFW_PRESS) {
    update_shader_programs();
  }
}

// update viewport and field of view
void update_view(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
  // use smaller dimension as reference
  float smaller = width < height ? width : height;
  glm::mat4 camera_projection = glm::ortho(-width / smaller, width / smaller, -height / smaller, height / smaller, 1.0f, -1.0f);
  // upload matrix to gpu
  glUniformMatrix4fv(location_projection_matrix, 1, GL_FALSE, glm::value_ptr(camera_projection));
}

// update camera transformation
void update_camera() {
  glm::mat4 camera_view{};
  // upload matrix to gpu
  glUniformMatrix4fv(location_view_matrix, 1, GL_FALSE, glm::value_ptr(camera_view));
}

// load geometry
void load_model() {
  float vertices[] =
  {
    -0.6f, -0.4f, 0.f,
    0.6f, -0.4f, 0.f,
    0.f, 0.6f, 0.0f
  };  

  // glm::vec3 colors[] =
  // {
  //   {1.f, 0.f, 0.f},
  //   {0.f, 1.f, 0.f},
  //   {0.f, 0.f, 1.f}
  // };  
  // generate vertex array object
  glGenVertexArrays(1, &model_vertex_AO);
  // bind the array for attaching buffers
  glBindVertexArray(model_vertex_AO);

  // generate generic buffer
  glGenBuffers(1, &model_vertex_BO);
  // bind this as an vertex array buffer containing all attributes
  glBindBuffer(GL_ARRAY_BUFFER, model_vertex_BO);
  // configure currently bound array buffer
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * 3, &vertices[0], GL_STATIC_DRAW);

  // activate first attribute on gpu
  glEnableVertexAttribArray(0);
  // first attribute is 3 floats with no offset & stride
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
}

// calculate fps and show in window title
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

// render geometry
void render(GLFWwindow* window) {

  glm::mat4 model_matrix = glm::rotate(glm::mat4{}, float(glfwGetTime()), glm::vec3{0.0f, 0.0f, 1.0f});
  glUniformMatrix4fv(location_model_matrix, 1, GL_FALSE, glm::value_ptr(model_matrix));

  // draw bound vertex array as triangles using bound shader
  glDrawArrays(GL_TRIANGLES, 0, 3);
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
  glfwSetFramebufferSizeCallback(window, update_view);

  // initialize glindings in this context
  glbinding::Binding::initialize();

  // do before framebuffer_resize call as it requires the projection uniform location
  update_shader_programs();

  // initialize projection
  int width, height;
  glfwGetFramebufferSize(window, &width, &height);
  update_view(window, width, height);

  update_camera();

  load_model();

  query_gl_error();

  // rendering loop
  while(!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    render(window);

    glfwSwapBuffers(window);
    glfwPollEvents();

    show_fps();
  }

  // free glfw resources
  glfwDestroyWindow(window);
  glfwTerminate();
  exit(EXIT_SUCCESS);
}