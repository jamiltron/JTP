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

void Shapes_DrawTriangle(Vec2 p1, Vec2 p2, Vec2 p3, Color color) {
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

typedef struct RectRenderer {
  bool init;
  ShaderProgram* shaderProgram;
  uint vao;
} RectRenderer;

/* TODO: think about having this live on game, we should "know" about game end somewhere */
static RectRenderer _rectRenderer = { 0 };

void Shapes_DrawRectangle(Rect rect, Color color) {
  _InitRectRenderer();
  glBindVertexArray(_rectRenderer.vao);
  Mat4 model = Mat4New(1.0f);
  model = Mat4Translate(model, (Vec3) {.x = rect.x, .y = rect.y, .z = 0});
  model = Mat4Scale(model, (Vec4) { .x = rect.width, .y = rect.height, .z = 1.0, .w = 1});
  ShaderSetMatrix4(_rectRenderer.shaderProgram, "model", &model, true);
  ShaderSetColor4f(_rectRenderer.shaderProgram, "color", &color, false);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

/* TODO think about future shader support */
void _InitRectRenderer() {
  if (_rectRenderer.init) return;
  Mat4 ortho = WindowProjection();
  _rectRenderer.shaderProgram = GetShader("default");

  float vertices[] = {
    -1.0f, -1.0f, // bottom left
    -1.0f,  1.0f, // top left
    1.0f, -1.0f,  // bottom right
    1.0f,  1.0f,  // top right
  };

  uint vbo;
  glGenVertexArrays(1, &_rectRenderer.vao);
  glGenBuffers(1, &vbo);
  glBindVertexArray(_rectRenderer.vao);

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  ShaderSetMatrix4(_rectRenderer.shaderProgram, "projection", &ortho, true);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
  _rectRenderer.init = true;
}
