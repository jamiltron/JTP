#include <stdio.h>
#include "jtp_game.h"
#include "jtp_math.h"
#include "jtp_shapes2d.h"

int main() {
  WindowInit(800, 600, "JTP");

  while(!WindowShouldClose()) {
    ProcessInput();
    float dt = GetTime();

    BeginDrawing();
    WindowClear((Color)
                { .r = 0.91f, .g = 0.45f, .b = 0.32f, .a = 1.0f });
       DrawTriangle((Vec2){ .x = 0, .y = 150},
                 (Vec2){ .x = -200, .y = -150},
                 (Vec2) { .x = 200, .y = -150},
                 (Color) { .r = 0.0f, .g = 0.0f, .b = 1.0f, .a = 1.0f});
      /*   DrawRectangle((Rect) { .x = 0, .y = 0, .width = 200, .height = 200}, */
      /* (Color){ .r = 0.0f, .g = 0.0f, .b = 1.0f, .a = 1.0f}); */
    EndDrawing();
  }

  WindowClose();
  return 0;
}
