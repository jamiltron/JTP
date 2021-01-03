#ifndef JTP_SHAPES2D
#define JTP_SHAPES2D
#include "jtp_math.h"

// TODO: batch
void Shapes_DrawTriangle(Vec2 p1, Vec2 p2, Vec2 p3, Color color);
void Shapes_DrawRectangle(Rect rect, Color color);
void Shapes_DrawQuad(Vec2 pos, Size size, Color color);

#endif
