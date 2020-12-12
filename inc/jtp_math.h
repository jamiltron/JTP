#ifndef JTP_MATH_H
#define JTP_MATH_H

typedef unsigned uint;

typedef struct Color {
  float r, g, b, a;
} Color;

typedef struct Vec2 {
  float x, y;
} Vec2;

typedef struct Size {
    float width, height;
} Size;

typedef struct Vec3 {
  float x, y, z;
} Vec3;

typedef struct Vec4 {
    float x, y, z, w;
} Vec4;

typedef struct Rect {
  float x, y, width, height;
} Rect;


#endif
