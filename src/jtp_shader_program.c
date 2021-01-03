#include "jtp_constants.h"
#include "jtp_shader_program.h"
#include <stdio.h>
#include <stdlib.h>
#include "glad/glad.h"

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

void ShaderSetVector4f(ShaderProgram *this, const char *name, Vec4 *vec, bool useProgram) {
  if (useProgram) {
    ShaderProgramUse(this);
  }
  glUniform4f(glGetUniformLocation(this->id, name), vec->x, vec->y, vec->z, vec->w);
}

void ShaderSetColor4f(ShaderProgram *this, const char *name, Color *color, bool useProgram) {
  if (useProgram) {
    ShaderProgramUse(this);
  }
  glUniform4f(glGetUniformLocation(this->id, name), color->r, color->g, color->b, color->a);
}

void ShaderSetMatrix4(ShaderProgram *this, const char *name, Mat4 *mat4, bool useProgram) {
  if (useProgram) {
    ShaderProgramUse(this);
  }
  float m[16] = { mat4->x0, mat4->y0, mat4->z0, mat4->w0,
    mat4->x1, mat4->y1, mat4->z1, mat4->w1,
    mat4->x2, mat4->y2, mat4->z2, mat4->w2,
    mat4->x3, mat4->y3, mat4->z3, mat4->w3,
  };

  glUniformMatrix4fv(glGetUniformLocation(this->id, name), 1, false, &m[0]);
}

uint ShaderGetUniformLocation(ShaderProgram *this, const char *name) {
  return glGetUniformLocation(this->id, name);
}
