#include "mesh.hpp"

namespace Attribute {

const std::vector<attribute_t> slots
 = {  
    /*POSITION*/{ 1 << 0, sizeof(float), 3, GL_FLOAT},
    /*NORMAL*/{   1 << 1, sizeof(float), 3, GL_FLOAT},
    /*TEXCOORD*/{ 1 << 2, sizeof(float), 2, GL_FLOAT},
    /*TANGENT*/{  1 << 3, sizeof(float), 3, GL_FLOAT},
    /*BITANGENT*/{1 << 4, sizeof(float), 3, GL_FLOAT}
 };

attribute_t const& POSITION = slots[0];
attribute_t const& NORMAL = slots[1];
attribute_t const& TEXCOORD = slots[2];
attribute_t const& TANGENT = slots[3];
attribute_t const& BITANGENT = slots[4];
attribute_t const& TRIANGLE{ 1 << 5, sizeof(unsigned),  1, GL_UNSIGNED_INT};
};

mesh::mesh()
 :data{}
 ,triangles{}
 ,offsets{}
 ,stride{0}
{}

mesh::mesh(std::vector<float> const& databuff, attrib_flag_t contained_attributes, std::vector<unsigned> const& trianglebuff)
 :data{databuff}
 ,triangles{trianglebuff}
 ,offsets{}
 ,stride{0}
{
  for (auto const& supported_attribute : Attribute::slots) {
    // check if buffer contains attribute
    if (supported_attribute.flag & contained_attributes) {
      // write offset, explicit cast to prevent narrowing warning
      offsets.insert(std::pair<attrib_flag_t, GLvoid*>{supported_attribute, (GLvoid*)uintptr_t(stride)});
      // move offset pointer forward
      stride += supported_attribute.size * supported_attribute.components;
    }
  }
}