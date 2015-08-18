#ifndef UTILS_HPP
#define UTISL_HPP

#include <glbinding/gl/gl.h>
// use gl definitions from glbinding 
using namespace gl;

namespace utils {
  // output current error
  bool query_gl_error();
  // check after every function if error was caused
  void watch_gl_errors(bool activate = true);
  
  void validate_program(GLuint program);

  GLint get_bound_VAO();
  // GLSLS error callback
  void glsl_error(int error, const char* description);

  // extract filename from path
  std::string file_name(std::string const& file_path);
  // output a gl error log in cerr
  void output_log(GLchar const* log_buffer, std::string const& prefix);
  // print bound textures for all texture units
  void print_bound_textures();
}

#endif