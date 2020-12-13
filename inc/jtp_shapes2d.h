#ifndef JTP_SHAPES2D
#define JTP_SHAPES2D
#include "jtp_math.h"

/* Currently not batched */
void DrawTriangle(Vec2 p1, Vec2 p2, Vec2 p3, Color color);

/* Currently not batched */
void DrawRectangle(Rect rect, Color color);

void DrawQuad(Vec2 pos, Size size, Color color);

#endif
