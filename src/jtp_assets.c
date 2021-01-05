#define STB_IMAGE_IMPLEMENTATION
#include "jtp_assets.h"
#include "jtp_constants.h"
#include "jtp_math.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stb/stb_image.h>

typedef struct ShaderEntry {
  ShaderProgram *program;
  const char *name;
} ShaderEntry;

typedef struct Texture2DEntry {
  Texture2D *texture;
  const char *name;
} Texture2DEntry;

struct Assets {
  uint shaderIndex;
  ShaderEntry shaders[MAX_SHADERS];

  uint texture2DIndex;
  Texture2DEntry textures2D[MAX_TEXTURES_2D];
};

static bool _IsShaderEntryOpen(Assets *assets, uint i);
static bool _IsTexture2DEntryOpen(Assets *assets, uint i);

const char *Assets_ReadFile(const char* path) {
  FILE *file = NULL;
#ifdef _WIN32
  errno_t err = fopen_s(&file, path, "rb");
  if (err != EXIT_SUCCESS) {
    printf("Error loading file %s\n", path);
    return NULL;
  }
#elif linux
  file = fopen(path, "r");
  if (file == NULL) {
    printf("Error loading file: %s\n", path);
    return NULL;
  }
#endif

  fseek(file, 0, SEEK_END);
  const long fileSize = ftell(file);
  rewind(file);

  char* string = malloc(fileSize + 1);
  fread(string, fileSize, 1, file);
  fclose(file);

  string[fileSize] = 0;
  return string;
}

Assets* Assets_New() {
  Assets *assets = malloc(sizeof(Assets));
  assets->shaderIndex = 0;
  for (size_t i = 0; i < MAX_SHADERS; ++i) {
    assets->shaders[i] = (ShaderEntry) { NULL, NULL };
  }

  assets->texture2DIndex = 0;
  for (size_t i = 0; i < MAX_TEXTURES_2D; ++i) {
    assets->textures2D[i] = (Texture2DEntry) { NULL, NULL };
  }
  return assets;
}

void Assets_Clear(Assets *assets) {
  for (size_t i = 0; i < MAX_SHADERS; ++i) {
    if (assets->shaders[i].program != NULL) {
      ShaderProgram_Delete(assets->shaders[i].program);
    }
    assets->shaders[i] = (ShaderEntry) { NULL, NULL };
  }

  for (size_t i = 0; i < MAX_TEXTURES_2D; ++i) {
    if (assets->textures2D[i].texture != NULL) {
      Texture2D_Delete(assets->textures2D[i].texture);
    }
    assets->textures2D[i] = (Texture2DEntry) { NULL, NULL };
  }
}

void Assets_Delete(Assets *assets) {
  Assets_Clear(assets);
  free(assets);
}

ShaderProgram* Assets_LoadShader(Assets *assets, const char* name, const char* vertPath, const char* fragPath) {
  while (assets->shaderIndex < MAX_SHADERS && !_IsShaderEntryOpen(assets, assets->shaderIndex)) {
    assets->shaderIndex++;
  }

  if (assets->shaderIndex >= MAX_SHADERS) {
    printf("Unable to load new shader %s, MAX_SHADER (%i) already loaded\n", name, MAX_SHADERS);
    return NULL;
  }

  const char* vertCode = Assets_ReadFile(vertPath);
  const char* fragCode = Assets_ReadFile(fragPath);

  ShaderProgram* program = ShaderProgram_New(vertCode, fragCode);
  assets->shaders[assets->shaderIndex++] = (ShaderEntry){ .program = program, .name = name };
  return program;
}

ShaderProgram* Assets_GetShader(Assets *assets, const char* name) {
  if (name == NULL) {
    return NULL;
  }
  for (size_t i = 0; i < assets->shaderIndex; ++i) {
    if (strcmp(name, assets->shaders[i].name) == 0) {
      return assets->shaders[i].program;
    }
  }
  return NULL;
}

void Assets_UnloadShader(Assets *assets, const char *name) {

  for (size_t i = 0; i < assets->shaderIndex; ++i) {
    if (strcmp(name, assets->shaders[i].name) == 0) {
      ShaderProgram_Delete(assets->shaders[i].program);
      assets->shaders[i].name = NULL;
      assets->shaderIndex = i;
    }
  }
}

Texture2D *Assets_LoadTexture2D(Assets *assets, const char *name, const char *path, bool alpha) {
  while (assets->texture2DIndex < MAX_TEXTURES_2D && !_IsTexture2DEntryOpen(assets, assets->texture2DIndex)) {
    assets->texture2DIndex++;
  }

  if (assets->texture2DIndex >= MAX_TEXTURES_2D) {
    printf("Unable to load new texture2D %s, MAX_TEXTURES_2D (%i) already loaded\n", name, MAX_TEXTURES_2D);
    return NULL;
  }

  uint width, height;
  int nrChannels;
  uchar *data = stbi_load(path, &width, &height, &nrChannels, 0);
  Texture2D *texture = Texture2D_New(width, height, alpha, data);
  assets->textures2D[assets->texture2DIndex++] = (Texture2DEntry) {.texture = texture, .name = name};
  stbi_image_free(data);

  return texture;
}

Texture2D* Assets_GetTexture2D(Assets *assets, const char* name) {
  if (name == NULL) {
    return NULL;
  }
  for (size_t i = 0; i < assets->texture2DIndex; ++i) {
    if (strcmp(name, assets->textures2D[i].name) == 0) {
      return assets->textures2D[i].texture;
    }
  }
  return NULL;
}

static bool _IsShaderEntryOpen(Assets *assets, uint i) {
  return assets->shaders[i].name == NULL && assets->shaders[i].program == NULL;
}

static bool _IsTexture2DEntryOpen(Assets *assets, uint i) {
  return assets->textures2D[i].name == NULL && assets->textures2D[i].texture == NULL;
}
