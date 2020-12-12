#include <stdio.h>
#include "game.h"
#include "types.h"

int main() {
  WindowInit(800, 600, "JTP");

  while(!WindowShouldClose()) {
    ProcessInput();
    float dt = GetTime();

    BeginDrawing();
    WindowClear((Color) { .r = 0.91f, .g = 0.45f, .b = 0.32f, .a = 1.0f });
    EndDrawing();
  }

  WindowClose();
  return 0;
}