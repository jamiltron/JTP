#include "jtp_assets.h"
#include "jtp_shapes2d.h"
#include "jtp_assets.h"
#include "jtp_shader_program.h"
#include <glad/glad.h>

/* This currently doesn't do what it says, I'm just getting something on screen. */
void DrawTriangle(Vec2 p1, Vec2 p2, Vec2 p3, Color color) {
  float vertices[] = {
    // position
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.0f, 0.5f, 0.0f
  };

  uint vbo, vao;
  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo);

  glBindVertexArray(vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);

  /* TODO don't do this */
  glUseProgram(GetShader("default")->id);
  glDrawArrays(GL_TRIANGLES, 0, 3);

  glBindVertexArray(0);
  glBindVertexArray(0);
}
