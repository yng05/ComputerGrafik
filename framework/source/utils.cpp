#include "utils.hpp"

#include <glbinding/gl/gl.h>
// load glbinding extensions
#include <glbinding/Binding.h>
// load meta info extension
#include <glbinding/Meta.h>
// load callback support
#include <glbinding/callbacks.h>

#include <iostream>
#include <sstream>

using glbinding::Meta;

namespace utils {
bool query_gl_error() {
  bool error_occured = false;

  GLenum error = glGetError();
  while(error != GL_NO_ERROR) {
    std::cerr << "OpenGL Error: " << Meta::getString(error) << std::endl;
    error = glGetError();

    error_occured = true;
  }

  return error_occured;
}

void watch_gl_errors(bool activate) {
  if(activate) {
    // add callback after each function call
    glbinding::setCallbackMaskExcept(glbinding::CallbackMask::After | glbinding::CallbackMask::ParametersAndReturnValue, { "glGetError" });
    glbinding::setAfterCallback(
      [](glbinding::FunctionCall const& call) {
        GLenum error = glGetError();
        if (error != GL_NO_ERROR) {
          // print name
          std::cerr <<  "OpenGL Error: " << call.function->name() << "(";
          // parameters
          for (unsigned i = 0; i < call.parameters.size(); ++i)
          {
            std::cerr << call.parameters[i]->asString();
            if (i < call.parameters.size() - 1)
              std::cerr << ", ";
          }
          std::cerr << ")";
          // return value
          if(call.returnValue) {
            std::cerr << " -> " << call.returnValue->asString();
          }
          // error
          std::cerr  << " - " << Meta::getString(error) << std::endl;

          exit(EXIT_FAILURE);
        }
      }
    );
  }
  else {
    glbinding::setCallbackMask(glbinding::CallbackMask::None);
  }
}

void validate_program(GLuint program) {
  glValidateProgram(program);
  // check if validation was successfull
  GLint success = 0;
  glGetProgramiv(program, GL_VALIDATE_STATUS, &success);
  if(success == 0) {
    // get log length
    GLint log_size = 0;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_size);
    // get log
    GLchar* log_buffer = (GLchar*)malloc(sizeof(GLchar) * log_size);
    glGetProgramInfoLog(program, log_size, &log_size, log_buffer);
    // output errors
    output_log(log_buffer, "program nr. " + program);
    // free broken program
    glDeleteProgram(program);
    free(log_buffer);

    throw std::logic_error("Validation of program nr. " + program);
  }
}

GLint get_bound_VAO() {
  GLint array = -1;
  glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &array);

  return array;
}

void glsl_error(int error, const char* description) {
  std::cerr << "GLSL Error " << error << " : "<< description << std::endl;
}

std::string file_name(std::string const& file_path) {
  return file_path.substr(file_path.find_last_of("/\\") + 1);
}

void output_log(GLchar const* log_buffer, std::string const& prefix) {
  std::string error{};
  std::istringstream error_stream{log_buffer};
  while(std::getline(error_stream, error)) {
    std::cerr << prefix << " - " << error << std::endl;
  }
}

void print_bound_textures() {
  GLint id1, id2, id3, active_unit, texture_units = 0;
  glGetIntegerv(GL_ACTIVE_TEXTURE, &active_unit);
  std::cout << "Active texture unit: " << active_unit - GLint(GL_TEXTURE0) << std::endl;

  glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &texture_units);

  for(GLint i = 0; i < texture_units; ++i) {
    glActiveTexture(GL_TEXTURE0 + i);
    glGetIntegerv(GL_TEXTURE_BINDING_3D, &id3);
    glGetIntegerv(GL_TEXTURE_BINDING_2D, &id2);
    glGetIntegerv(GL_TEXTURE_BINDING_1D, &id1);
    if(id1 != 0 || id2 != 0 || id3 != 0) {
      std::cout <<"Texure unit " << i << " - ";
      if(id1 != 0) std::cout << "1D: " << id1 << ", ";
      if(id2 != 0) std::cout << "2D: " << id2 << ", ";
      if(id3 != 0) std::cout << "3D: " << id3;
      std::cout << std::endl;
    }
  }
  // reactivate previously active unit
  glActiveTexture(GLenum(active_unit));
}

};