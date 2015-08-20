#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <glbinding/gl/gl.h>
#include <vector>

using namespace gl;

// holds texture data and format information
struct texture {
  texture()
   :data()
   ,width{0}
   ,height{0}
   ,depth{0}
   ,target{GL_NONE}
   ,format{GL_NONE}
   ,type{GL_NONE}
  {}

  texture(std::vector<uint8_t> dat, GLenum t, GLenum f, GLenum ty, GLsizei w, GLsizei h = 0, GLsizei d = 0)
   :data(dat)
   ,width{w}
   ,height{h}
   ,depth{d}
   ,target{GL_TEXTURE_2D}
   ,format{f}
   ,type{ty}
  {
    // fit target to input dimensions
    if (height < 2) {
      target = GL_TEXTURE_1D;
    }
    else if (depth > 1) {
      target = GL_TEXTURE_3D;
    }
  }

  std::vector<uint8_t> data;
  GLsizei width;
  GLsizei height;
  GLsizei depth;
  // texture purpose
  GLenum target;
  // channel format
  GLenum format; 
  // pixel format
  GLenum type; 
};

#endif