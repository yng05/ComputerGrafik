#ifndef SHADER_LOADER_HPP
#define SHADER_LOADER_HPP

#include <glbinding/gl/gl.h>

using namespace gl;

namespace shader_loader {
  GLuint shader(std::string const& file_name, GLenum shader_type);
  
  GLuint program(std::string const& vertex_name, std::string const& fragment_name);
};

#endif
