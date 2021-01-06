#include "jtp_string.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

char* StringLeftTrim(const char* string, const char* chaff) {
  if (string == NULL || chaff == NULL) {
    return NULL;
  }

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

char* StringRightTrim(const char* string, const char* chaff) {
  if (string == NULL || chaff == NULL) {
    return NULL;
  }
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
  if (string == NULL || character == '\0') {
    return false;
  }

  for (const char *p = string; *p != '\0'; ++p) {
    if (*p == character) {
      return true;
    }
  }
  return false;
}

bool StringContainsAnyCharacter(const char* string, const char* characters) {
  if (string == NULL || characters == NULL) {
    return false;
  }

  for (const char *p = string; *p != '\0'; ++p) {
    for (const char *c = characters; *c != '\0'; ++c) {
      if (strcmp(p, c) == 0) {
        return true;
      }
    }
  }
  return false;
}

bool StringIsInteger(const char* string) {
  if (!string) {
    return false;
  }

  // check that the first digit isn't led with a 0
  if (*string < '1' || *string > '9') {
    return false;
  }

  // check the rest
  for (const char* c = string+1; *c != '\0'; ++c) {
    if (!isdigit((unsigned int) *c)) {
      return false;
    }
  }
  return true;
}
