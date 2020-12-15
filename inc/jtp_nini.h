#ifndef JTP_NINI_H
#define JTP_NINI_H

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
  NiniEntry* entries;
} NiniTable;

typedef struct Nini {
  const char* name;
  NiniTable* tables;
} Nini;


Nini* NiniReadFile(const char* path, const char* name);
NiniTable* NiniGetTable(Nini* nini, const char* name);
NiniEntry* NiniGetEntry(Nini* nini, const char* tableName, const char* entryName);
NiniEntry* NiniTableGetEntry(NiniTable* table, const char* name);
void NiniTableSetValue(NiniTable *table, const char* name, NiniValue value);
void NiniDestroy(Nini *table);

char* ParseNiniTableName(char* token);
NiniEntry ParseNiniEntry(char* token);
NiniValue ParseNiniValue(char* token);

#endif