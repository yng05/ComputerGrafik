#include "texture_loader.hpp"

// request supported types
#define STBI_ONLY_JPEG
#define STBI_ONLY_PNG
#define STBI_ONLY_TGA
#define STBI_NO_LINEAR
// get extensive error on failure
#define STBI_FAILURE_USERMSG
// create implementation here
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
 
#include <cstdint> 
#include <cstring> 

namespace texture_loader {
texture file(std::string const& file_name) {
  uint8_t* data_ptr;
  int width = 0;
  int height = 0;
  int format = STBI_default;
  data_ptr = stbi_load(file_name.c_str(), &width, &height, &format, STBI_rgb_alpha);

  if(!data_ptr) {
    throw std::logic_error(std::string{"stb_image: "} + stbi_failure_reason());
  }

  GLenum target = GL_TEXTURE_2D;
  if(height == 1) {
    target = GL_TEXTURE_1D;
  }

  // determine format of image data, internal format should be sized
  GLenum pixel_format = GL_NONE;
  std::size_t num_components = 0;
  if (format == STBI_grey) {
    pixel_format = GL_RED;
    num_components = 1;
  }
  else if (format == STBI_grey_alpha) {
    pixel_format = GL_RG;
    num_components = 2;
  }
  else if (format == STBI_rgb) {
    pixel_format = GL_RGB;
    num_components = 3;
  }
  else if (format == STBI_rgb_alpha) {
    pixel_format = GL_RGBA;
    num_components = 4;
  }
  else {
    throw std::logic_error("stb_image: misinterpreted data, incorrect format");
  }

  std::vector<uint8_t> texture_data(width * height * num_components);
  // copy data to vector
  std::memcpy(&texture_data[0], data_ptr, texture_data.size());
  stbi_image_free(data_ptr);

  return ::texture{texture_data, target, pixel_format, GL_UNSIGNED_BYTE, width, height};
}

};