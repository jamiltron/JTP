#ifndef JTP_GAME_H
#define JTP_GAME_H
#include "jtp_math.h"
#include <stdbool.h>

void WindowInit(uint width, uint height, const char *title);
void WindowClear(Color color);
void WindowClose(void);
bool WindowShouldClose(void);
void ProcessInput(void);
void BeginDrawing(void);
void EndDrawing(void);
float GetTime(void);
Size WindowSize(void);
Mat4 WindowProjection(void);

// Primitives
void DrawTriangle(Vec2 p1, Vec2 p2, Vec2 p3, Color color);
void DrawRectangle(Rect rect, Color color);

#endif
