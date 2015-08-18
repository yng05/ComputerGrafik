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
// helper to get filename from path
static std::string file_name(std::string const& file_path) {
  return file_path.substr(file_path.find_last_of("/\\") + 1);
}

static void output_log(GLchar const* log_buffer, std::string const& prefix) {
  std::string error{};
  std::istringstream error_stream{log_buffer};
  while(std::getline(error_stream, error)) {
    std::cerr << prefix << " - " << error << std::endl;
  }
}

GLuint shader(std::string const& file_path, GLenum shader_type) {

  GLuint shader = 0;
  shader = glCreateShader(shader_type);

  std::string shader_source{read_file(file_path)};
  // glshadersource expects array of c-strings
  const char* shader_chars = shader_source.c_str();
  glShaderSource(shader, 1, &shader_chars, 0);

  glCompileShader(shader);

  // check if compilation was successfull
  GLint success = 0;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if(success == 0) {
    // get log length
    GLint log_size = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_size);
    // get log
    GLchar* log_buffer = (GLchar*)malloc(sizeof(GLchar) * log_size);
    glGetShaderInfoLog(shader, log_size, &log_size, log_buffer);
    // output errors
    output_log(log_buffer, file_name(file_path));
    // free broken shader
    glDeleteShader(shader);
    free(log_buffer);

    throw std::logic_error("Compilation of " + file_path);
  }

  return shader;
}

GLuint program(std::string const& vertex_path, std::string const& fragment_path) {

  GLuint program = glCreateProgram();

  // load and compile vert and frag shader
  GLuint vertex_shader = shader(vertex_path, GL_VERTEX_SHADER);
  GLuint fragment_shader = shader(fragment_path, GL_FRAGMENT_SHADER);

  // attach the shaders to the program
  glAttachShader(program, vertex_shader);
  glAttachShader(program, fragment_shader);
  // link shaders
  glLinkProgram(program);

  // check if linking was successfull
  GLint success = 0;
  glGetProgramiv(program, GL_LINK_STATUS, &success);
  if(success == 0) {
    // get log length
    GLint log_size = 0;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_size);
    // get log
    GLchar* log_buffer = (GLchar*)malloc(sizeof(GLchar) * log_size);
    glGetProgramInfoLog(program, log_size, &log_size, log_buffer);
    // output errors
    output_log(log_buffer, file_name(vertex_path) + " & " + file_name(fragment_path));
    // free broken program
    glDeleteProgram(program);
    free(log_buffer);

    throw std::logic_error("Linking of " + vertex_path + " & " + fragment_path);
  }
  // detach shaders
  glDetachShader(program, vertex_shader);
  glDetachShader(program, fragment_shader);
  // and free them
  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);

  return program;
}

};