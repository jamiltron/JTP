#ifndef JTP_NINI_H
#define JTP_NINI_H
#include "jtp_math.h"

typedef enum NiniTokenType {
  NiniTableToken,
  NiniIdentifierToken,
  NiniEqualsToken,
  NiniEndToken
} NiniTokenType;

typedef struct NiniToken {
  NiniTokenType type;
  const char* value;
} NiniToken;

typedef enum NiniEntryType {
  None,
  Integer,
  String,
  Bool
} NiniEntryType;

typedef struct NiniValue {
  NiniEntryType entryType;
  union {
    int integer;
    char* string;
    bool boolean;
  } value;
} NiniValue;

typedef struct NiniEntry {
  char* key;
  NiniValue value;
} NiniEntry;

typedef struct NiniTable {
  const char* name;
  uint count;
  NiniEntry** entries;
} NiniTable;

typedef struct Nini {
  const char* name;
  uint count;
  NiniTable** tables;
} Nini;

NiniToken* NiniTokenize(const char* source);
Nini* NiniNew(NiniToken* tokens, const char* name);
void NiniFree(Nini* nini);

#endif
