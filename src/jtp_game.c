#include "jtp_game.h"
#include "jtp_assets.h"
#include "jtp_shader_program.h"
#include "jtp_timer.h"
#include <GL/gl.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  GLFWwindow* window;
  Timer timer;
  ShaderProgram* defaultShader;
  Mat4x4 ortho;
} _Game;

static void _FramebufferSizeCallback(GLFWwindow* window, int width, int height);
static void _ProcessInput(GLFWwindow* window);

static _Game game;

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
  //glViewport(0, 0, 800, 600);
  //glViewport(0, 0, 800, 600);
  glfwMakeContextCurrent(game.window);
  glfwSetFramebufferSizeCallback(game.window, _FramebufferSizeCallback);
  if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
    printf("Failed to initialize GLAD\n");
    exit(1);
  }

  glViewport(0, 0, 800, 600);

  /* TODO don't do this */
  game.defaultShader = LoadShader("default", "../res/shaders/default.vert", "../res/shaders/default.frag");
  game.ortho = Ortho(0.0, 800.0, 600.0, 0.0, -1.0, 1.0);
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

void WindowClose() { glfwTerminate(); }

Size WindowSize() {
  int width, height;
  glfwGetWindowSize(game.window, &width, &height);
  return (Size) { .width = width, .height = height };
}

Mat4x4 WindowOrtho() {
  return game.ortho;
}

void _FramebufferSizeCallback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, 800, 600);
}

void _ProcessInput(GLFWwindow* window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, 1);
  }
}
