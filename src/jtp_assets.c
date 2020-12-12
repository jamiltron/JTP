#include "jtp_assets.h"
#include "jtp_constants.h"
#include "jtp_shader_program.h"
#include "jtp_types.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ShaderEntry {
  ShaderProgram *program;
  const char* name;
} ShaderEntry;


static uint _entryIndex = 0;
static ShaderEntry _shaders[MAX_SHADERS] = {NULL};

static bool IsEntryOpen(uint i);

const char *ReadFile(const char* path) {
  FILE *file = NULL;
#ifdef _WIN32
  errno_t err = fopen_s(file, path, "r");
  if (err != EXIT_SUCCESS) {
    printf("Error loading file %s\n", path);
    return NULL;
  }
#elif linux
  file = fopen(path, "r");
  if (file == NULL) {
    printf("Error loading file: %s\n", path);
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

ShaderProgram* LoadShader(const char* name, const char* vertPath, const char* fragPath) {
  while (_entryIndex < MAX_SHADERS && !IsEntryOpen(_entryIndex)) {
    _entryIndex++;
  }

  if (_entryIndex >= MAX_SHADERS) {
    printf("Unable to load new shader %s, MAX_SHADER (%i) already loaded\n", name, MAX_SHADERS);
    return NULL;
  }

  const char* vertCode = ReadFile(vertPath);
  const char* fragCode = ReadFile(fragPath);

  ShaderProgram* program = ShaderProgramNew(vertCode, fragCode);
  _shaders[_entryIndex++] = (ShaderEntry){ .program = program, .name = name };
  return program;
}

ShaderProgram* GetShader(const char* name) {
  for (size_t i = 0; i < _entryIndex; ++i) {
    if (strcmp(name, _shaders[i].name) == 0) {
      return _shaders[i].program;
    }
  }
  return NULL;
}

void UnloadShader(const char *name) {
  for (size_t i = 0; i < _entryIndex; ++i) {
    if (strcmp(name, _shaders[i].name) == 0) {
      ShaderDelete(_shaders[i].program);
      _shaders[i].name = NULL;
      _entryIndex = i;
    }
  }
}

static bool IsEntryOpen(uint i) {
  return _shaders[i].name == NULL && _shaders[i].program == NULL;
}
