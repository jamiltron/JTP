#include "jtp_assets.h"
#include "jtp_shapes2d.h"
#include "jtp_assets.h"
#include "jtp_shader_program.h"
#include <glad/glad.h>

/* This currently doesn't do what it says, I'm just getting something on screen. */
void DrawTriangle(Vec2 p1, Vec2 p2, Vec2 p3, Color color) {
  /* TODO: don't do this */
  float x1 = (2.0 / (800 - 0)) * p1.x;
  float y1 = (2.0 / (600 - 0)) * p1.y;

  float x2 = (2.0 / (800 - 0)) * p2.x;
  float y2 = (2.0 / (600 - 0)) * p2.y;

  float x3 = (2.0 / (800 - 0)) * p3.x;
  float y3 = (2.0 / (600 - 0)) * p3.y;

  float vertices[] = {
    // position
    x1, y1,
    x2, y2,
    x3, y3
  };

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
  glBindVertexArray(0);
}
