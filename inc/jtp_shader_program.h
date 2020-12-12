#ifndef JTP_SHADER_PROGRAM_H
#define JTP_SHADER_PROGRAM_H
#include "jtp_types.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

typedef struct ShaderProgram {
  uint id;
} ShaderProgram;

ShaderProgram* ShaderProgramNew(const char *vertCode, const char* fragCode);
uint ShaderCompile(const char *shaderCode, GLenum type);
void ShaderDelete(ShaderProgram* program);

#endif
