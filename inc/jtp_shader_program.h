#ifndef JTP_SHADER_PROGRAM_H
#define JTP_SHADER_PROGRAM_H
#include "jtp_math.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdbool.h>

typedef struct ShaderProgram ShaderProgram;

ShaderProgram* ShaderProgram_New(const char *vertCode, const char* fragCode);
void ShaderProgram_Delete(ShaderProgram *program);
void ShaderProgram_Use(ShaderProgram *program);
void ShaderProgram_SetVector4f(ShaderProgram *this, uint location, Vec4 *value, bool useShader);
void ShaderProgram_SetColor4f(ShaderProgram *this, uint location, Color *color, bool useShader);
void ShaderProgram_SetMatrix4(ShaderProgram *this, uint location, Mat4x4 *matrix, bool useShader);
uint ShaderProgram_GetUniformLocation(ShaderProgram *this, const char *name);

uint Shader_Compile(const char *shaderCode, GLenum type);

#endif
