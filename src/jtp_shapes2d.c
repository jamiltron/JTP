#include "jtp_assets.h"
#include "jtp_game.h"
#include "jtp_math.h"
#include "jtp_shapes2d.h"
#include "jtp_assets.h"
#include "jtp_shader_program.h"
#include <GL/gl.h>
#include <glad/glad.h>

/* This currently doesn't do what it says, I'm just getting something on screen. */
void DrawTriangle(Vec2 p1, Vec2 p2, Vec2 p3, Color color) {
  /* TODO: don't do this? */
  Mat4x4 ortho = WindowOrtho();
  Vec2 t1 = MultMat4x4ByVec2(ortho, p1);
  Vec2 t2 = MultMat4x4ByVec2(ortho, p2);
  Vec2 t3 = MultMat4x4ByVec2(ortho, p3);

  float vertices[] = {
    t1.x, t1.y,
    t2.x, t2.y,
    t3.x, t3.y
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
    ShaderSetVector4f(def, "color", &color, true);
    glDrawArrays(GL_TRIANGLES, 0, 3);
  }

  glBindVertexArray(0);
}

void DrawRectangle(Rect rect, Color color) {
  float left = rect.x - rect.width / 2.0f;
  float bottom = rect.y - rect.height  / 2.0f;
  float right = rect.x + rect.width / 2.0f;
  float top = rect.y + rect.height / 2.0f;

  Mat4x4 ortho = WindowOrtho();

  Vec2 t1 = MultMat4x4ByVec2(ortho, (Vec2) { .x = right, .y = top });
  Vec2 t2 = MultMat4x4ByVec2(ortho, (Vec2) { .x = left, .y = top });
  Vec2 t3 = MultMat4x4ByVec2(ortho, (Vec2) { .x = left, .y = bottom });
  Vec2 t4 = MultMat4x4ByVec2(ortho, (Vec2) { .x = right, .y = bottom });

  float vertices[] = {
    t1.x,  t1.y,  // top right
    t4.x, t4.y,   // bottom right
    t3.x, t3.y,   // bottom left
    t2.x,  t2.y,  // top left
  };

  unsigned int indices[] = {
    0, 1, 3,
    1, 2, 3
  };

  unsigned int vbo, vao, ebo;
  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo);
  glGenBuffers(1, &ebo);
  glBindVertexArray(vao);

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  ShaderProgram* def = GetShader("default");
  if (def != NULL) {
    ShaderSetVector4f(def, "color", &color, true);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  }

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}
