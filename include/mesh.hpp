#ifndef MESH_HPP
#define MESH_HPP

#include <glbinding/gl/gl.h>

#include <cstdint>
#include <map>
#include <vector>
// use gl definitions from glbinding 
using namespace gl;

//flag type to combine attributes
typedef int attrib_flag_t;

struct attribute_t {

  attribute_t(attrib_flag_t f, GLsizei s, GLsizei c, GLenum t)
   :flag{f}
   ,size{s}
   ,components{c}
   ,type{t}
  {}

  attribute_t(attribute_t const& a)
   :flag{a.flag}
   ,size{a.size}
   ,components{a.components}
   ,type{a.type}
   ,offset{a.offset}
  {}

  // conversion to flag type for use as enum
  operator attrib_flag_t const&() const{
    return flag;
  }

  // ugly enum to use for flag, must be unique power of two
  attrib_flag_t flag;
  // size in bytes
  GLsizei size;
  // number of scalar components
  GLint components;
  // Gl type
  GLenum type;
  // offset from element beginning
  GLvoid* offset;
};

namespace Attribute{
// holds all possible mesh attributes, for iteration
extern const std::vector<attribute_t> slots;
// symbolic values to access valuesin vector by name
extern attribute_t const& POSITION;
extern attribute_t const& NORMAL;
extern attribute_t const& TEXCOORD;
extern attribute_t const& TANGENT;
extern attribute_t const& BITANGENT;
extern attribute_t const& TRIANGLE;
}

// holds vertex information and triangle indices
struct mesh {
  mesh(std::vector<float> const& databuff, attrib_flag_t attribs, std::vector<unsigned> const& trianglebuff = std::vector<unsigned>{});
  mesh(){};

  std::vector<float> data;
  std::vector<unsigned> triangles;
  // byte offsets of individual element attributes
  std::map<attrib_flag_t, GLvoid*> offsets;
  // size of one vertex element in bytes
  GLsizei stride;
};

#endif