#ifndef JTP_NINI_H
#define JTP_NINI_H

typedef enum NiniTokenType {
  NiniTableToken,
  NiniIdentifierToken,
  NiniEqualsToken
} NiniTokenType;

typedef struct NiniToken {
  NiniTokenType type;
  const char* value;
} NiniToken;

typedef enum NiniEntryType {
  None,
  Integer,
  String
} NiniEntryType;

typedef struct NiniValue {
  NiniEntryType entryType;
  union {
    int integer;
    char* string;
  } value;
} NiniValue;

typedef struct NiniEntry {
  char* key;
  NiniValue value;
} NiniEntry;

typedef struct NiniTable {
  const char* name;
  NiniEntry entries;
  uint count;
} NiniTable;

typedef struct Nini {
  const char* name;
  NiniTable* tables;
  uint count;
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

NiniToken* NiniTokenize(const char* source, int* count);

#endif