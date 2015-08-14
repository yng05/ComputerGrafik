#include "texture_loader.hpp"

// request supported types
#define STBI_ONLY_JPEG
#define STBI_ONLY_PNG
#define STBI_ONLY_TGA
#define STBI_NO_LINEAR
// get extensiv error on failure
#define STBI_FAILURE_USERMSG
// create implementation here
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
 
#include <cstdint> 

namespace texture_loader {
  GLuint texture(std::string const& file_name) {
    uint8_t* data_ptr;
    int width = 0;
    int height = 0;
    int format = STBI_default;
    data_ptr = stbi_load(file_name.c_str(), &width, &height, &format, STBI_rgb_alpha);

    if(!data_ptr) {
      throw std::logic_error(std::string{"stb_image: "} + stbi_failure_reason());
    }

    GLuint texture = 0;
    glGenTextures(1, &texture);
    // bind new tetxure handle to current unit for configuration
    glBindTexture(GL_TEXTURE_2D, texture);
    // if coordinate is outside texture, use border color
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GLint(GL_CLAMP_TO_EDGE));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GLint(GL_CLAMP_TO_EDGE));
    //linear interpolation if texel is smaller/bigger than fragment pixel 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GLint(GL_LINEAR));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GLint(GL_LINEAR));

    // determine format of image data, internal format should be sized
    GLenum source_format = GL_NONE;
    GLenum internal_format = GL_NONE;
    if (format == STBI_grey) {
      source_format = GL_RED;
      internal_format = GL_R8;
    }
    else if (format == STBI_grey_alpha) {
      source_format = GL_RG;
      internal_format = GL_RG8;
    }
    else if (format == STBI_rgb) {
      source_format = GL_RGB;
      internal_format = GL_RGB8;
    }
    else if (format == STBI_rgb_alpha) {
      source_format = GL_RGBA;
      internal_format = GL_RGBA8;
    }
    else {
      throw std::logic_error("stb_image: misinterpreted data, incorrect format");
    }
    // define & upload texture data
    glTexImage2D(GL_TEXTURE_2D, 0, GLint(internal_format), width, height, 0, source_format, GL_UNSIGNED_BYTE, data_ptr);

    stbi_image_free(data_ptr);
    return texture;
  }

};