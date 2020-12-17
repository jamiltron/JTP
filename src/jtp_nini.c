#include "jtp_assets.h"
#include "jtp_nini.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

NiniToken* NiniTokenize(const char* source) {
  NiniToken tokens[1024];
  int count = 0;

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
      tokens[count++] = (NiniToken) { .type = NiniTableToken, .value = name };
      head = lookahead + 1;
    }

    if (isalnum((unsigned char) *head)) {
      lookahead = head;

      while (isalnum((unsigned char) *lookahead)) {
        lookahead++;
      }

      int diff = lookahead - head;
      char* name = malloc(sizeof(char) * (diff + 1));
      strncpy(name, head, diff);
      name[diff] = '\0';
      tokens[count++] = (NiniToken) { .type = NiniIdentifierToken, .value = name };
      head = lookahead-1;
    }

    if (*head == '=') {
      tokens[count++] = (NiniToken) {.type = NiniEqualsToken, .value = NULL };
    }

    head++;
  }

  NiniToken* result = malloc(sizeof(NiniToken) * (count + 1));
    for (int i = 0; i < count; ++i) {
    result[i] = tokens[i];
  }
  result[count] = (NiniToken) { .type = NiniEndToken, .value = NULL };

  return result;
}

Nini* NiniNew(NiniToken* tokens) {
  // count number of tables
  uint numTables = 0;
  for (NiniToken* t = tokens; t->type != NiniEndToken; ++t) {
    if (t->type == NiniTableToken) {
      ++numTables;
    }
  }

  Nini* nini = malloc(sizeof(Nini));

  nini->name = "TODO: pass this in";
  nini->count = numTables;
  nini->tables = malloc(sizeof(NiniTable*) * numTables);
  NiniToken* tablePtr = tokens;
  for (uint i = 0; i < numTables; ++i) {
    NiniToken test = *tablePtr;

    // find each table and get their entries
    while (tablePtr->type != NiniTableToken) {
      ++tablePtr;
    }
    char* tableName = (*tablePtr).value;

    // count the number of entries
    uint numEntries = 0;
    NiniToken* entriesPtr = tablePtr+1;
    while (entriesPtr && entriesPtr->type != NiniEndToken && entriesPtr->type != NiniTableToken) {
      // todo we should do some better error checking/debugging
      if (entriesPtr->type == NiniIdentifierToken) {
        // double check that the entry is indeed well-formed, otherwise throw a tantrum
        if ((entriesPtr+1)->type == NiniEqualsToken && (entriesPtr+2)->type == NiniIdentifierToken) {
          numEntries += 1;
          entriesPtr += 3;
          continue;
        } else {
          printf("Error reading Nini file (TODO: pass in file name so we have context\n");
          exit(1);
        }
      } else {
        ++entriesPtr;
      }
      ++entriesPtr;
    }

    NiniTable *table = malloc(sizeof(NiniTable));
    table->name = tableName;
    table->count = numEntries;
    table->entries = malloc(sizeof(NiniEntry*) * numEntries);

    entriesPtr = tablePtr+1;
    for (uint j = 0; j < numEntries; j++) {
      char* key = entriesPtr[j*3].value;
      char* strVal = entriesPtr[j*3+2].value;
      printf("key: %s, val: %s\n", key, strVal);

      NiniValue *value = malloc(sizeof(NiniValue));

      if (StringIsInteger(strVal)) {
        value->value.integer = atoi(strVal);
        value->entryType = Integer;
      } else if (strcmp(strVal, "true") == 0) {
        value->value.boolean = true;
        value->entryType = Bool;
      } else if (strcmp(strVal, "false") == 0) {
        value->value.boolean = false;
        value->entryType = Bool;
      } else {
        value->value.string = strVal;
        value->entryType = String;
      }

      NiniEntry *entry = malloc(sizeof(NiniEntry));
      entry->key = key;
      entry->value = value;
      table->entries[j] = entry;
    }

    // set the table
    nini->tables[i] = table;
  }

  return nini;
}

void NiniFree(Nini* nini) {
  for (int i = 0; i < nini->count; ++i) {
    NiniTable* table = nini->tables[i];
    for (int j = 0; j < table->count; ++j) {
      NiniEntry *entry = table->entries[j];
      free(entry->value);
      free(entry);
    }
    free(table);
  }
  free(nini);
}

