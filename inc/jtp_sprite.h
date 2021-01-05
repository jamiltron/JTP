#ifndef JTP_SPRITES_H
#define JTP_SPRITES_H
#include "jtp_math.h"
#include "jtp_shader.h"
#include "jtp_texture2d.h"

typedef struct Sprites_Renderer Sprites_Renderer;

Sprites_Renderer *Sprites_RendererNew(ShaderProgram *shaderProgram);
Sprites_Renderer Sprites_RendererDelete(Sprites_Renderer *renderer);

void Sprites_Draw(Sprites_Renderer *renderer, Texture2D *texture, Vec2 position, Vec2 size, float rotation, Color color);

#endif
