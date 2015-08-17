#include "mesh.hpp"

std::vector<mesh::attribute> const mesh::VERTEX_ATTRIBS
 = {  
    /*POSITION*/{ 1 << 0, sizeof(float), 3, GL_FLOAT},
    /*NORMAL*/{   1 << 1, sizeof(float), 3, GL_FLOAT},
    /*TEXCOORD*/{ 1 << 2, sizeof(float), 2, GL_FLOAT},
    /*TANGENT*/{  1 << 3, sizeof(float), 3, GL_FLOAT},
    /*BITANGENT*/{1 << 4, sizeof(float), 3, GL_FLOAT}
 };

mesh::attribute const& mesh::POSITION = mesh::VERTEX_ATTRIBS[0];
mesh::attribute const& mesh::NORMAL = mesh::VERTEX_ATTRIBS[1];
mesh::attribute const& mesh::TEXCOORD = mesh::VERTEX_ATTRIBS[2];
mesh::attribute const& mesh::TANGENT = mesh::VERTEX_ATTRIBS[3];
mesh::attribute const& mesh::BITANGENT = mesh::VERTEX_ATTRIBS[4];
mesh::attribute const  mesh::INDEX{1 << 5, sizeof(unsigned),  1, GL_UNSIGNED_INT};

mesh::mesh()
 :data{}
 ,indices{}
 ,offsets{}
 ,stride{0}
 ,vertex_num{0}
{}

mesh::mesh(std::vector<float> const& databuff, attrib_flag_t contained_attributes, std::vector<unsigned> const& trianglebuff)
 :data(databuff)
 ,indices(trianglebuff)
 ,offsets{}
 ,stride{0}
 ,vertex_num{0}
{
  // number of components per vertex
  std::size_t component_num = 0;

  for (auto const& supported_attribute : mesh::VERTEX_ATTRIBS) {
    // check if buffer contains attribute
    if (supported_attribute.flag & contained_attributes) {
      // write offset, explicit cast to prevent narrowing warning
      offsets.insert(std::pair<attrib_flag_t, GLvoid*>{supported_attribute, (GLvoid*)uintptr_t(stride)});
      // move offset pointer forward
      stride += supported_attribute.size * supported_attribute.components;
      // increase number of components
      component_num += supported_attribute.components;
    }
  }
  // set number of vertice sin buffer
  vertex_num = data.size() / component_num;
}