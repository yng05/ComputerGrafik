#include "model_loader.hpp"
#include <iostream>

namespace model_loader {

mesh obj(std::string const& name, attrib_flag_t import_attribs){
  std::vector<tinyobj::shape_t> shapes;
  std::vector<tinyobj::material_t> materials;

  std::string err = tinyobj::LoadObj(shapes, materials, name.c_str());

  if (!err.empty()) {
    if (err[0] == 'W' && err[1] == 'A' && err[2] == 'R') {
      std::cerr << "tinyobjloader: " << err << std::endl;    
    }
    else {
      throw std::logic_error("tinyobjloader: " + err);    
    }
  }

  attrib_flag_t attributes{Attribute::POSITION | import_attribs};

  if(import_attribs & Attribute::TANGENT) {
    // create tangents and bitangents?
    throw std::invalid_argument("Attribute nr. " + std::to_string(Attribute::TANGENT) + "not supported");
  }

  std::vector<float> vertex_data;
  std::vector<unsigned> triangles;

  unsigned vertex_offset = 0;

  for (auto const& shape : shapes) {
    tinyobj::mesh_t const& curr_mesh = shape.mesh;
    // std::cout << curr_mesh.normals.size() << std::endl;
    bool has_normals = true;
    if (curr_mesh.normals.empty()) {
      has_normals = false;
      if(import_attribs & Attribute::NORMAL) {
        // disable attribute
        attributes ^= Attribute::NORMAL;
        // generate normals?
        std::cerr << "Shape has no normals" << std::endl;
      }
    }

    bool has_uvs = true;
    if (curr_mesh.texcoords.empty()) {
      has_uvs = false;
      if(import_attribs & Attribute::TEXCOORD) {
        attributes ^= Attribute::TEXCOORD;
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