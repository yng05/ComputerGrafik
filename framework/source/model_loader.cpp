#include "model_loader.hpp"

// use floats and med precision operations
#define GLM_PRECISION_MEDIUMP_FLOAT
#include <glm/vec3.hpp>
#include <glm/geometric.hpp>

#include <iostream>

namespace model_loader {

mesh obj(std::string const& name, mesh::attrib_flag_t import_attribs){
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

  mesh::attrib_flag_t attributes{mesh::POSITION | import_attribs};

  if(import_attribs & mesh::TANGENT) {
    // create tangents and bitangents?
    throw std::invalid_argument("Attribute nr. " + std::to_string(mesh::TANGENT) + "not supported");
  }

  std::vector<float> vertex_data;
  std::vector<unsigned> triangles;

  GLuint vertex_offset = 0;

  for (auto& shape : shapes) {
    tinyobj::mesh_t& curr_mesh = shape.mesh;
    
    bool has_normals = import_attribs & mesh::NORMAL;
    if(has_normals) {
      // generate normals if necessary
      if (curr_mesh.normals.empty()) {
        generate_normals(curr_mesh);
      }
    }

    bool has_uvs = import_attribs & mesh::TEXCOORD;
    if(has_uvs) {
      if (curr_mesh.texcoords.empty()) {
        has_uvs = false;
        attributes ^= mesh::TEXCOORD;
        std::cerr << "Shape has no texcoords" << std::endl;
      }
    }

    // push back vertex attributes
    for (unsigned i = 0; i < curr_mesh.positions.size() / 3; ++i) {
      vertex_data.push_back(curr_mesh.positions[i * 3]);
      vertex_data.push_back(curr_mesh.positions[i * 3 + 1]);
      vertex_data.push_back(curr_mesh.positions[i * 3 + 2]);

      if (has_normals) {
        vertex_data.push_back(curr_mesh.normals[i * 3]);
        vertex_data.push_back(curr_mesh.normals[i * 3 + 1]);
        vertex_data.push_back(curr_mesh.normals[i * 3 + 2]);
      }

      if (has_uvs) {
        vertex_data.push_back(curr_mesh.texcoords[i * 2]);
        vertex_data.push_back(curr_mesh.texcoords[i * 2 + 1]);
      }
    }

    // add triangles
    for (unsigned i = 0; i < curr_mesh.indices.size(); ++i) {
      triangles.push_back(vertex_offset + curr_mesh.indices[i]);
    }

    vertex_offset += GLuint(curr_mesh.positions.size() / 3);
  }

  return mesh{vertex_data, attributes, triangles};
}

void generate_normals(tinyobj::mesh_t& mesh) {
  std::vector<glm::vec3> positions(mesh.positions.size() / 3);

  for (unsigned i = 0; i < mesh.positions.size(); i+=3) {
    positions[i / 3] = glm::vec3{mesh.positions[i], mesh.positions[i + 1], mesh.positions[i + 2]};
  }

  std::vector<glm::vec3> normals(mesh.positions.size() / 3, glm::vec3{0.0f});
  for (unsigned i = 0; i < mesh.indices.size(); i+=3) {
    glm::vec3 normal = glm::cross(positions[mesh.indices[i+1]] - positions[mesh.indices[i]], positions[mesh.indices[i+2]] - positions[mesh.indices[i]]);

    normals[mesh.indices[i]] += normal;
    normals[mesh.indices[i+1]] += normal;
    normals[mesh.indices[i+2]] += normal;
  }

  mesh.normals.reserve(mesh.positions.size());
  for (unsigned i = 0; i < normals.size(); ++i) {
    glm::vec3 normal = glm::normalize(normals[i]);
    mesh.normals[i * 3] = normal[0];
    mesh.normals[i * 3 + 1] = normal[1];
    mesh.normals[i * 3 + 2] = normal[2];
  }
}

};