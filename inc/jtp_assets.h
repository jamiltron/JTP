#ifndef JTP_ASSETS_H
#define JTP_ASSETS_H
#include "jtp_shader_program.h"
#include "jtp_texture2d.h"

const char *Assets_ReadFile(const char *path);
void Assets_Clear(void);

// Shaders
ShaderProgram *Assets_LoadShader(const char *name, const char *vertPath,
               const char *fragPath);
ShaderProgram *Assets_GetShader(const char *name);
void Assets_UnloadShader(const char *name);

// Textures
Texture2D *Assets_LoadTexture2D(const char *name, const char *path, bool alpha);
Texture2D *Assets_GetTexture2D(const char *name);


#endif
