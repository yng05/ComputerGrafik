#include "shader_loader.hpp"

#include <iostream>
#include <sstream>
#include <fstream>

namespace shader_loader {

std::string read_file(std::string const& name) {

  std::ifstream file_in{name};
  if(file_in) {
    std::string contents;
    file_in.seekg(0, std::ios::end);
    contents.resize(file_in.tellg());
    file_in.seekg(0, std::ios::beg);
    file_in.read(&contents[0], contents.size());
    file_in.close();
    return(contents);
  }
  else {
    std::cerr << "File \'" << name << "\' not found" << std::endl;
    
    throw std::invalid_argument(name);
  } 
}

GLuint shader(std::string const& file_name, GLenum shader_type) {

  GLuint shader = 0;
  shader = glCreateShader(shader_type);

  std::string shader_source{read_file(file_name)};
  // glshadersource expects array of c-strings
  const char* shader_chars = shader_source.c_str();
  glShaderSource(shader, 1, &shader_chars, 0);

  glCompileShader(shader);

  // check if compilation was successfull
  GLint success = 0;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

  if(success == 0) {
    GLint log_size = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_size);

    char log_buffer[log_size];
    glGetShaderInfoLog(shader, log_size, &log_size, log_buffer);

    // output errors
    std::string error{};
    std::istringstream error_stream{log_buffer};
    while(std::getline(error_stream, error)) {
      std::cerr << file_name << " - " << error << std::endl;
    }
    // free broken shader
    glDeleteShader(shader);

    throw std::logic_error(file_name);
  }

  return shader;
}

GLuint program(std::string const& vertex_name, std::string const& fragment_name) {

  GLuint program = glCreateProgram();

  //load vert and frag shader
  GLuint vertex_shader = shader(vertex_name, GL_VERTEX_SHADER);
  GLuint fragment_shader = shader(fragment_name, GL_FRAGMENT_SHADER);

  //attach the different shader components to the shader program
  glAttachShader(program, vertex_shader);
  glAttachShader(program, fragment_shader);
  //and compile it
  glLinkProgram(program);

  //program is linked, so we can detach compiled shaders again
  glDetachShader(program, vertex_shader);
  glDetachShader(program, fragment_shader);
  // free objects after linking
  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);

  return program;
}

};