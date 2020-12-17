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
  NiniValue* value;
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


Nini* NiniReadFile(const char* path, const char* name);
Nini* NiniCreate(const char* source, const char* name);
void NiniDestroy(Nini* nini);
NiniTable* NiniGetTable(Nini* nini, const char* name);
NiniEntry* NiniGetEntry(Nini* nini, const char* tableName, const char* entryName);
NiniEntry* NiniTableGetEntry(NiniTable* table, const char* name);
void NiniTableSetValue(NiniTable *table, const char* name, NiniValue value);
void NiniDestroy(Nini *table);

char* ParseNiniTableName(char* token);
NiniTable ParseNiniTable(char* token);
NiniEntry ParseNiniEntry(char* token);
NiniValue ParseNiniValue(char* token);

NiniToken* NiniTokenize(const char* source);
Nini* NiniNew(NiniToken* tokens);
void NiniFree(Nini* nini);

#endif
