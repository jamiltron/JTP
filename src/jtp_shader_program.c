#include "jtp_constants.h"
#include "jtp_shader_program.h"
#include <stdio.h>
#include <stdlib.h>
#include <glad/glad.h>

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
    printf("Error compiling shader: %s\n", infoLog);
  }

  return shader;
}

void ShaderProgramUse(ShaderProgram* this) {
  glUseProgram(this->id);
}

void ShaderDelete(ShaderProgram* program) {
  glDeleteProgram(program->id);
  free(program);
}

void ShaderSetVector4f(ShaderProgram* this, const char *name, Vec4 *vec, bool useProgram) {
  if (useProgram) {
    ShaderProgramUse(this);
  }
  glUniform4f(glGetUniformLocation(this->id, name), vec->x, vec->y, vec->z, vec->w);
}

void ShaderSetMatrix4(ShaderProgram* this, const char* name, Mat4x4 *matrix, bool useProgram) {
  if (useProgram) {
    ShaderProgramUse(this);
  }
  float m[16] = { matrix->x0, matrix->y0, matrix->z0, matrix->w0,
    matrix->x1, matrix->y1, matrix->z1, matrix->w1,
    matrix->x2, matrix->y2, matrix->z2, matrix->w2,
    matrix->x3, matrix->y3, matrix->z3, matrix->w3,
  };

  glUniformMatrix4fv(glGetUniformLocation(this->id, name), 1, false, &m[0]);
}
