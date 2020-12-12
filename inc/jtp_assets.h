#ifndef JTP_ASSETS_H
#define JTP_ASSETS_H
#include "jtp_shader_program.h"

const char *ReadFile(const char* path);
ShaderProgram* LoadShader(const char* vertPath, const char* fragPath);

#endif
