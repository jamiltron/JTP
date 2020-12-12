#include "jtp_assets.h"
#include <stdio.h>
#include <stdlib.h>

const char *ReadFile(const char* path) {
  FILE *file = NULL;
#ifdef _WIN32
  errno_t err = fopen_s(file, path, "rb");
  if (err != EXIT_SUCCESS) {
    printf("Error loading file %s\n", path);
    return NULL;
  }
#elif linux
  file = fopen(path, "rb");
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
