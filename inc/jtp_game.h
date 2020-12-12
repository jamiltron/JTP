#ifndef JTP_GAME_H
#define JTP_GAME_H
#include "jtp_types.h"
#include <stdbool.h>

void WindowInit(uint width, uint height, const char* title);
void WindowClose(void);
bool WindowShouldClose(void);
void ProcessInput(void);
void BeginDrawing(void);
void EndDrawing(void);
float GetTime(void);
#endif