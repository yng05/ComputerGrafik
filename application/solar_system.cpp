
///////////////////////////////// includes ///////////////////////////////////

#include <memory>

#include "program.hpp"
#include "camera.hpp"
#include "scene_node.hpp"
#include "renderer.hpp"
#include "program.hpp"
#include "point_cloud.hpp"






#include <glbinding/gl/gl.h>
// load glbinding extensions
#include <glbinding/Binding.h>

//dont load gl bindings from glfw
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

/* include abstractions for the solar system */
#include "planet.hpp"
#include "sun.hpp"

// use floats and med precision operations
#define GLM_PRECISION_MEDIUMP_FLOAT
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/polar_coordinates.hpp>

#include "shader_loader.hpp"
#include "model_loader.hpp"
#include "texture_loader.hpp"
#include "utils.hpp"

#include <cstdlib>
#include <iostream>

// use gl definitions from glbinding
using namespace gl;

//////      CUSTOM

Renderer renderer;

Camera cam;

std::shared_ptr<Program> point_cloud_prg;

std::shared_ptr<SceneNode> point_cloud;







/////////////////////////// variable definitions //////////////////////////////
// vertical field of view of camera
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
model planet_model{};

// solar system
std::vector<std::shared_ptr<Orb>> orbs;

// holds gpu representation of model
struct model_object {
  GLuint vertex_AO = 0;
  GLuint vertex_BO = 0;
  GLuint element_BO = 0;
};
model_object planet_object;

// holds current camera position in spherical coordinates
glm::vec3 camera_position (
  10,  // radius
  0,  // latitude
  0   // longitude
);

// camera matrices
glm::mat4 camera_view = glm::translate(glm::mat4{}, glm::vec3{0.0f, 0.0f, 2.0f});
glm::mat4 camera_projection{1.0f};

// uniform locations
GLint location_normal_matrix = -1;
GLint location_model_matrix = -1;
GLint location_view_matrix = -1;
GLint location_projection_matrix = -1;

// path to the resource folders
std::string resource_path{};

/////////////////////////// forward declarations //////////////////////////////
void quit(int status);
void update_view(GLFWwindow* window, int width, int height);
void update_camera();
void update_uniform_locations();
void update_shader_programs();
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void initialize_solar_system();
void initialize_geometry();
void show_fps();
void render();

const double PI_2 = 3.14 / 2.0;

// helper
glm::vec3 from_spherical(glm::vec3 const& c)
{
  glm::mat4 t;

  float phi   = c.y;
  float theta = c.z;

  t = glm::rotate(t, phi, glm::vec3(0.0, 1.0, 0.0));
  t = glm::rotate(t, theta, glm::vec3(1.0, 0.0, 0.0));

  return glm::vec3(t * glm::vec4(glm::vec3(0, 0, c.x), 1.0));
}

/////////////////////////////// main function /////////////////////////////////
int main(int argc, char* argv[]) {
  glfwSetErrorCallback(utils::glsl_error);

  if(!glfwInit()) {
    std::exit(EXIT_FAILURE);
  }

//on MacOS, set OGL version explicitly
#ifdef __APPLE__
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, true);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

  // create window, if unsuccessfull, quit
  window = glfwCreateWindow(window_width, window_height, "OpenGL Framework", NULL, NULL);
  if(!window) {
    glfwTerminate();
    std::exit(EXIT_FAILURE);
  }

  // use the windows context
  glfwMakeContextCurrent(window);
  // disable vsync
  glfwSwapInterval(0);
  // register key input function
  glfwSetKeyCallback(window, key_callback);
  // allow free mouse movement
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  // register resizing function
  glfwSetFramebufferSizeCallback(window, update_view);

  // initialize glindings in this context
  glbinding::Binding::initialize();

  // activate error checking after each gl function call
  utils::watch_gl_errors();

  //first argument is resource path
  if (argc > 1) {
    resource_path = argv[1];
  }
  // no resource path specified, use default
  else {
    std::string exe_path{argv[0]};
    resource_path = exe_path.substr(0, exe_path.find_last_of("/\\"));
    resource_path += "/../../resources/";
  }



  // do before framebuffer_resize call as it requires the projection uniform location
  update_shader_programs();

  // initialize projection and view matrices
  int width, height;
  glfwGetFramebufferSize(window, &width, &height);
  update_view(window, width, height);
  update_camera();

  // set up solar system
  initialize_solar_system();

  // set up models
  initialize_geometry();

  point_cloud_prg = std::make_shared<Program>();
  point_cloud_prg->load_from_file(resource_path + "shaders/pointcloud.vert", resource_path + "shaders/pointcloud.frag");

  point_cloud = std::make_shared<PointCloud>(100000);
  point_cloud->program(point_cloud_prg);
  point_cloud->transform(glm::scale(point_cloud->transform(), glm::vec3(100)));

  renderer.camera(cam);

  renderer.register_for_rendering(point_cloud);

  // enable depth testing
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  // rendering loop
  while(!glfwWindowShouldClose(window)) {
    // query input
    glfwPollEvents();
    // clear buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    double mouse_x, mouse_y;
    glfwGetCursorPos(window, &mouse_x, &mouse_y);

    camera_position.y = (mouse_x / width) * PI_2;
    camera_position.z = (mouse_y / height) * PI_2;
    update_camera ();

    // draw geometry
    render();
    // swap draw buffer to front
    glfwSwapBuffers(window);
    // display fps
    show_fps();
  }

  quit(EXIT_SUCCESS);
}

///////////////////////// initialisation functions ////////////////////////////

// initialize solar system
void initialize_solar_system () {
  std::shared_ptr<Orb> sun = std::make_shared<Sun>("sun", 1.0f);
  orbs.push_back(sun);

  orbs.push_back(std::make_shared<Planet>("merkur",  sun, 0.03f, 2.0f));
  orbs.push_back(std::make_shared<Planet>("venus",   sun, 0.05f, 3.0f));

  std::shared_ptr<Orb> earth = std::make_shared<Planet>("earth", sun, 0.1f,  4.0f);
  orbs.push_back(earth);

  std::shared_ptr<Orb> moon = std::make_shared<Planet>("moon", earth, 0.03f,  0.5f);
  orbs.push_back(moon);

  orbs.push_back(std::make_shared<Planet>("mars",    sun, 0.08f, 5.0f));
  orbs.push_back(std::make_shared<Planet>("jupiter", sun, 0.4f,  6.0f));
  orbs.push_back(std::make_shared<Planet>("saturn",  sun, 0.25f, 7.0f));
  orbs.push_back(std::make_shared<Planet>("uranus",  sun, 0.2f,  8.0f));
  orbs.push_back(std::make_shared<Planet>("neptun",  sun, 0.01f, 9.0f));
}

// load models
void initialize_geometry() {
  planet_model = model_loader::obj(resource_path + "models/sphere.obj", model::NORMAL);

  // generate vertex array object
  glGenVertexArrays(1, &planet_object.vertex_AO);
  // bind the array for attaching buffers
  glBindVertexArray(planet_object.vertex_AO);

  // generate generic buffer
  glGenBuffers(1, &planet_object.vertex_BO);
  // bind this as an vertex array buffer containing all attributes
  glBindBuffer(GL_ARRAY_BUFFER, planet_object.vertex_BO);
  // configure currently bound array buffer
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * planet_model.data.size(), planet_model.data.data(), GL_STATIC_DRAW);

  // activate first attribute on gpu
  glEnableVertexAttribArray(0);
  // first attribute is 3 floats with no offset & stride
  glVertexAttribPointer(0, model::POSITION.components, model::POSITION.type, GL_FALSE, planet_model.vertex_bytes, planet_model.offsets[model::POSITION]);
  // activate second attribute on gpu
  glEnableVertexAttribArray(1);
  // second attribute is 3 floats with no offset & stride
  glVertexAttribPointer(1, model::NORMAL.components, model::NORMAL.type, GL_FALSE, planet_model.vertex_bytes, planet_model.offsets[model::NORMAL]);

   // generate generic buffer
  glGenBuffers(1, &planet_object.element_BO);
  // bind this as an vertex array buffer containing all attributes
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, planet_object.element_BO);
  // configure currently bound array buffer
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, model::INDEX.size * planet_model.indices.size(), planet_model.indices.data(), GL_STATIC_DRAW);
}

///////////////////////////// render functions ////////////////////////////////
// render model
void render() {
  glm::mat4 model_matrix; //= glm::rotate(glm::mat4{}, float(glfwGetTime()), glm::vec3{0.0f, 1.0f, 0.0f});
  //model_matrix = glm::translate(model_matrix, glm::vec3{0.0f, 0.0f, -10.0f});


  renderer.render_all();


  glUseProgram(simple_program);
    // after shader is recompiled uniform locations may change
    update_uniform_locations();


  for (auto orb: orbs) {

    // model_matrix = glm::translate(model_matrix, glm::vec3{0.0f, 0.0f, -10.0f});
     glm::mat4 obj_model_matrix = orb->transformation();


    orb->move(0.0001f);

    glUniformMatrix4fv(location_model_matrix, 1, GL_FALSE, glm::value_ptr(obj_model_matrix));

    // extra matrix for normal transformation to keep them orthogonal to surface
    glm::mat4 normal_matrix = glm::inverseTranspose(camera_view * glm::inverse(obj_model_matrix));

    glUniformMatrix4fv(location_normal_matrix, 1, GL_FALSE, glm::value_ptr(normal_matrix));


    glBindVertexArray(planet_object.vertex_AO);
    utils::validate_program(simple_program);
    // draw bound vertex array as triangles using bound shader
    glDrawElements(GL_TRIANGLES, GLsizei(planet_model.indices.size()), model::INDEX.type, NULL);
  }


}

// void
// render_stars ()
// {
//     glUseProgram (starfield_program);
//     update_uniform_locations ();
//     set_uniforms ();
// }

///////////////////////////// update functions ////////////////////////////////
// update viewport and field of view
void update_view(GLFWwindow* window, int width, int height) {
  // resize framebuffer
  glViewport(0, 0, width, height);

  float aspect = float(width) / float(height);
  float fov_y = camera_fov;
  // if width is smaller, extend vertical fov
  if(width < height) {
    fov_y = 2.0f * glm::atan(glm::tan(camera_fov * 0.5f) * (1.0f / aspect));
  }
  // projection is hor+
  camera_projection = glm::perspective(fov_y, aspect, 0.1f, 1000.0f);

  cam.update_projection(fov_y, aspect, 0.1f, 1000.0f);

  // upload matrix to gpu
  glUniformMatrix4fv(location_projection_matrix, 1, GL_FALSE, glm::value_ptr(camera_projection));
}

// update camera transformation
void update_camera() {
  glm::vec3 eye = from_spherical(camera_position);
  glm::vec3 center = glm::vec3(0.0f, 0.0f, 0.0f);
  glm::vec3 up(0.0f, 1.0f, 0.0f);




  camera_view = glm::inverse(glm::lookAt(eye, center, up));

  cam.view_transform(glm::lookAt(eye, center, up));

  renderer.camera(cam);

  // vertices are transformed in camera space, so camera transform must be inverted
  glm::mat4 inv_camera_view = glm::inverse(camera_view);
  // upload matrix to gpu
  glUniformMatrix4fv(location_view_matrix, 1, GL_FALSE, glm::value_ptr(inv_camera_view));
}

// load shaders and update uniform locations
void update_shader_programs() {
  try {
    // throws exception when compiling was unsuccessfull
    GLuint new_program = shader_loader::program(resource_path + "shaders/simple.vert",
                                                resource_path + "shaders/simple.frag");
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
  catch(std::exception&) {
    // dont crash, allow another try
  }
}

// update shader uniform locations
void update_uniform_locations() {
  location_normal_matrix = glGetUniformLocation(simple_program, "NormalMatrix");
  location_model_matrix = glGetUniformLocation(simple_program, "ModelMatrix");
  location_view_matrix = glGetUniformLocation(simple_program, "ViewMatrix");
  location_projection_matrix = glGetUniformLocation(simple_program, "ProjectionMatrix");
}

///////////////////////////// misc functions ////////////////////////////////
// handle key input
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, 1);
  }
  else if(key == GLFW_KEY_R && action == GLFW_PRESS) {
    update_shader_programs();
  }
  else if(key == GLFW_KEY_W && action == GLFW_PRESS) {
    camera_position.x -= 1;
    update_camera();
  }
  else if(key == GLFW_KEY_S && action == GLFW_PRESS) {
    camera_position.x += 1;
    update_camera();
  }
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

void quit(int status) {
  // free opengl resources
  glDeleteProgram(simple_program);
  glDeleteBuffers(1, &planet_object.vertex_BO);
  glDeleteVertexArrays(1, &planet_object.element_BO);
  glDeleteVertexArrays(1, &planet_object.vertex_AO);

  // free glfw resources
  glfwDestroyWindow(window);
  glfwTerminate();

  std::exit(status);
}
