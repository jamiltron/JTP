#include "jtp_assets.h"
#include "jtp_game.h"
#include "jtp_math.h"
#include "jtp_shader_program.h"
#include "jtp_shapes2d.h"
#include <glad/glad.h>
#include <stdio.h>
#include <stdlib.h>

static void _InitRectRenderer(void);

struct Shapes2D_Renderer {
  ShaderProgram *shaderProgram;
  uint projectionUniform;
  uint modelUniform;
  uint colorUniform;
  uint rectVao;
};

Shapes2D_Renderer* Shapes2D_RendererNew(ShaderProgram *shaderProgram) {
  Shapes2D_Renderer *renderer = malloc(sizeof(Shapes2D_Renderer));
  renderer->shaderProgram = shaderProgram;
  renderer->projectionUniform = ShaderGetUniformLocation(renderer->shaderProgram, "projection");
  renderer->modelUniform = ShaderGetUniformLocation(renderer->shaderProgram, "model");
  renderer->colorUniform = ShaderGetUniformLocation(renderer->shaderProgram, "color");

  Mat4 projection = WindowProjection();

  float vertices[] = {
    -1.0f, -1.0f, // bottom left
    -1.0f,  1.0f, // top left
    1.0f, -1.0f,  // bottom right
    1.0f,  1.0f,  // top right
  };

  uint vbo;
  glGenVertexArrays(1, &(renderer->rectVao));
  glGenBuffers(1, &vbo);
  glBindVertexArray(renderer->rectVao);

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  ShaderSetMatrix4(renderer->shaderProgram, renderer->projectionUniform, &projection, true);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
  return renderer;
}

void Shapes2D_DrawTriangle(Shapes2D_Renderer *renderer, Vec2 p1, Vec2 p2, Vec2 p3, Color color) {
  Mat4x4 projection = WindowProjection();
  Size windowSize = WindowSize();

  float vertices[] = {
    p1.x, p1.y,
    p2.x, p2.y,
    p3.x, p3.y
  };

  /* TODO think about how we can cache these */
  uint vbo, vao;
  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo);

  glBindVertexArray(vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);

  /* TODO don't do this */
  ShaderProgram* def = GetShader("default");
  if (def != NULL) {
    glUseProgram(def->id);
    Mat4 model = Mat4New(1.0f);
    ShaderSetMatrix4(def, renderer->projectionUniform, &projection, false);
    ShaderSetMatrix4(def, renderer->modelUniform, &model, false);
    ShaderSetColor4f(def, renderer->colorUniform, &color, false);
    glDrawArrays(GL_TRIANGLES, 0, 3);
  }

  glBindVertexArray(0);
}

void Shapes2D_DrawRectangle(Shapes2D_Renderer *renderer, Rect rect, Color color) {
  glBindVertexArray(renderer->rectVao);
  Mat4 model = Mat4New(1.0f);
  model = Mat4Translate(model, (Vec3) {.x = rect.x, .y = rect.y, .z = 0});
  model = Mat4Scale(model, (Vec4) { .x = rect.width, .y = rect.height, .z = 1.0, .w = 1});
  ShaderSetMatrix4(renderer->shaderProgram, renderer->modelUniform, &model, true);
  ShaderSetColor4f(renderer->shaderProgram, renderer->colorUniform, &color, false);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}
