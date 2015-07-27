#include "model_loader.hpp"
#include <iostream>

namespace model_loader {

mesh obj(std::string const& name, Attributes import_attribs){
  std::vector<tinyobj::shape_t> shapes;
  std::vector<tinyobj::material_t> materials;

  std::string err = tinyobj::LoadObj(shapes, materials, name.c_str());

  if (!err.empty()) {
    std::cerr << "File \'" << name << "\' not found" << std::endl;
    
    throw std::invalid_argument(name);
  }

  Attributes attributes{Attribute::POSITION | import_attribs};

  if(import_attribs & Attribute::TANGENT) {
    std::cerr << "Attribute not supported" << std::endl;
    throw std::invalid_argument(name);
  }

  std::vector<float> vertex_data;
  std::vector<unsigned> triangles;

  unsigned vertex_offset = 0;

  for (auto const& shape : shapes) {
    tinyobj::mesh_t const& curr_mesh = shape.mesh;

    // create tangents and bitangents

    bool has_normals = true;
    if (curr_mesh.normals.size() < 0 || curr_mesh.normals.size() < curr_mesh.positions.size()) {
      has_normals = false;
      if(import_attribs & Attribute::NORMAL) {
        // generate normals?
        attributes &= Attribute::NORMAL;
        std::cerr << "Shape has no normals" << std::endl;
      }
    }

    bool has_uvs = true;
    if (curr_mesh.texcoords.size() < 0 || curr_mesh.texcoords.size() < curr_mesh.positions.size()) {
      has_uvs = false;
      if(import_attribs & Attribute::TEXCOORD) {
        attributes &= Attribute::TEXCOORD;
        std::cerr << "Shape has no texcoords" << std::endl;
      }
    }

    for (unsigned i = 0; i < curr_mesh.positions.size(); i+=3) {
      vertex_data.push_back(curr_mesh.positions[i]);
      vertex_data.push_back(curr_mesh.positions[i + 1]);
      vertex_data.push_back(curr_mesh.positions[i + 2]);

      if (has_normals) {
        vertex_data.push_back(curr_mesh.normals[i]);
        vertex_data.push_back(curr_mesh.normals[i + 1]);
        vertex_data.push_back(curr_mesh.normals[i + 2]);
      }

      if (has_uvs) {
        vertex_data.push_back(curr_mesh.texcoords[i]);
        vertex_data.push_back(curr_mesh.texcoords[i + 1]);
        vertex_data.push_back(curr_mesh.texcoords[i + 2]);
      }

    }

    // add triangles
    for (unsigned i = 0; i < curr_mesh.indices.size(); ++i) {
      triangles.push_back(vertex_offset + curr_mesh.indices[i]);
    }

    // increase vertex offset by number of verts of current mesh
    vertex_offset += curr_mesh.positions.size() / 3;
  }

  return mesh{vertex_data, attributes, triangles};
}

};