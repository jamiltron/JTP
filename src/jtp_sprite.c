#include "jtp_sprite.h"
#include <stdlib.h>

struct Sprite_Renderer {
  ShaderProgram *shader;
  uint vao;
};

Sprite_Renderer *Sprite_RendererNew(ShaderProgram *shader) {
  Sprite_Renderer *renderer = malloc(sizeof(Sprite_Renderer));

  // TODO: all the stuff

  return renderer;
}

void Sprite_RendererDelete(Sprite_Renderer *renderer) {
  free(renderer);
}

void Sprite_Draw(Sprite_Renderer *renderer, Texture2D *texture, Vec2 position, Vec2 size, float rotation, Color color) {

}
