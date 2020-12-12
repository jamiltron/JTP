#ifndef JTP_TIMER_H
#define JTP_TIMER_H

typedef struct Timer {
  float deltaTime, lastTime;
} Timer;

void Timer_Update(Timer* timer);

#endif