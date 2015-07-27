#include "mesh.hpp"

std::map<Attribute, attribute> mesh::supported_attributes
 = {{Attribute::POSITION, attribute{sizeof(float), 3, GL_FLOAT}},
    {Attribute::NORMAL,   attribute{sizeof(float), 3, GL_FLOAT}},
    {Attribute::TEXCOORD, attribute{sizeof(float), 2, GL_FLOAT}},
    {Attribute::TANGENT,  attribute{sizeof(float), 3, GL_FLOAT}},
    {Attribute::BITANGENT,attribute{sizeof(float), 3, GL_FLOAT}},
    {Attribute::TRIANGLE, attribute{sizeof(unsigned),  1, GL_UNSIGNED_INT}}
 };

mesh::mesh(std::vector<float> const& databuff, Attributes contained_attributes, std::vector<unsigned> const& trianglebuff)
 :data{databuff}
 ,triangles{trianglebuff}
 ,attributes{}
 ,stride{0}
{
  for (auto const& supported_attribute : supported_attributes) {
    // check ig buffer contains attribute
    if (supported_attribute.first & contained_attributes) {
      attribute new_attribute{supported_attribute.second};
      new_attribute.offset = (GLvoid*)uintptr_t(stride);
      // move offset pointer forward
      stride += supported_attribute.second.size * supported_attribute.second.components;

      // put the info in the map
      attributes.insert(std::pair<Attribute, attribute>{supported_attribute.first, new_attribute});
    }
  }
  // check if index buffer is included
  if (trianglebuff.size() > 0) {
    attributes.insert(std::pair<Attribute, attribute>{Attribute::TRIANGLE, supported_attributes.at(Attribute::TRIANGLE)});
  }
}

attribute const& mesh::operator[](Attribute const& attr) const {
  return attributes.at(attr);
}
