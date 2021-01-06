#include "jtp_game.h"
#include "jtp_assets.h"
#include "jtp_shader.h"
#include "jtp_shapes2d.h"
#include "jtp_timer.h"
#include <GL/gl.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Game {
  GLFWwindow *window;
  Assets *assets;
  Timer timer;
  ShaderProgram *defaultShader;
  Mat4 projection;
  Shapes2D_Renderer *rendererShapes2D;
} Game;

static void _FramebufferSizeCallback(GLFWwindow* window, int width, int height);
static void _ProcessInput(GLFWwindow* window);

static Game game;

void WindowInit(uint width, uint height, const char* title) {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
  game.timer = (Timer) { .deltaTime = 0.0f, .lastTime = 0.0f };
  game.window = glfwCreateWindow(width, height, title, NULL, NULL);
  if (game.window == NULL) {
    printf("Failed to create GLFW window\n");
    glfwTerminate();
    exit(1);
  }
  glfwMakeContextCurrent(game.window);
  glfwSetFramebufferSizeCallback(game.window, _FramebufferSizeCallback);
  if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
    printf("Failed to initialize GLAD\n");
    exit(1);
  }

  glViewport(0, 0, 800, 600);

  game.assets = Assets_New();
  game.defaultShader = Assets_LoadShader(game.assets, "primitive", "primitive.vs", "primitive.fs");
  game.projection = Ortho(0.0, 800.0, 600.0, 0.0, -1.0, 1.0);
  game.rendererShapes2D = Shapes2D_RendererNew(game.defaultShader);
}

bool WindowShouldClose() {
  return glfwWindowShouldClose(game.window);
}

void WindowClear(Color color) {
  glClearColor(color.r, color.g, color.b, color.a);
  glClear(GL_COLOR_BUFFER_BIT);
}

void BeginDrawing() {}

void EndDrawing() {
  glfwSwapBuffers(game.window);
}

void ProcessInput() {
  glfwPollEvents();
  _ProcessInput(game.window);
}

float GetTime(void) {
  TimerUpdate(&game.timer);
  return game.timer.deltaTime;
}

void WindowClose() {
  Assets_Clear(game.assets);
  Shapes2D_RendererDelete(game.rendererShapes2D);
  glfwTerminate();
}

Size WindowSize() {
  int width, height;
  glfwGetWindowSize(game.window, &width, &height);
  return (Size) { .width = width, .height = height };
}

Mat4 WindowProjection() {
  return game.projection;
}

void DrawTriangle(Vec2 p1, Vec2 p2, Vec2 p3, Color color) {
  Shapes2D_DrawTriangle(game.rendererShapes2D, p1, p2, p3, color);
}

void DrawRectangle(Rect rect, Color color) {
  Shapes2D_DrawRectangle(game.rendererShapes2D, rect, color);
}

void _FramebufferSizeCallback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}

void _ProcessInput(GLFWwindow* window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, 1);
  }
}
