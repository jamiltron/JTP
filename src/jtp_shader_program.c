#include "jtp_constants.h"
#include "jtp_shader_program.h"
#include "jtp_types.h"
#include <stdio.h>
#include <stdlib.h>

ShaderProgram* ShaderProgramNew(const char *vertCode, const char *fragCode) {
  ShaderProgram* program = malloc(sizeof(ShaderProgram));
  uint vert = ShaderCompile(vertCode, GL_VERTEX_SHADER);
  uint frag = ShaderCompile(fragCode, GL_FRAGMENT_SHADER);

  program->id = glCreateProgram();
  glAttachShader(program->id, vert);
  glAttachShader(program->id, frag);
  glLinkProgram(program->id);

  int success;
  char infoLog[INFO_LOG_LEN];
  glGetProgramiv(program->id, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(program->id, INFO_LOG_LEN, NULL, infoLog);
    printf("Failed linking shader program %s\n", infoLog);
  }

  glDeleteShader(vert);
  glDeleteShader(frag);
  return program;
}

uint ShaderCompile(const char* shaderCode, GLenum type) {
  uint shader = glCreateShader(type);
  glShaderSource(shader, 1, &shaderCode, NULL);
  glCompileShader(shader);

  int success;
  char infoLog[INFO_LOG_LEN];
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(shader, INFO_LOG_LEN, NULL, infoLog);
  }
  printf("Error compiling shader: %s\n", infoLog);

  return shader;
}

void ShaderDelete(ShaderProgram* program) {
  glDeleteProgram(program->id);
  free(program);
}
