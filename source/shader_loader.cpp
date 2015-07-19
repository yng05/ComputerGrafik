#include "shader_loader.hpp"

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>

namespace shader_loader {

static char* read_file(std::string const& file_name) {
  char* text = 0;

  FILE *file = fopen(file_name.c_str(), "rt");

  if (file != 0) {
    fseek(file, 0, SEEK_END);
    int count = ftell(file);
    rewind(file);

    if (count > 0) {
      text = (char*)malloc(sizeof(char) * (count + 1));
      count = fread(text, sizeof(char), count, file);
      text[count] = '\0';
    }
    fclose(file);
  }
  else {
    std::cerr << "File \'" << file_name << "\' not found" << std::endl;
  }

  return text;
}

static void validate_shader(GLuint shader, std::string const& file_name) {
  const unsigned int BUFFER_SIZE = 512;
  char buffer[BUFFER_SIZE];
  memset(buffer, 0, BUFFER_SIZE);
  GLsizei length = 0;

  glGetShaderInfoLog(shader, BUFFER_SIZE, &length, buffer);
  if (length > 0) {
    std::cerr << "Shader " << shader << " (" << file_name << ") compile Log: " << buffer << std::endl;
  }
}

GLuint load(std::string const& file_name, GLenum shader_type) {

  GLuint shader_id = 0;
  const char* glsl_source;

  glsl_source = read_file(file_name);

  shader_id = glCreateShader(shader_type);

  glShaderSource(shader_id, 1, &glsl_source, 0);
  glCompileShader(shader_id);
  validate_shader(shader_id, file_name);

  return shader_id;
}

GLuint create(std::string const& vertex_name, std::string const& fragment_name) {

  GLuint shader_id = glCreateProgram();

  //load vert and frag shader
  GLuint vertex_shader = load(vertex_name, GL_VERTEX_SHADER);
  GLuint fragment_shader = load(fragment_name, GL_FRAGMENT_SHADER);

  //attach the different shader components to the shader program
  glAttachShader(shader_id, vertex_shader);
  glAttachShader(shader_id, fragment_shader);
  //and compile it
  glLinkProgram(shader_id);

  //program is linked, so we can detach compiled shaders again
  glDetachShader(shader_id, vertex_shader);
  glDetachShader(shader_id, fragment_shader);
  // free objects after linking
  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);

  return shader_id;
}

};