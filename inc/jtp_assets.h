#ifndef JTP_ASSETS_H
#define JTP_ASSETS_H
#include "jtp_shader_program.h"
#include "jtp_texture2d.h"
#include <stdbool.h>

typedef struct Assets Assets;

// TODO: probably accept a context path or something
Assets *Assets_New(void);

const char *Assets_ReadFile(const char *path);
void Assets_Clear(Assets *assets);
void Assets_Delete(Assets *assets);

// Shaders
ShaderProgram *Assets_LoadShader(Assets *assets, const char *name, const char *vertPath,
               const char *fragPath);
ShaderProgram *Assets_GetShader(Assets *assets, const char *name);
void Assets_UnloadShader(Assets *assets, const char *name);

// Textures
Texture2D *Assets_LoadTexture2D(Assets *assets, const char *name, const char *path, bool alpha);
Texture2D *Assets_GetTexture2D(Assets *assets, const char *name);

#endif
