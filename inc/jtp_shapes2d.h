#ifndef JTP_SHAPES2D
#define JTP_SHAPES2D
#include "jtp_math.h"
#include "jtp_shader_program.h"

typedef struct Shapes2D_Renderer Shapes2D_Renderer;

// TODO: batch
Shapes2D_Renderer* Shapes2D_RendererNew(ShaderProgram *shaderProgram);
void Shapes2D_DrawTriangle(Shapes2D_Renderer *renderer, Vec2 p1, Vec2 p2, Vec2 p3, Color color);
void Shapes2D_DrawRectangle(Shapes2D_Renderer *renderer, Rect rect, Color color);

#endif
