#include "jtp_assets.h"
#include "jtp_nini.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Nini* NiniReadFile(const char* path, const char* name) {
  Nini *nini = malloc(sizeof(NiniTable));
  nini->name = name;
  nini->tables = NULL;

  char* str = ReadFile(path);
  char *tablePtr, *token;

#ifdef _WIN32
  token = strtok_s(str, "\t\n ", &tablePtr);
  if (token[0] == '[') { // we are in table parsing land
    ParseNiniTableName(token);
  }
   while (token) {
     printf("%s\n", token);
     token = strtok_s(NULL, "\t\n ", &tablePtr);
   }
#else
#endif

  return nini;
}

NiniEntry ParseNiniEntry(char* token) {
  char* sep;
  char* lhs;
  char* rhs;

  sep = strchr(token, '=');
  if (sep) {
    size_t lhsLen = sep - token;
    size_t rhsLen = strlen(token) - (lhsLen + 1);

    lhs = malloc(lhsLen);
    strncpy(lhs, token, lhsLen);
    lhs[lhsLen] = '\0';

    rhs = malloc(rhsLen);
    strncpy(rhs, token+lhsLen+1, rhsLen);
    rhs[rhsLen] = '\0';

    return (NiniEntry) { .key = lhs, .value = ParseNiniValue(rhs)};
  }
  return (NiniEntry) {.key = NULL, .value = (NiniValue) { .entryType = None }};
}

NiniValue ParseNiniValue(char* token) {
  if (isalpha((unsigned char) token[0])) {
    return (NiniValue) { .entryType = String, .value.string = token };
  } else if (isdigit((unsigned char) token[0])) {
    int i = atoi(token);
    return (NiniValue) { .entryType = Integer, .value.integer = i};
  } else {
    return (NiniValue) { .entryType = None };
  }
}

char* ParseNiniTableName(char* token) {
  size_t len = strlen(token);
  char* tableName = malloc(sizeof(char) * len - 3);
  strncpy(tableName, token+1, len-3);
  tableName[len-3] = '\0';
  printf("tableName: %s\n", tableName);
  return tableName;
}
