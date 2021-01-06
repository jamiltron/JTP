#include "jtp_sprite.h"
#include "jtp_math.h"
#include "jtp_shader.h"
#include <stdlib.h>

struct Sprite_Renderer {
  ShaderProgram *shader;
  uint vao;
  uint projectionUniform;
  uint modelUniform;
  uint spriteColorUniform;
  uint imageUniform;
};

Sprite_Renderer *Sprite_RendererNew(ShaderProgram *shader) {
  Sprite_Renderer *renderer = malloc(sizeof(Sprite_Renderer));
  renderer->shader = shader;
  renderer->projectionUniform = ShaderProgram_GetUniformLocation(renderer->shader, "projection");
  renderer->modelUniform = ShaderProgram_GetUniformLocation(renderer->shader, "model");
  renderer->spriteColorUniform = ShaderProgram_GetUniformLocation(renderer->shader, "spriteColor");
  renderer->imageUniform = ShaderProgram_GetUniformLocation(renderer->shader, "image");
  uint vbo;

  // TODO triangle strip this once it works
  float vertices[] = {
    // pos      //tex
    0.0f, 1.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 1.0f, 1.0f,
    1.0f, 0.0f, 1.0f, 0.0f
  };

  glGenVertexArrays(1, &renderer->vao);
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindVertexArray(renderer->vao);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*) 0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  return renderer;
}

void Sprite_RendererDelete(Sprite_Renderer *renderer) {
  free(renderer);
}

void Sprite_Draw(Sprite_Renderer *renderer, Texture2D *texture, Vec2 position, Vec2 size, float rotation, Color color) {
  ShaderProgram_Use(renderer->shader);
  Mat4 model = Mat4New(1.0f);

  model = Mat4Translate(model, (Vec3) {.x = 0.5f * size.x, .y = 0.5f * size.y, .z = 0.0f});

  // TODO: write rotation
}
