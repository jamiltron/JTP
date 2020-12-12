#ifndef JTP_ASSETS_H
#define JTP_ASSETS_H
#include "jtp_shader_program.h"

const char* ReadFile(const char *path);
/* TODO still not sure about storing shaders by name */
ShaderProgram* LoadShader(const char *name, const char *vertPath,
                          const char *fragPath);
/* TODO same as above */
ShaderProgram* GetShader(const char *name);
void UnloadShader(const char *name);

#endif
