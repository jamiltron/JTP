#ifndef JTP_SHADER_PROGRAM_H
#define JTP_SHADER_PROGRAM_H
#include "jtp_math.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdbool.h>

typedef struct ShaderProgram {
  uint id;
} ShaderProgram;

ShaderProgram* ShaderProgramNew(const char *vertCode, const char* fragCode);
uint ShaderCompile(const char *shaderCode, GLenum type);

void ShaderDelete(ShaderProgram *program);
void ShaderSetVector4f(ShaderProgram *this, const char *name, Vec4 *value, bool useShader);
void ShaderSetMatrix4(ShaderProgram* this, const char* name, Mat4x4 *matrix, bool useShader);

#endif
