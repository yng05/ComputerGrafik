#ifndef MODEL_LOADER_HPP
#define MODEL_LOADER_HPP

#include "mesh.hpp"
#include "tiny_obj_loader.h"

namespace model_loader {

mesh obj(std::string const& path, mesh::attrib_flag_t import_attribs = mesh::POSITION);

void generate_normals(tinyobj::mesh_t& mesh);

}

#endif