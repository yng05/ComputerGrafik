#ifndef SHADER_HPP
#define SHADER_HPP

#include <glbinding/gl/gl.h>
#include <glbinding/Binding.h>

using namespace gl;

namespace shader_loader {
  GLuint shader(std::string const& file_name, GLenum shaderType)/*Takes a filename and a Shadertype and returns an id of the compiled shader; shaderType could be: GL_VERTEX_SHADER, GL_FRAGMENT_SHADER, GL_GEOMETRIE_SHADER*/;
  
  GLuint program(std::string const& vertex_name, std::string const& fragment_name);
};

#endif
