
#include <glbinding/gl/gl.h>
// load glbinding extensions
#include <glbinding/Binding.h>
// load meta info extension
#include <glbinding/Meta.h>
// load callback support
#include <glbinding/callbacks.h>

//dont load gl bindings from glfw
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

// use floats and med precision operations
#define GLM_PRECISION_MEDIUMP_FLOAT
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/type_ptr.hpp>

// load tinyobjloader
#include <tiny_obj_loader.h>

#include <stdlib.h>
#include <iostream>

#include "shader_loader.hpp"
#include "model_loader.hpp"

// use gl definitions from glbinding 
using namespace gl;
using glbinding::Meta;

// verticel field of view of camera
const float camera_fov = glm::radians(60.0f);
// initial window dimensions
const unsigned window_width = 640;
const unsigned window_height = 480;

// the rendering window
GLFWwindow* window;
// variables for fps computation
double last_second_time = 0;
unsigned frames_per_second = 0;
// the main shader program
GLuint simple_program = 0;
// cpu representation of model
mesh mesh{};
// holds gpu representation of model
struct geometry {
  GLuint vertex_AO = 0;
  GLuint vertex_BO = 0;
  GLuint element_BO = 0;
};
geometry model;
// camera matrices
glm::mat4 camera_view = glm::translate(glm::mat4{}, glm::vec3{0.0f, 0.0f, 2.0f});
glm::mat4 camera_projection{};
// uniform locations
GLint location_normal_matrix = -1;
GLint location_model_matrix = -1;
GLint location_view_matrix = -1;
GLint location_projection_matrix = -1;

void quit(int status) {
  // free opengl resources
  glDeleteProgram(simple_program);
  glDeleteBuffers(1, &model.vertex_BO);
  glDeleteVertexArrays(1, &model.element_BO);
  glDeleteVertexArrays(1, &model.vertex_AO);

  // free glfw resources
  glfwDestroyWindow(window);
  glfwTerminate();

  exit(status);
}

// output current error
bool query_gl_error() {
  bool error_occured = false;

  GLenum error = glGetError();
  while(error != GL_NO_ERROR) {
    std::cerr << "OpenGL Error: " << Meta::getString(error) << std::endl;
    error = glGetError();

    error_occured = true;
  }

  return error_occured;
}

// check after every function if error was caused
void watch_gl_errors(bool activate = true) {
  if(activate) {
    // add callback after each function call
    glbinding::setCallbackMaskExcept(glbinding::CallbackMask::After | glbinding::CallbackMask::ParametersAndReturnValue, { "glGetError" });
    glbinding::setAfterCallback(
      [](glbinding::FunctionCall const& call) {
        GLenum error = glGetError();
        if (error != GL_NO_ERROR) {
          // print name
          std::cerr <<  "OpenGL Error: " << call.function->name() << "(";
          // parameters
          for (unsigned i = 0; i < call.parameters.size(); ++i)
          {
            std::cerr << call.parameters[i]->asString();
            if (i < call.parameters.size() - 1)
              std::cerr << ", ";
          }
          std::cerr << ")";
          // return value
          if(call.returnValue) {
            std::cerr << " -> " << call.returnValue->asString();
          }
          // error
          std::cerr  << " - " << Meta::getString(error) << std::endl;

          quit(EXIT_FAILURE);
        }
      }
    );
  }
  else {
    glbinding::setCallbackMask(glbinding::CallbackMask::None);
  }
}

GLint get_bound_VAO() {
  GLint array = -1;
  glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &array);

  return array;
}

// update viewport and field of view
void update_view(GLFWwindow* window, int width, int height) {
  // resize framebuffer
  glViewport(0, 0, width, height);

  float aspect = float(width) / height;
  float fov_y = camera_fov;
  // if width is smaller, extend vertical fov 
  if(width < height) {
    fov_y = 2.0f * glm::atan(glm::tan(camera_fov * 0.5f) * (1.0f / aspect));
  }
  // projection is hor+ 
  camera_projection = glm::perspective(fov_y, aspect, 0.1f, 10.0f);
  // upload matrix to gpu
  glUniformMatrix4fv(location_projection_matrix, 1, GL_FALSE, glm::value_ptr(camera_projection));
}

// update camera transformation
void update_camera() {
  // vertices are transformed in camera space, so camera transform must be inverted
  glm::mat4 inv_camera_view = glm::inverse(camera_view);
  // upload matrix to gpu
  glUniformMatrix4fv(location_view_matrix, 1, GL_FALSE, glm::value_ptr(inv_camera_view));
}

// update shader uniform locations
void update_uniform_locations() {
  location_normal_matrix = glGetUniformLocation(simple_program, "NormalMatrix");
  location_model_matrix = glGetUniformLocation(simple_program, "ModelMatrix");
  location_view_matrix = glGetUniformLocation(simple_program, "ViewMatrix");
  location_projection_matrix = glGetUniformLocation(simple_program, "ProjectionMatrix");
}

// load shaders and update uniform locations
void update_shader_programs() {
  try {
    // throws exception when compiling was unsuccessfull
    GLuint new_program = shader_loader::program("../resources/shaders/simple.vert", "../resources/shaders/simple.frag");
    // free old shader
    glDeleteProgram(simple_program);
    // save new shader
    simple_program = new_program;
    // bind shader
    glUseProgram(simple_program);
    // after shader is recompiled uniform locations may change
    update_uniform_locations();

    // upload view uniforms to new shader
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    update_view(window, width, height);
    update_camera();
  }
  catch(std::exception& e) {
    // dont crash, allow another try
  }

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
  else if(key == GLFW_KEY_W && action == GLFW_PRESS) {
    camera_view = glm::translate(camera_view, glm::vec3{0.0f, 0.0f, -0.1f});
    std::cout << "w" << std::endl;
    update_camera();
  }
  else if(key == GLFW_KEY_S && action == GLFW_PRESS) {
    camera_view = glm::translate(camera_view, glm::vec3{0.0f, 0.0f, 0.1f});
    std::cout << "s" << std::endl;
    update_camera();
  }
}

// load geometry
void load_model() {
  mesh = model_loader::obj("../resources/models/triangle.obj", mesh::NORMAL);

  // generate vertex array object
  glGenVertexArrays(1, &model.vertex_AO);
  // bind the array for attaching buffers
  glBindVertexArray(model.vertex_AO);

  // generate generic buffer
  glGenBuffers(1, &model.vertex_BO);
  // bind this as an vertex array buffer containing all attributes
  glBindBuffer(GL_ARRAY_BUFFER, model.vertex_BO);
  // configure currently bound array buffer
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * mesh.data.size(), &mesh.data[0], GL_STATIC_DRAW);

  // activate first attribute on gpu
  glEnableVertexAttribArray(0);
  // first attribute is 3 floats with no offset & stride
  glVertexAttribPointer(0, mesh::POSITION.components, mesh::POSITION.type, GL_FALSE, mesh.stride, mesh.offsets[mesh::POSITION]);
  // activate second attribute on gpu
  glEnableVertexAttribArray(1);
  // second attribute is 3 floats with no offset & stride
  glVertexAttribPointer(1, mesh::NORMAL.components, mesh::NORMAL.type, GL_FALSE, mesh.stride, mesh.offsets[mesh::NORMAL]);

   // generate generic buffer
  glGenBuffers(1, &model.element_BO);
  // bind this as an vertex array buffer containing all attributes
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model.element_BO);
  // configure currently bound array buffer
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh::INDEX.size * mesh.indices.size(), &mesh.indices[0], GL_STATIC_DRAW);
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
  glm::mat4 model_matrix = glm::rotate(glm::mat4{}, float(glfwGetTime()), glm::vec3{0.0f, 1.0f, 0.0f});
  glUniformMatrix4fv(location_model_matrix, 1, GL_FALSE, glm::value_ptr(model_matrix));
  // extra matrix for normal transformation to keep them orthogonal to surface
  glm::mat4 normal_matrix = glm::inverseTranspose(camera_view * model_matrix);
  glUniformMatrix4fv(location_normal_matrix, 1, GL_FALSE, glm::value_ptr(normal_matrix));

  glBindVertexArray(model.vertex_AO);
  // draw bound vertex array as triangles using bound shader
  glDrawElements(GL_TRIANGLES, mesh.indices.size(), mesh::INDEX.type, NULL);
}

int main(void) {

  glfwSetErrorCallback(error_callback);

  if(!glfwInit()) {
    exit(EXIT_FAILURE);  
  }

  window = glfwCreateWindow(window_width, window_height, "OpenGL Framework", NULL, NULL);

  if(!window) {
      glfwTerminate();
      exit(EXIT_FAILURE);
  }
  // use the windows context
  glfwMakeContextCurrent(window);
  // disable vsync
  glfwSwapInterval(0);
  glfwSetKeyCallback(window, key_callback);
  glfwSetFramebufferSizeCallback(window, update_view);

  // initialize glindings in this context
  glbinding::Binding::initialize();

  // activate error checking after each gl function call
  watch_gl_errors();

  simple_program = shader_loader::program("../resources/shaders/simple.vert", "../resources/shaders/simple.frag");
  // do before framebuffer_resize call as it requires the projection uniform location
  update_shader_programs();

  // initialize projection
  int width, height;
  glfwGetFramebufferSize(window, &width, &height);
  update_view(window, width, height);

  update_camera();

  load_model();
  // Enables Depth Testing
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  
  // rendering loop
  while(!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    render(window);

    glfwSwapBuffers(window);
    glfwPollEvents();

    show_fps();
  }

  quit(EXIT_SUCCESS);
}