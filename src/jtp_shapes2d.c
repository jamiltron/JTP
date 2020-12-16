#include "jtp_assets.h"
#include "jtp_game.h"
#include "jtp_math.h"
#include "jtp_shapes2d.h"
#include "jtp_assets.h"
#include "jtp_shader_program.h"
#include <GL/gl.h>
#include <glad/glad.h>
#include <stdio.h>

static void _InitRectRenderer(void);

/* This currently doesn't do what it says, I'm just getting something on screen. */
void DrawTriangle(Vec2 p1, Vec2 p2, Vec2 p3, Color color) {
  /* TODO: don't do this? */
  /* Mat4x4 ortho = WindowOrtho();
  Vec2 t1 = MultMat4x4ByVec2(ortho, p1);
  Vec2 t2 = MultMat4x4ByVec2(ortho, p2);
  Vec2 t3 = MultMat4x4ByVec2(ortho, p3);

  float vertices[] = {
    t1.x, t1.y,
    t2.x, t2.y,
    t3.x, t3.y
  };


  //Mat4x4 model = Mat4(1.0f);

  /* TODO think about how we can cache these */
  /* uint vbo, vao;
  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo);

  glBindVertexArray(vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0); */

  /* TODO don't do this */
 /*  ShaderProgram* def = GetShader("default");
  if (def != NULL) {
    //model = ScaleMat4x4(model, (Vec4) { 10.0f, 10.0f, 1.0f, 1.0f});
    Mat4x4 model = {
      .x0 = 100.0f, .x1 = 0,      .x2 = 0,    .x3 = 400.0f,
      .y0 = 0,      .y1 = 100.0f, .y2 = 0,    .y3 = 300.0f,
      .z0 = 0,      .z1 = 0,      .z2 = 1.0f, .z3= 0,
      .w0 = 0,      .w1 = 0,      .w2 = 0,    .w3 = 1.0f
    };
    glUseProgram(def->id);
    ShaderSetMatrix4(def, "projection", &ortho, false);
    ShaderSetMatrix4(def, "model", &model, false);
    ShaderSetVector4f(def, "color", &color, false);
    glDrawArrays(GL_TRIANGLES, 0, 6);
  }

  glBindVertexArray(0); */
}

typedef struct RectRenderer {
  bool init;
  ShaderProgram* shaderProgram;
  uint vao;
} RectRenderer;

/* TODO: think about having this live on game, we should "know" about game end somewhere */
static RectRenderer _rectRenderer = { 0 };

void DrawRectangle(Rect rect, Color color) {
  _InitRectRenderer();
  glBindVertexArray(_rectRenderer.vao);
  Mat4 model = Mat4New(1.0f);
  model = TranslateMat4x4(model, (Vec3) {.x = rect.x, .y = rect.y, .z = 0});
  model = ScaleMat4x4(model, (Vec4) { .x = rect.width, .y = rect.height, .z = 1.0, .w = 1});
  ShaderSetMatrix4(_rectRenderer.shaderProgram, "model", &model, true);
  ShaderSetVector4f(_rectRenderer.shaderProgram, "color", &color, false);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

/* TODO think about future shader support */
void _InitRectRenderer() {
  if (_rectRenderer.init) return;
  Mat4 ortho = WindowOrtho();
  _rectRenderer.shaderProgram = GetShader("default");

  float vertices[] = {
    1.0f,  1.0f,  // top right
    1.0f, -1.0f,  // bottom right
    -1.0f, -1.0f, // bottom left
    -1.0f,  1.0f, // top left
  };

  unsigned int indices[] = {
    0, 1, 3,
    1, 2, 3
  };

  uint vbo, ebo;
  glGenVertexArrays(1, &_rectRenderer.vao);
  glGenBuffers(1, &vbo);
  glGenBuffers(1, &ebo);
  glBindVertexArray(_rectRenderer.vao);

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  ShaderSetMatrix4(_rectRenderer.shaderProgram, "projection", &ortho, true);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
  _rectRenderer.init = true;
}
