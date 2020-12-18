#include <stdio.h>
#include "jtp_assets.h"
#include "jtp_game.h"
#include "jtp_math.h"
#include "jtp_nini.h"
#include "jtp_shapes2d.h"
#include "jtp_string.h"

int main() {
  /*WindowInit(800, 600, "JTP");

  while(!WindowShouldClose()) {
    ProcessInput();
    float dt = GetTime();

    BeginDrawing();
    WindowClear((Color)
                { .r = 0.91f, .g = 0.45f, .b = 0.32f, .a = 1.0f });
      DrawRectangle(
        (Rect) { .x = 400, .y = 300, .width = 64, .height = 64},
        (Color){ .r = 0.0f, .g = 0.0f, .b = 1.0f, .a = 1.0f});
    EndDrawing();
  }

  WindowClose();*/
  //NiniReadFile("test.nini", "test");
  /* NiniEntry entry = ParseNiniEntry("size=212");
  printf("key: %s, ", entry.key);
  if (entry.value.entryType == Integer) {
    printf(" value: %i\n", entry.value.value.integer);
  } else if (entry.value.entryType == String) {
    printf(" value: %s\n", entry.value.value.string);
  } else {
    printf(" value: None\n");
  }*/

  const char *source = ReadFile("test.nini");
  NiniToken* tokens = NiniTokenize(source);
  /* free(source);

  int i = 0;
  while (tokens[i].type != NiniEndToken) {
    NiniToken token = tokens[i];
    if (token.type == NiniTableToken) {
      printf("[%s]\n", token.value);
    } else if (token.type == NiniIdentifierToken) {
      printf("(%s)\n", token.value);
    } else if (token.type == NiniEqualsToken) {
      printf("=\n");
    }
    if (token.value) {
      free(token.value);
    }
    ++i;
  } */

  Nini* nini = NiniNew(tokens, "test");
  printf("\n\n******\n");
  printf("nini.name: %s, table.count: %i\n", nini->name, nini->count);
  for (uint t = 0; t < nini->count; ++t) {
    NiniTable* table = nini->tables[t];
    printf("table.name: %s, entries.count: %i\n", table->name, table->count);

    for (uint e = 0; e < table->count; ++e) {
      NiniEntry* entry = table->entries[e];
      printf("entry.name: %s, ", entry->key);
      if (entry->value.entryType == Integer) {
        printf("entry.value.value %i\n", entry->value.value.integer);
      }
    }
  }
  printf("******\n");
  free(tokens);
  NiniFree(nini);

  return 0;
}
