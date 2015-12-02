
///////////////////////////////// includes ///////////////////////////////////

#include <memory>
#include <random>


#include <glbinding/gl/gl.h>
// load glbinding extensions
#include <glbinding/Binding.h>

//dont load gl bindings from glfw
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

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
GLuint starfield_program = 0;
GLuint orbit_line_program = 0;

// random number generator
std::default_random_engine prng;

// cpu representation of model
model planet_model{};

// number of stars
const unsigned int num_stars = 100000;

// resolution of the orbit lines
const unsigned int orbit_line_resolution = 1000;

// ambient/specular/diffuse light
bool ambient = true;
bool specular = true;
bool diffuse = true;

// use cell shading
bool cell_shading = false;

// holds gpu representation of model
struct model_object {
  GLuint vertex_AO = 0;
  GLuint vertex_BO = 0;
  GLuint element_BO = 0;
};
model_object planet_object;

// holds gpu representation of planet color textures
struct texture_object {

  texture_object (texture const& t)
   : tex(t)
  {}

  GLenum context = GL_TEXTURE0;
  GLenum target = GL_TEXTURE_2D;
  GLuint obj_ptr = 0;
  texture tex;
};
std::vector<texture_object> planet_textures;

struct point_cloud_object {
  GLuint vertex_AO = 0;
  GLuint vertex_BO = 0;
};
point_cloud_object starfield_object;

struct line_object {
  GLuint vertex_AO = 0;
  GLuint vertex_BO = 0;
  GLuint element_BO = 0;
};
line_object orbit_line_object;

// holds the structure of the solar system
struct orb {
  orb (float r, float sz, float sp, float az, orb* p, glm::vec3 const& cl, bool el, texture const& ct, texture const& nt, bool ncb)
   : radius(r), size(sz), speed(sp), azimuth(az), color(cl), emitsLight(el), parent(p)
   , color_tex_obj(ct), normal_tex_obj(nt), no_cell_border(ncb)
  {}
  float radius = 0;
  float size = 0;
  float speed = 0;
  float azimuth = 0;
  glm::vec3 color;
  bool emitsLight = false;
  orb* parent = NULL;


  texture_object color_tex_obj;
  texture_object normal_tex_obj;

  bool no_cell_border = false;
};
std::vector<orb*> orbs;

// holds current camera position in spherical coordinates
glm::vec3 camera_position(10.0f, 0.0f, 0.0f);

glm::vec3 camera_center (0.0f);
int selected_center_orb = 0;

// camera matrices

glm::mat4 camera_view = glm::translate(glm::mat4{}, glm::vec3{0.0f, 0.0f, 2.0f});

glm::mat4 camera_projection{1.0f};

// uniform locations
struct simple_program_locations_struct
{
  GLint location_normal_matrix = -1;
  GLint location_model_matrix = -1;
  GLint location_view_matrix = -1;
  GLint location_projection_matrix = -1;
  GLint location_color_vector = -1;
  GLint location_light_vector = -1;
  GLint location_emits_light_bool = -1;
  GLint location_shininess_float = -1;
  GLint location_ambient_float = -1;
  GLint location_specular_float = -1;
  GLint location_diffuse_float = -1;
  GLint location_cell_shading_float = -1;
  GLint location_color_tex = -1;
  GLint location_normal_tex = -1;
  GLint location_no_cell_border_bool = -1;
} simple_program_locations;

struct starfield_program_locations_struct
{
  GLint location_model_matrix = -1;
  GLint location_view_matrix = -1;
  GLint location_projection_matrix = -1;
} starfield_program_locations;

struct orbit_line_program_location_struct
{
  GLint location_model_matrix = -1;
  GLint location_view_matrix = -1;
  GLint location_projection_matrix = -1;
} orbit_line_program_locations;

// path to the resource folders
std::string resource_path{};

/////////////////////////// forward declarations //////////////////////////////
void quit(int status);
void update_view(GLFWwindow* window, int width, int height);
void update_camera();
void update_uniform_locations();

void update_shader_programs();
void update_camera_position(GLFWwindow* window, int width, int height);

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void initialize_solar_system();
void initialize_geometry();
void initialize_planet_textures();
void show_fps();
void render();

// helper
glm::vec3 from_spherical(glm::vec3 const& c, glm::vec3 const& origin)
{
  glm::mat4 t;

  float phi   = c.y;
  float theta = c.z;

  t = glm::rotate(t, phi, glm::vec3(0.0, 1.0, 0.0));
  t = glm::rotate(t, theta, glm::vec3(1.0, 0.0, 0.0));

  return origin + glm::vec3(t * glm::vec4(glm::vec3(0, 0, c.x), 1.0));
}

/////////////////////////////// main function /////////////////////////////////
int main(int argc, char* argv[]) {
  glfwSetErrorCallback(utils::glsl_error);

  if(!glfwInit()) {
    std::exit(EXIT_FAILURE);
  }


//on MacOS, set OGL version explicitly
// #ifdef __APPLE__

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, true);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

// #endif


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

///////////////////do not use gl* functions before this line!//////////////////

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
  // throw exception if shader compilation was unsuccessfull
  update_shader_programs();

  // initialize projection and view matrices
  int width, height;
  glfwGetFramebufferSize(window, &width, &height);
  update_view(window, width, height);
  update_camera();

  // set up solar system
  initialize_solar_system();


  // initialize textures
  initialize_planet_textures();

  // set up models
  initialize_geometry();

  // enable depth testing
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  // rendering loop
  while(!glfwWindowShouldClose(window)) {
    // query input
    glfwPollEvents();
    // clear buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    update_camera_position(window, width, height);

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

  texture normal_texture = texture_loader::file(resource_path + "textures/normalmap.png");

  orb* sun =      new orb(0.0f,  1.0f, 0.0f, 0.0f,  NULL, glm::vec3(1.0f, 1.0f, 0.0f), true, texture_loader::file(resource_path + "textures/sunmap.png"), normal_texture, false);
  orb* merkur =   new orb(2.0f,  0.15f, 2.5f, 0.1f,  sun, glm::vec3(0.8f, 0.6f, 0.7f), false, texture_loader::file(resource_path + "textures/mercurymap.png"), normal_texture, false);
  orb* venus =    new orb(4.0f,  0.2f, 2.0f, 0.1f,  sun,  glm::vec3(0.6f, 0.8f, 0.7f), false, texture_loader::file(resource_path + "textures/venusmap.png"), normal_texture, false);
  orb* earth =    new orb(6.0f,  0.3f, 1.0f, 0.3f,  sun,  glm::vec3(0.0f, 0.5f, 1.0f), false, texture_loader::file(resource_path + "textures/earthmap1k.png"), normal_texture, false);
  orb* mars =     new orb(8.0f,  0.25f, 1.0f, 0.3f, sun,  glm::vec3(1.0f, 0.4f, 0.0f), false, texture_loader::file(resource_path + "textures/marsmap1k.png"), normal_texture, false);
  orb* jupiter =  new orb(10.0f, 0.7f, 1.0f, 0.3f,  sun,  glm::vec3(0.8f, 0.5f, 0.6f), false, texture_loader::file(resource_path + "textures/jupitermap.png"), normal_texture, false);
  orb* saturn =   new orb(12.0f, 0.6f, 1.0f, 0.3f,  sun,  glm::vec3(0.6f, 0.5f, 0.6f), false, texture_loader::file(resource_path + "textures/saturnmap.png"), normal_texture, false);
  orb* uranus =   new orb(14.0f, 0.5f, 1.0f, 0.3f,  sun,  glm::vec3(0.4f, 0.5f, 0.6f), false, texture_loader::file(resource_path + "textures/uranusmap.png"), normal_texture, false);
  orb* neptun =   new orb(16.0f, 0.3f, 1.0f, 0.3f,  sun,  glm::vec3(0.4f, 0.6f, 0.6f), false, texture_loader::file(resource_path + "textures/neptunemap.png"), normal_texture, false);
  orb* pluto =    new orb(18.0f, 0.1f, 1.0f, 0.3f,  sun,  glm::vec3(0.5f, 0.5f, 0.8f), false, texture_loader::file(resource_path + "textures/plutomap1k.png"), normal_texture, false);

  orb* moon = new orb(1.0f, 0.1f, 4.0f, 0.0f, earth, glm::vec3(0.5f, 0.5f, 0.5f), false, texture_loader::file(resource_path + "textures/moonmap1k.png"), normal_texture, false);


  orb* universe = new orb(0.0f,  500.0f, 0.0f, 0.0f,  NULL, glm::vec3(1.0f, 1.0f, 0.0f), true, texture_loader::file(resource_path + "textures/galaxy.png"), normal_texture, true);

  orbs.push_back(sun);
  orbs.push_back(merkur);
  orbs.push_back(venus);
  orbs.push_back(earth);
  orbs.push_back(mars);
  orbs.push_back(jupiter);
  orbs.push_back(saturn);
  orbs.push_back(uranus);
  orbs.push_back(neptun);
  orbs.push_back(pluto);

  orbs.push_back(moon);

  orbs.push_back(universe);

  for (auto& orb: orbs) {
    if (orb->radius > 0 && orb->size > 0) {
      orb->speed = 1 / (orb->size * orb->radius);
    }
  }
}


void initialize_planet_textures () {

  for (auto orb: orbs) {

    // initialize color texture
    
    // select the current texture context
    glActiveTexture(GL_TEXTURE0);

    // generate a new texture object
    glGenTextures(1, &orb->color_tex_obj.obj_ptr);

    // bind the texture to the current context and target
    glBindTexture(orb->color_tex_obj.tex.target, orb->color_tex_obj.obj_ptr);

    // set texture sampling parameters
    glTexParameteri(orb->color_tex_obj.tex.target, GL_TEXTURE_MIN_FILTER, GLint(GL_LINEAR));
    glTexParameteri(orb->color_tex_obj.tex.target, GL_TEXTURE_MAG_FILTER, GLint(GL_LINEAR));

    glTexImage2D(orb->color_tex_obj.tex.target,
      0, // mipmaps
      GLint(GL_RGBA),
      orb->color_tex_obj.tex.width, orb->color_tex_obj.tex.height,
      0, // no border
      GL_RGBA,
      orb->color_tex_obj.tex.channel_type,
      orb->color_tex_obj.tex.data.data()
    );

    // initialize normal texture
    
    // select the current texture context
    glActiveTexture(GL_TEXTURE1);

    // generate a new texture object
    glGenTextures(1, &orb->normal_tex_obj.obj_ptr);

    // bind the texture to the current context and target
    glBindTexture(orb->normal_tex_obj.tex.target, orb->normal_tex_obj.obj_ptr);

    // set texture sampling parameters
    glTexParameteri(orb->normal_tex_obj.tex.target, GL_TEXTURE_MIN_FILTER, GLint(GL_LINEAR));
    glTexParameteri(orb->normal_tex_obj.tex.target, GL_TEXTURE_MAG_FILTER, GLint(GL_LINEAR));

    glTexImage2D(orb->normal_tex_obj.tex.target,
      0, // mipmaps
      GLint(GL_RGBA),
      orb->normal_tex_obj.tex.width, orb->normal_tex_obj.tex.height,
      0, // no border
      GL_RGBA,
      orb->normal_tex_obj.tex.channel_type,
      orb->normal_tex_obj.tex.data.data()
    );

  }


} 

void initialize_planet_geometry() {
  planet_model = model_loader::obj(resource_path + "models/sphere.obj", model::NORMAL | model::TEXCOORD | model::TANGENT | model::BITANGENT);


  // generate vertex array object
  glGenVertexArrays(1, &planet_object.vertex_AO);
  // bind the array for attaching buffers
  glBindVertexArray(planet_object.vertex_AO);

  // generate generic buffer
  glGenBuffers(1, &planet_object.vertex_BO);
  // bind this as an vertex array buffer containing all attributes
  glBindBuffer(GL_ARRAY_BUFFER, planet_object.vertex_BO);
  // configure currently bound array buffer
  glBufferData(GL_ARRAY_BUFFER, GLsizeiptr(sizeof(float) * planet_model.data.size()), planet_model.data.data(), GL_STATIC_DRAW);

  // activate first attribute on gpu
  glEnableVertexAttribArray(0);
  // first attribute is 3 floats with no offset & stride
  glVertexAttribPointer(0, model::POSITION.components, model::POSITION.type, GL_FALSE, planet_model.vertex_bytes, planet_model.offsets[model::POSITION]);
  // activate second attribute on gpu
  glEnableVertexAttribArray(1);
  // second attribute is 3 floats with no offset & stride
  glVertexAttribPointer(1, model::NORMAL.components, model::NORMAL.type, GL_FALSE, planet_model.vertex_bytes, planet_model.offsets[model::NORMAL]);
  // activate third attribute on gpu
  glEnableVertexAttribArray(2);
  // second attribute is 2 floats with no offset & stride
  glVertexAttribPointer(2, model::TEXCOORD.components, model::TEXCOORD.type, GL_FALSE, planet_model.vertex_bytes, planet_model.offsets[model::TEXCOORD]);

  // activate fourth attribute on gpu
  glEnableVertexAttribArray(3);
  // second attribute is 3 floats with no offset & stride
  glVertexAttribPointer(3, model::TANGENT.components, model::TANGENT.type, GL_FALSE, planet_model.vertex_bytes, planet_model.offsets[model::TANGENT]);

  // activate fifth attribute on gpu
  glEnableVertexAttribArray(4);
  // second attribute is 3 floats with no offset & stride
  glVertexAttribPointer(4, model::BITANGENT.components, model::BITANGENT.type, GL_FALSE, planet_model.vertex_bytes, planet_model.offsets[model::BITANGENT]);



   // generate generic buffer
  glGenBuffers(1, &planet_object.element_BO);
  // bind this as an vertex array buffer containing all attributes
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, planet_object.element_BO);
  // configure currently bound array buffer
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, GLsizeiptr(model::INDEX.size * GLsizei(planet_model.indices.size())), planet_model.indices.data(), GL_STATIC_DRAW);

}

std::vector<float> generate_random_starfield (int num_stars)
{
  std::normal_distribution<float> dist;
  std::vector<float> data;
  for (int i=0; i<num_stars; ++i)
  {
    float x = dist(prng);
    float y = dist(prng);
    float z = dist(prng);
    glm::vec3 p(x, y, z);
    p = 0.9f * p + 0.1f * glm::normalize(p);

    data.push_back(p.x);
    data.push_back(p.y);
    data.push_back(p.z);
  }
  return data;
}

void initialize_starfield_geometry ()
{
  auto data = generate_random_starfield(num_stars);

  // generate vertex array object
  glGenVertexArrays(1, &starfield_object.vertex_AO);
  // bind the array for attaching buffers
  glBindVertexArray(starfield_object.vertex_AO);

  // generate generic buffer
  glGenBuffers(1, &starfield_object.vertex_BO);
  // bind this as an vertex array buffer containing all attributes
  glBindBuffer(GL_ARRAY_BUFFER, starfield_object.vertex_BO);
  // configure currently bound array buffer
  glBufferData(GL_ARRAY_BUFFER, GLsizeiptr(GLsizei(sizeof(float) * data.size())), data.data(), GL_STATIC_DRAW);

  // activate first attribute on gpu
  glEnableVertexAttribArray(0);

  // first attribute is 3 floats with no offset & stride
  glVertexAttribPointer(0, model::POSITION.components, model::POSITION.type, GL_FALSE, planet_model.vertex_bytes, planet_model.offsets[model::POSITION]);
}

std::pair<std::vector<float>, std::vector<int>> generate_orbit_line_data (int orbit_line_resolution)
{
  std::vector<float> data;
  std::vector<int> indices;
  for (int i=0; i< orbit_line_resolution+1; ++i)
  {
    float t = float(i) / float(orbit_line_resolution);
    float x = (float) glm::cos(t * 4.0f * M_PI);
    float y = (float) glm::sin(t * 4.0f * M_PI);
    float z = 0;

    int first = i;
    int second = (i+1) % orbit_line_resolution;

    std::cout << x << " " << y << std::endl;

    data.push_back(x);
    data.push_back(y);
    data.push_back(z);
    data.push_back(t);

    indices.push_back(first);
    indices.push_back(second);
  }

  return std::make_pair(data, indices);
}

void initialize_orbit_line_geometry ()
{
  auto data = generate_orbit_line_data(orbit_line_resolution);

  // generate vertex array object
  glGenVertexArrays(1, &orbit_line_object.vertex_AO);
  // bind the array for attaching buffers
  glBindVertexArray(orbit_line_object.vertex_AO);

  // generate generic buffer
  glGenBuffers(1, &orbit_line_object.vertex_BO);
  // bind this as an vertex array buffer containing all attributes
  glBindBuffer(GL_ARRAY_BUFFER, orbit_line_object.vertex_BO);
  // configure currently bound array buffer
  glBufferData(GL_ARRAY_BUFFER, GLsizeiptr(GLsizei(sizeof(float)) * data.first.size()), data.first.data(), GL_STATIC_DRAW);

  // activate first attribute on gpu
  glEnableVertexAttribArray(0);
  // first attribute is 3 floats with no offset & stride
  uintptr_t offset0 = 0 * sizeof(float);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, /* planet_model.vertex_bytes */ 4 * sizeof(float), /* planet_model.offsets[model::POSITION] */ (const GLvoid*) offset0);

  // activate first attribute on gpu
  glEnableVertexAttribArray(1);
  // first attribute is 3 floats with no offset & stride
  uintptr_t offset1 = 3 * sizeof(float);
  glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, /* planet_model.vertex_bytes */ 4 * sizeof(float), /* planet_model.offsets[model::POSITION] */ (const GLvoid*) offset1);


   // generate generic buffer
  glGenBuffers(1, &orbit_line_object.element_BO);
  // bind this as an vertex array buffer containing all attributes
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, orbit_line_object.element_BO);
  // configure currently bound array buffer
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, GLsizeiptr(2 * GLsizei(data.second.size())), data.second.data(), GL_STATIC_DRAW);

}


// load models
void initialize_geometry() {
  initialize_planet_geometry();
  initialize_starfield_geometry();
  initialize_orbit_line_geometry();
}

///////////////////////////// render functions ////////////////////////////////

void render_planets (float t)
{
  glUseProgram(simple_program);

  // the sun is in the origin
  glUniform3f(simple_program_locations.location_light_vector, 0.0f, 0.0f, 0.0f);

  // shininess is the same for all planets
  glUniform1f(simple_program_locations.location_shininess_float, 10.0f);

  // initial light
  glUniform1f(simple_program_locations.location_cell_shading_float, cell_shading);
  glUniform1f(simple_program_locations.location_diffuse_float, diffuse);
  glUniform1f(simple_program_locations.location_ambient_float, ambient);
  glUniform1f(simple_program_locations.location_specular_float, specular);

  for (unsigned long i=0; i<orbs.size(); ++i)
  {

    auto orb = orbs[i];

    glm::mat4 transform;
    glm::mat4 normal_transform;
    glm::vec3 position;

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(orb->color_tex_obj.tex.target, orb->color_tex_obj.obj_ptr);
    glUniform1i(simple_program_locations.location_color_tex, 0);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(orb->normal_tex_obj.tex.target, orb->normal_tex_obj.obj_ptr);
    glUniform1i(simple_program_locations.location_normal_tex, 1);

    // scale the planet
    transform = glm::scale(transform, glm::vec3(1.0f/orb->size));

    // init planet with right rotation  
    // transform = glm::rotate(transform, float(-M_PI/6.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    
    // spin of the planet
    transform = glm::rotate(transform, t * orb->speed * 10.0f, glm::vec3(0.0f, 0.0f, 1.0f));


    auto current = orb;
    while (current != NULL)
    {
      // translate the planet to its orbit
      transform = glm::translate(transform, current->radius * glm::vec3(1.0f, 0.0f, 0.0f));

      // rotate the planet around its orbit
      transform = glm::rotate(transform, -t * current->speed, glm::vec3(0.0f, 0.0f, 1.0f));

      // as long as we have a parent, apply its transformation too
      current = current->parent;
    }

    // application order of the model transformation is reversed to its definition
    transform = glm::inverse(transform);

    if (selected_center_orb == i) 
    {
      camera_center = glm::vec3(transform * glm::vec4(glm::vec3(0.0f), 1.0f));
    }

    // sent the model matrix to the shader
    glUniformMatrix4fv(simple_program_locations.location_model_matrix, 1, GL_FALSE, glm::value_ptr(transform));

    // calculate the correct normal transformation
    normal_transform = glm::inverseTranspose(glm::inverse(camera_view) * transform);

    // send the noraml matrix to the shader
    glUniformMatrix4fv(simple_program_locations.location_normal_matrix, 1, GL_FALSE, glm::value_ptr(normal_transform));


    glUniform1i(simple_program_locations.location_no_cell_border_bool, orb->no_cell_border);

    glUniform3f(simple_program_locations.location_color_vector, orb->color.x, orb->color.y, orb->color.z);
    glUniform1i(simple_program_locations.location_emits_light_bool, orb->emitsLight);

    glBindVertexArray(planet_object.vertex_AO);
    utils::validate_program(simple_program);
    glDrawElements(GL_TRIANGLES, GLsizei(planet_model.indices.size()), model::INDEX.type, NULL);
  }
}

void render_stars ()
{
  glUseProgram(starfield_program);

  glm::mat4 transform;
  transform = glm::scale(transform, glm::vec3(100.0f));
  glUniformMatrix4fv(starfield_program_locations.location_model_matrix, 1, GL_FALSE, glm::value_ptr(transform));

  glUseProgram(starfield_program);
  glBindVertexArray(starfield_object.vertex_AO);
  glDrawArrays(GL_POINTS, 0, num_stars);
}

void render_orbit_lines (float t)
{
  glUseProgram(orbit_line_program);

  for (auto orb: orbs)
  {
    glm::mat4 transform;
    glm::mat4 normal_transform;
    glm::vec3 position;

    // rotate the orbit around its center
    transform = glm::rotate(transform, -t * orb->speed, glm::vec3(0.0f, 0.0f, 1.0f));

    // scale the orbit circle to the radius of the orbit of the planet
    transform = glm::scale(transform, glm::vec3(-1 / orb->radius));

    auto current = orb->parent;
    while (current != NULL)
    {
      // translate the orbit to the its orbit center
      transform = glm::translate(transform, current->radius * glm::vec3(1.0f, 0.0f, 0.0f));

      // rotate the orbit around its orbit center
      transform = glm::rotate(transform, -t * current->speed, glm::vec3(0.0f, 0.0f, 1.0f));

      // as long as we have a parent, apply its transformation too
      current = current->parent;
    }

    // application order of the model transformation is reversed to its definition
    transform = glm::inverse(transform);


    glUniformMatrix4fv(orbit_line_program_locations.location_model_matrix, 1, GL_FALSE, glm::value_ptr(transform));

    glBindVertexArray(orbit_line_object.vertex_AO);
    utils::validate_program(orbit_line_program);
    glDrawElements(GL_LINE_LOOP, orbit_line_resolution, model::INDEX.type, NULL);
  }
}

// render model
void render() {

  float factor = 0.1f;
  float t = factor * (float) glfwGetTime();

  render_stars();
  render_planets(t);
  render_orbit_lines(t);


}


///////////////////////////// update functions ////////////////////////////////
// update viewport and field of view
void update_view(GLFWwindow* window, int width, int height) {
  // resize framebuffer
  glViewport(0, 0, width, height);

  float aspect = float(width) / float(height);
  float fov_y = camera_fov;
  // if width is smaller, extend vertical fov
  if(width < height)
  {
    fov_y = 2.0f * glm::atan(glm::tan(camera_fov * 0.5f) * (1.0f / aspect));
  }
  // projection is hor+
  camera_projection = glm::perspective(fov_y, aspect, 0.1f, 1000.0f);

  // upload matrix to gpu
  glUseProgram(simple_program);
  glUniformMatrix4fv(simple_program_locations.location_projection_matrix, 1, GL_FALSE, glm::value_ptr(camera_projection));

  glUseProgram(starfield_program);
  glUniformMatrix4fv(starfield_program_locations.location_projection_matrix, 1, GL_FALSE, glm::value_ptr(camera_projection));

  glUseProgram(orbit_line_program);
  glUniformMatrix4fv(orbit_line_program_locations.location_projection_matrix, 1, GL_FALSE, glm::value_ptr(camera_projection));
}

// update camera transformation

void update_camera() {
  glm::vec3 eye = from_spherical(camera_position, camera_center);
  glm::vec3 center = camera_center; // glm::vec3(0.0f, 0.0f, 0.0f);
  glm::vec3 up(0.0f, 1.0f, 0.0f);

  camera_view = glm::inverse(glm::lookAt(eye, center, up));


  // vertices are transformed in camera space, so camera transform must be inverted
  glm::mat4 inv_camera_view = glm::inverse(camera_view);
  // upload matrix to gpu
  glUseProgram(simple_program);
  glUniformMatrix4fv(simple_program_locations.location_view_matrix, 1, GL_FALSE, glm::value_ptr(inv_camera_view));

  glUseProgram(starfield_program);
  glUniformMatrix4fv(starfield_program_locations.location_view_matrix, 1, GL_FALSE, glm::value_ptr(inv_camera_view));

  glUseProgram(orbit_line_program);
  glUniformMatrix4fv(orbit_line_program_locations.location_view_matrix, 1, GL_FALSE, glm::value_ptr(inv_camera_view));
}

// load shaders and update uniform locations

void update_shader_programs() {

  std::vector<std::pair<std::pair<std::string, std::string>, GLuint*>> shaders {
    { {"shaders/simple.vert",     "shaders/simple.frag"},     &simple_program },
    { {"shaders/pointcloud.vert", "shaders/pointcloud.frag"}, &starfield_program },
    { {"shaders/lines.vert",      "shaders/lines.frag"},      &orbit_line_program }
  };

  try {  
    for (auto p: shaders) {

      auto vertex_path = p.first.first;
      auto frag_path   = p.first.second;
      auto program     = p.second;

      // throws exception when compiling was unsuccessfull
      GLuint new_program = shader_loader::program(resource_path + vertex_path,
                                                  resource_path + frag_path);
      // free old shader
      glDeleteProgram(*program);

      // save new shader
      *program = new_program;

      // bind shader
      glUseProgram(*program);
      // after shader is recompiled uniform locations may change


    }

    update_uniform_locations();

    // upload view uniforms to new shader
      int width, height;
      glfwGetFramebufferSize(window, &width, &height);
      update_view(window, width, height);
      update_camera();

  } catch (std::exception& e) {

  }
}

// update shader uniform locations
void update_uniform_locations() {
  glUseProgram(simple_program);
  simple_program_locations.location_normal_matrix = glGetUniformLocation(simple_program, "NormalMatrix");
  simple_program_locations.location_model_matrix = glGetUniformLocation(simple_program, "ModelMatrix");
  simple_program_locations.location_view_matrix = glGetUniformLocation(simple_program, "ViewMatrix");
  simple_program_locations.location_projection_matrix = glGetUniformLocation(simple_program, "ProjectionMatrix");
  simple_program_locations.location_color_vector = glGetUniformLocation(simple_program, "Color");
  simple_program_locations.location_light_vector = glGetUniformLocation(simple_program, "LightPosition");
  simple_program_locations.location_emits_light_bool = glGetUniformLocation(simple_program, "EmitsLight");
  simple_program_locations.location_no_cell_border_bool = glGetUniformLocation(simple_program, "NoCellBorder");
  simple_program_locations.location_shininess_float = glGetUniformLocation(simple_program, "Shininess");
  simple_program_locations.location_ambient_float = glGetUniformLocation(simple_program, "Ambient");
  simple_program_locations.location_specular_float = glGetUniformLocation(simple_program, "Specular");
  simple_program_locations.location_diffuse_float = glGetUniformLocation(simple_program, "Diffuse");
  simple_program_locations.location_cell_shading_float = glGetUniformLocation(simple_program, "CellShading");
  simple_program_locations.location_color_tex = glGetUniformLocation(simple_program, "ColorTex");
  simple_program_locations.location_normal_tex = glGetUniformLocation(simple_program, "NormalTex");


  glUseProgram(starfield_program);
  starfield_program_locations.location_model_matrix = glGetUniformLocation(starfield_program, "ModelMatrix");
  starfield_program_locations.location_view_matrix = glGetUniformLocation(starfield_program, "ViewMatrix");
  starfield_program_locations.location_projection_matrix = glGetUniformLocation(starfield_program, "ProjectionMatrix");

  glUseProgram(orbit_line_program);
  orbit_line_program_locations.location_model_matrix = glGetUniformLocation(orbit_line_program, "ModelMatrix");
  orbit_line_program_locations.location_view_matrix = glGetUniformLocation(orbit_line_program, "ViewMatrix");
  orbit_line_program_locations.location_projection_matrix = glGetUniformLocation(orbit_line_program, "ProjectionMatrix");
}

void update_camera_position (GLFWwindow* window, int width, int height) {
  double mouse_x, mouse_y;
  glfwGetCursorPos(window, &mouse_x, &mouse_y);

  // set latitude and longitude to thsle mouse x and mouse y offset respectively
  camera_position.y = (float) (mouse_x / width) * float(M_PI) / 2.0f;
  camera_position.z = (float) (mouse_y / height) * float(M_PI) / 2.0f;

  update_camera ();
}

///////////////////////////// misc functions ////////////////////////////////
// handle key input
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  // moving:
  if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
  {
    glfwSetWindowShouldClose(window, 1);
  }
  else if(key == GLFW_KEY_R && action == GLFW_PRESS)
  {
    update_shader_programs();
  }

  else if(key == GLFW_KEY_W && action == GLFW_PRESS)
  {
    camera_position.x -= 1;
    update_camera();
  }
  else if(key == GLFW_KEY_S && action == GLFW_PRESS)
  {
    camera_position.x += 1;
    update_camera();
  }

  else if (key == GLFW_KEY_K && action == GLFW_PRESS)
  {
    selected_center_orb = glm::min(int(selected_center_orb + 1), int(orbs.size()-2));
  }
  else if (key == GLFW_KEY_L && action == GLFW_PRESS)
  {
    selected_center_orb = glm::max(int(selected_center_orb - 1), int(0));
  }

  // light
  glUseProgram(simple_program);
  if (key == GLFW_KEY_1 && action == GLFW_PRESS)
  { // phong shading
    cell_shading = false;
    glUniform1f(simple_program_locations.location_cell_shading_float, cell_shading);
  }
  else if (key == GLFW_KEY_2 && action == GLFW_PRESS)
  { // cell shading
    cell_shading = true;
    glUniform1f(simple_program_locations.location_cell_shading_float, cell_shading);
  }
  else if (key == GLFW_KEY_3 && action == GLFW_PRESS)
  { // diffuse light
    diffuse = !diffuse;
    glUniform1f(simple_program_locations.location_diffuse_float, diffuse);
  }
  else if (key == GLFW_KEY_4 && action == GLFW_PRESS)
  { // ambient light
    ambient = !ambient;
    glUniform1f(simple_program_locations.location_ambient_float, ambient);
  }
  else if (key == GLFW_KEY_5 && action == GLFW_PRESS)
  { // specular light
    specular = !specular;
    glUniform1f(simple_program_locations.location_specular_float, specular);
  }
}

// calculate fps and show in window title
void show_fps() {
  ++frames_per_second;
  double current_time = glfwGetTime();
  if(current_time - last_second_time >= 1.0) {
    std::string title{"OpenGL Framework - "};
    title += std::to_string(frames_per_second) + " fps";

    if (cell_shading)
    {
      title += " - Cell Shading";
    }
    if (ambient)
    {
      title += " - Ambient Light";
    }
    if (specular)
    {
      title += " - Specular Light";
    }
    if (diffuse)
    {
      title += " - Diffuse Light";
    }

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
