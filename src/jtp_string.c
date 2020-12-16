#include "jtp_string.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

/* TODO error check and be safe and what not */
char* StringLeftTrim(const char* string, const char* chaff) {
  size_t length = strlen(string);

  int i;
  for (i = 0; i < length; ++i) {
    if (!StringContainsCharacter(chaff, string[i])) {
      break;
    }
  }

  int remaining = length - i;
  char *new = malloc(sizeof(char) * remaining + 1);
  strncpy(new, string + i, remaining);
  new[remaining] = '\0';
  return new;
}

char* StringRightTrim(char* string, const char* chaff) {
  size_t length = strlen(string);

  int i;
  for (i = length - 1; i >= 0; --i) {
    if (!StringContainsCharacter(chaff, string[i])) {
      break;
    }
  }

  char *new = malloc(sizeof(char) * i + 2);
  strncpy(new, string, i + 1);
  new[i + 1] = '\0';
  return new;
}

bool StringContainsCharacter(const char* string, char character) {
  for (const char *p = string; *p != '\0'; ++p) {
    if (*p == character) {
      return true;
    }
  }
  return false;
}

bool StringContainsAnyCharacter(const char* string, const char* characters) {
  for (const char *p = string; *p != '\0'; ++p) {
    for (const char *c = characters; *c != '\0'; ++c) {
      if (strcmp(p, c) == 0) {
        return true;
      }
    }
  }
  return false;
}