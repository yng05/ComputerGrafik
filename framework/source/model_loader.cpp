#include "model_loader.hpp"

// use floats and med precision operations
#define GLM_PRECISION_MEDIUMP_FLOAT
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/geometric.hpp>

#include <iostream>

namespace model_loader {

void generate_normals(tinyobj::mesh_t& model);

std::pair<std::vector<glm::vec3>, std::vector<glm::vec3>> generate_tangents(tinyobj::mesh_t const& model);

model obj(std::string const& name, model::attrib_flag_t import_attribs){
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

  model::attrib_flag_t attributes{model::POSITION | import_attribs};

  // if(import_attribs & model::TANGENT) {
  //   // create tangents and bitangents?
  //   throw std::invalid_argument("Attribute nr. " + std::to_string(model::TANGENT) + "not supported");


  // }

  std::vector<float> vertex_data;
  std::vector<unsigned> triangles;

  std::vector<glm::vec3> tangents;
  std::vector<glm::vec3> bitangents;

  GLuint vertex_offset = 0;

  for (auto& shape : shapes) {
    tinyobj::mesh_t& curr_mesh = shape.mesh;
    // prevent MSVC warning due to Win BOOL implementation
    bool has_normals = (import_attribs & model::NORMAL) != 0;
    if(has_normals) {
      // generate normals if necessary
      if (curr_mesh.normals.empty()) {
        generate_normals(curr_mesh);
      }
    }

    bool has_uvs = (import_attribs & model::TEXCOORD) != 0;
    if(has_uvs) {
      if (curr_mesh.texcoords.empty()) {
        has_uvs = false;
        attributes ^= model::TEXCOORD;
        std::cerr << "Shape has no texcoords" << std::endl;
      }
    }

    bool has_tangents = (import_attribs & model::TANGENT);
    if (has_normals && has_tangents) {
      auto p_bt = generate_tangents(curr_mesh);
      tangents = p_bt.first;
      bitangents = p_bt.second;

      // attributes ^= model::TANGENT;
      // attributes ^= model::BITANGENT;
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

      if (has_tangents) {
        vertex_data.push_back(tangents[i].x);
        vertex_data.push_back(tangents[i].y);
        vertex_data.push_back(tangents[i].z);

        vertex_data.push_back(bitangents[i].x);
        vertex_data.push_back(bitangents[i].y);
        vertex_data.push_back(bitangents[i].z);
      }
    }

    // add triangles
    for (unsigned i = 0; i < curr_mesh.indices.size(); ++i) {
      triangles.push_back(vertex_offset + curr_mesh.indices[i]);
    }

    vertex_offset += GLuint(curr_mesh.positions.size() / 3);
  }

  return model{vertex_data, attributes, triangles};
}

void generate_normals(tinyobj::mesh_t& model) {
  std::vector<glm::vec3> positions(model.positions.size() / 3);

  for (unsigned i = 0; i < model.positions.size(); i+=3) {
    positions[i / 3] = glm::vec3{model.positions[i], model.positions[i + 1], model.positions[i + 2]};
  }

  std::vector<glm::vec3> normals(model.positions.size() / 3, glm::vec3{0.0f});
  for (unsigned i = 0; i < model.indices.size(); i+=3) {
    glm::vec3 normal = glm::cross(positions[model.indices[i+1]] - positions[model.indices[i]], positions[model.indices[i+2]] - positions[model.indices[i]]);

    normals[model.indices[i]] += normal;
    normals[model.indices[i+1]] += normal;
    normals[model.indices[i+2]] += normal;
  }

  model.normals.reserve(model.positions.size());
  for (unsigned i = 0; i < normals.size(); ++i) {
    glm::vec3 normal = glm::normalize(normals[i]);
    model.normals[i * 3] = normal[0];
    model.normals[i * 3 + 1] = normal[1];
    model.normals[i * 3 + 2] = normal[2];
  }
}

std::pair<std::vector<glm::vec3>, std::vector<glm::vec3>> generate_tangents(tinyobj::mesh_t const& model) {
  // containers for vetex attributes
  std::vector<glm::vec3> positions(model.positions.size() / 3);
  std::vector<glm::vec3> normals(model.positions.size() / 3);
  std::vector<glm::vec2> texcoords(model.positions.size() / 3);
  std::vector<glm::vec3> tangents(model.positions.size() / 3, glm::vec3{0.0f});
  std::vector<glm::vec3> bitangents(model.positions.size() / 3);

  // get vertex positions and texture coordinates from mesh_t
  for (unsigned i = 0; i < model.positions.size(); i+=3) {
    positions[i / 3] = glm::vec3{model.positions[i],
                                 model.positions[i + 1],
                                 model.positions[i + 2]};
    normals[i / 3] = glm::vec3{model.normals[i],
                                 model.normals[i + 1],
                                 model.normals[i + 2]};
  }
  for (unsigned i = 0; i < model.texcoords.size(); i+=2) {
    texcoords[i / 2] = glm::vec2{model.texcoords[i], model.texcoords[i + 1]};
  }

  // calculate tangent for triangles
  for (unsigned i = 0; i < model.indices.size() / 3; i++) {
    // indices of vertices of this triangle, access any attribute of first vert with "attribute[indices[0]]"
    unsigned indices[3] = {model.indices[i * 3],
                           model.indices[i * 3 + 1],
                           model.indices[i * 3 + 2]};
    
    // implement tangent calculation here
    auto p0 = positions[indices[0]];
    auto p1 = positions[indices[1]];
    auto p2 = positions[indices[2]];

    auto uv0 = texcoords[indices[0]];
    auto uv1 = texcoords[indices[1]];
    auto uv2 = texcoords[indices[2]];

    auto duv1 = uv1 - uv0;
    auto duv2 = uv2 - uv0;

    auto dp1 = p1 - p0;
    auto dp2 = p2 - p0;

    auto f = 1 / (duv1.x * duv2.y - duv2.x * duv1.y);
    glm::mat2x2 A {{duv2.y, -duv1.y}, {-duv2.x, duv1.x}};
    glm::mat3x2 B = glm::transpose(glm::mat2x3{dp1, dp2});

    auto TB = glm::transpose(f * A * B);

    auto tangent = glm::normalize(TB[0]);

    tangents[indices[0]] = tangent;
    tangents[indices[1]] = tangent;
    tangents[indices[2]] = tangent;
  }

  for (unsigned i = 0; i < tangents.size(); ++i) {
    // implement orthogonalization and normalization here
    auto n = normals[i];
    auto t = tangents[i];
    t = t - n * glm::dot(n, t);
    tangents[i] = t;
    bitangents[i] = glm::cross(n, t);
  }

  return std::make_pair(tangents, bitangents);
}



};