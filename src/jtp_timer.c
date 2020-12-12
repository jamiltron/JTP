#include "jtp_timer.h"
#include <GLFW/glfw3.h>

void TimerUpdate(Timer* timer) {
  float currentTime = glfwGetTime();
  timer->deltaTime = timer->lastTime - currentTime;
  timer->lastTime = currentTime;
}