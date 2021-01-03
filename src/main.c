#include <stdio.h>
#include "jtp_game.h"

int main() {
  WindowInit(800, 600, "JTP");

  while(!WindowShouldClose()) {
    ProcessInput();
    float dt = GetTime();

    BeginDrawing();
    WindowClear((Color)
                { .r = 0.91f, .g = 0.45f, .b = 0.32f, .a = 1.0f });
    DrawRectangle((Rect){.x = 100, .y = 100, .width = 100, .height = 100}, (Color){1.0f, 1.0f, 1.0f, 1.0f});
    DrawTriangle((Vec2){400.0f, 200.f}, (Vec2){200, 400}, (Vec2){600, 400}, (Color){0.0f, 0.0f, 0.0f, 1.0f});
    EndDrawing();
  }

  WindowClose();
  return 0;
}
