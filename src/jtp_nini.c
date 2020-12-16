#include "jtp_assets.h"
#include "jtp_nini.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int CountFollowingEntries(char* table);

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
     token = strtok_s(NULL, "\t\n ", &tablePtr);
   }
#else
#endif

  return nini;
}

Nini* NiniCreate(const char* source, const char* name) {
  Nini* nini = malloc(sizeof(Nini));
  nini->name = name;
  nini->tables = NULL;
  nini->count = 1;

  char* tablePtr;

  for (const char* s = source; s != '\0'; ++s) {
    if (*s == '[') {
      tablePtr = s;

    }
  }

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
  return tableName;
}

int CountFollowingEntries(char* table) {
  return 0;
}

NiniToken* NiniTokenize(const char* source, int* count) {
  NiniToken tokens[1024];
  *count = 0;

  char *head;
  char *lookahead;

  head = source;
  while (*head != '\0') {
    if (*head == '[') {
      lookahead = head;
      while (*lookahead != ']') {
        lookahead++;
      }

      int diff = lookahead - head;
      char* name = malloc(sizeof(char) * diff);
      strncpy(name, head+1, diff - 1);
      name[diff - 1] = '\0';
      tokens[*count] = (NiniToken) { .type = NiniTableToken, .value = name };
      *count += 1;
      head = lookahead + 1;
    }

    if (isalnum((unsigned char) *head)) {
      lookahead = head;

      while (isalnum((unsigned char) *lookahead)) {
        lookahead++;
      }

      int diff = lookahead - head;
      char* name = malloc(sizeof(char) * diff + 1);
      strncpy(name, head, diff);
      name[diff] = '\0';
      tokens[*count] = (NiniToken) { .type = NiniIdentifierToken, .value = name };
      *count += 1;
      head = lookahead-1;
    }

    if (*head == '=') {
      tokens[*count] = (NiniToken) {.type = NiniEqualsToken, .value = '='};
      *count += 1;
    }

    head++;
  }

  NiniToken* result = malloc(sizeof(NiniToken) * (*count));
  memset(result, *count, 0);

  for (int i = 0; i < *count; ++i) {
    result[i] = tokens[i];
  }

  return result;
}