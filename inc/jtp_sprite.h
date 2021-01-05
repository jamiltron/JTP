#ifndef JTP_SPRITE_H
#define JTP_SPRITE_H
#include "jtp_math.h"
#include "jtp_shader.h"
#include "jtp_texture2d.h"

typedef struct Sprite_Renderer Sprite_Renderer;

Sprite_Renderer *Sprite_RendererNew(ShaderProgram *shader);
void Sprite_RendererDelete(Sprite_Renderer *renderer);

void Sprite_Draw(Sprite_Renderer *renderer, Texture2D *texture, Vec2 position, Vec2 size, float rotation, Color color);

#endif
