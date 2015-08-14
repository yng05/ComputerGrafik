#ifndef TEXTURE_LOADER_HPP
#define TEXTURE_LOADER_HPP

#include <glbinding/gl/gl.h>

using namespace gl;

namespace texture_loader {
  GLuint texture(std::string const& file_name);
};

#endif