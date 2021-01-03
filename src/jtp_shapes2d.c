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
  uint vao;
};

Shapes2D_Renderer* Shapes2D_RendererNew(ShaderProgram *shaderProgram) {
  Shapes2D_Renderer *renderer = malloc(sizeof(Shapes2D_Renderer));
  renderer->shaderProgram = shaderProgram;
  Mat4 ortho = WindowProjection();

  float vertices[] = {
    -1.0f, -1.0f, // bottom left
    -1.0f,  1.0f, // top left
    1.0f, -1.0f,  // bottom right
    1.0f,  1.0f,  // top right
  };

  uint vbo;
  glGenVertexArrays(1, &(renderer->vao));
  glGenBuffers(1, &vbo);
  glBindVertexArray(renderer->vao);

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  ShaderSetMatrix4(renderer->shaderProgram, "projection", &ortho, true);

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
    ShaderSetMatrix4(def, "projection", &projection, false);
    ShaderSetMatrix4(def, "model", &model, false);
    ShaderSetColor4f(def, "color", &color, false);
    glDrawArrays(GL_TRIANGLES, 0, 3);
  }

  glBindVertexArray(0);
}

void Shapes2D_DrawRectangle(Shapes2D_Renderer *renderer, Rect rect, Color color) {
  glBindVertexArray(renderer->vao);
  Mat4 model = Mat4New(1.0f);
  model = Mat4Translate(model, (Vec3) {.x = rect.x, .y = rect.y, .z = 0});
  model = Mat4Scale(model, (Vec4) { .x = rect.width, .y = rect.height, .z = 1.0, .w = 1});
  ShaderSetMatrix4(renderer->shaderProgram, "model", &model, true);
  ShaderSetColor4f(renderer->shaderProgram, "color", &color, false);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}
