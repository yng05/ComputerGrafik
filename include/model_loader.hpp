#ifndef MODEL_LOADER_HPP
#define MODEL_LOADER_HPP

#include "mesh.hpp"
#include "tiny_obj_loader.h"

namespace model_loader {

mesh obj(std::string const& path, Attributes import_attribs = Attribute::POSITION);

}

#endif