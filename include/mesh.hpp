#ifndef MESH_HPP
#define MESH_HPP

#include <glbinding/gl/gl.h>

#include <cstdint>
#include <map>
#include <vector>
// use gl definitions from glbinding 
using namespace gl;

enum Attribute {
  POSITION = 1 << 0,
  NORMAL   = 1 << 1,
  TEXCOORD = 1 << 2,
  TANGENT  = 1 << 3,
  BITANGENT= 1 << 4,
  TRIANGLE = 1 << 5
};

typedef int Attributes;

struct attribute {

  attribute(GLsizei s, GLsizei c, GLenum t)
   :size{s}
   ,components{c}
   ,type{t}
  {}

  attribute(attribute const& a)
   :size{a.size}
   ,components{a.components}
   ,type{a.type}
   ,offset{a.offset}
  {}

  GLsizei size;
  GLint components;
  GLenum type;
  GLvoid* offset;
};

struct mesh {
  mesh(std::vector<float> const& databuff,  Attributes attribs, std::vector<unsigned> const& trianglebuff = std::vector<unsigned>{});
  mesh(){};
  attribute const& operator[](Attribute const&) const;

  std::vector<float> data;
  std::vector<unsigned> triangles;
  std::map<Attribute, attribute> attributes;
  GLsizei stride;

  static std::map<Attribute, attribute> supported_attributes;
};

#endif