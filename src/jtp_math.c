#include "jtp_math.h"
#include <math.h>
#include <stdio.h>

Mat4 Ortho(double left, double right, double bottom, double top, double near, double far) {
  float x = (float)(right - left);
  float y = (float)(top - bottom);
  float z = (float)(far - near);

  Mat4 m = {
    m.x0 = 2.0f / x, m.x1 = 0, m.x2 = 0, m.x3 = -(left + right) / x,
    m.y0 = 0, m.y1 = 2.0f / y, m.y2 = 0, m.y3 = -(top + bottom) / y,
    m.z0 = 0, m.z1 = 0, m.z2 = -2.0f / z,   m.z3 = -(far + near) / z,
    m.w0 = 0, m.w1 = 0, m.w2 = 0, m.w3 = 1.0f
  };

  return m;
}

Vec2 Mat4Vec2Mult(Mat4 mat, Vec2 vec) {
  Vec4 vec4 = (Vec4) { .x = vec.x, .y = vec.y, .z = 0, .w = 0.0f};
  vec4 = Mat4Vec4Mult(mat, vec4);
  return (Vec2) { .x = vec4.x, .y = vec4.y };
}

Vec3 Mat4Vec3Mult(Mat4 mat, Vec3 vec) {
  Vec4 vec4 = (Vec4) { .x = vec.x, .y = vec.y, .z = vec.z, .w = 0.0f};
  vec4 = Mat4Vec4Mult(mat, vec4);
  return (Vec3) { .x = vec4.x, .y = vec4.y, .z = vec4.z };
}

Vec4 Mat4Vec4Mult(Mat4 mat, Vec4 vec) {
  Vec4 res = { 0 };

  res.x = mat.x0 * vec.x + mat.x1 * vec.y + mat.x2 * vec.z + mat.x3 * vec.w;
  res.y = mat.y0 * vec.x + mat.y1 * vec.y + mat.y2 * vec.z + mat.y3 * vec.w;
  res.z = mat.z0 * vec.x + mat.z1 * vec.y + mat.z2 * vec.z + mat.z3 * vec.w;
  res.w = mat.w0 * vec.x + mat.w1 * vec.y + mat.w2 * vec.z + mat.w3 * vec.w;

  return res;
}

Mat4 Mat4New(float diagonal) {
  Mat4 mat = { 0 };
  mat.x0 = diagonal;
  mat.y1 = diagonal;
  mat.z2 = diagonal;
  mat.w3 = diagonal;

  return mat;
}

Mat4 Mat4Mult(Mat4 m0, Mat4 m1) {
  Mat4 res = { 0 };

  res.x0 = m0.x0 * m1.x0 + m0.x1 * m1.y0 + m0.x2 * m1.z0 + m0.x3 * m1.w0;
  res.x1 = m0.x0 * m1.x1 + m0.x1 * m1.y1 + m0.x2 * m1.z1 + m0.x3 * m1.w1;
  res.x2 = m0.x0 * m1.x2 + m0.x1 * m1.y2 + m0.x2 * m1.z2 + m0.x3 * m1.w2;
  res.x3 = m0.x0 * m1.x3 + m0.x1 * m1.y3 + m0.x2 * m1.z3 + m0.x3 * m1.w3;

  res.y0 = m0.y0 * m1.x0 + m0.y1 * m1.y0 + m0.y2 * m1.z0 + m0.y3 * m1.w0;
  res.y1 = m0.y0 * m1.x1 + m0.y1 * m1.y1 + m0.y2 * m1.z1 + m0.y3 * m1.w1;
  res.y2 = m0.y0 * m1.x2 + m0.y1 * m1.y2 + m0.y2 * m1.z2 + m0.y3 * m1.w2;
  res.y3 = m0.y0 * m1.x3 + m0.y1 * m1.y3 + m0.y2 * m1.z3 + m0.y3 * m1.w3;

  res.z0 = m0.z0 * m1.x0 + m0.z1 * m1.y0 + m0.z2 * m1.z0 + m0.z3 * m1.w0;
  res.z1 = m0.z0 * m1.x1 + m0.z1 * m1.y1 + m0.z2 * m1.z1 + m0.z3 * m1.w1;
  res.z2 = m0.z0 * m1.x2 + m0.z1 * m1.y2 + m0.z2 * m1.z2 + m0.z3 * m1.w2;
  res.z3 = m0.z0 * m1.x3 + m0.z1 * m1.y3 + m0.z2 * m1.z3 + m0.z3 * m1.w3;

  res.w0 = m0.w0 * m1.x0 + m0.w1 * m1.y0 + m0.w2 * m1.z0 + m0.w3 * m1.w0;
  res.w1 = m0.w0 * m1.x1 + m0.w1 * m1.y1 + m0.w2 * m1.z1 + m0.w3 * m1.w1;
  res.w2 = m0.w0 * m1.x2 + m0.w1 * m1.y2 + m0.w2 * m1.z2 + m0.w3 * m1.w2;
  res.w3 = m0.w0 * m1.x3 + m0.w1 * m1.y3 + m0.w2 * m1.z3 + m0.w3 * m1.w3;

  return res;
}

Mat4 Mat4Scale(Mat4 mat, Vec4 vec) {
  return Mat4Mult(mat, Mat4ScaleMatrix(vec));
}

Mat4 Mat4ScaleMatrix(Vec4 vec) {
  Mat4 res = { 0 };
  res.x0 = vec.x;
  res.y1 = vec.y;
  res.z2 = vec.z;
  res.w3 = vec.w;
  return res;
}

Mat4 Mat4TranslationMatrix(Vec3 vec) {
  Mat4 res = {0};
  res.x3 = vec.x;
  res.y3 = vec.y;
  res.z3 = vec.z;
  res.w3 = 1.0f;
  return res;
}

Mat4 Mat4Translate(Mat4 mat, Vec3 vec) {
  Mat4 res = {
    mat.x0, mat.x1, mat.x2, vec.x,
    mat.y0, mat.y1, mat.y2, vec.y,
    mat.z0, mat.z1, mat.z2, vec.z,
    mat.w0, mat.w1, mat.w2, 1.0f,
  };
  return res;
}

Vec2 Vec2Normalize(Vec2 vec) {
  return Vec2Scale(vec, 1.0 / sqrt(Vec2Dot(vec, vec)));
}

Vec2 Vec2Scale(Vec2 vec, float scalar) {
  return (Vec2) {
    .x = vec.x * scalar,
    .y = vec.x * scalar,
  };
}

float Vec2Dot(Vec2 vec1, Vec2 vec2) {
  return vec1.x * vec2.x + vec1.y * vec2.y;
}

float Vec2Length(Vec2 vec) {
  return sqrt(Vec2Dot(vec, vec));
}

float Vec2Cross(Vec2 vec1, Vec2 vec2) {
  return vec1.x * vec2.y - vec1.y * vec2.x;
}

Vec2 Vec2Add(Vec2 vec1, Vec2 vec2) {
  return (Vec2) {
    .x = vec1.x + vec2.x,
    .y = vec1.y + vec2.y,
  };
}

Vec3 Vec3Normalize(Vec3 vec) {
  return Vec3Scale(vec, 1.0 / sqrt(Vec3Dot(vec, vec)));
}

Vec3 Vec3Scale(Vec3 vec3, float scalar) {
  return (Vec3) {
    .x = vec3.x * scalar,
    .y = vec3.y * scalar,
    .z = vec3.z * scalar
  };
}

float Vec3Dot(Vec3 vec1, Vec3 vec2) {
  return vec1.x * vec2.x + vec1.y + vec2.y * vec1.z + vec2.z;
}

float Vec3Length(Vec3 vec) {
  return sqrt(Vec3Dot(vec, vec));
}

Vec3 Vec3Cross(Vec3 vec1, Vec3 vec2) {
  return (Vec3) {
    .x = vec1.y * vec2.z - vec1.z * vec2.y,
    .y = vec1.z * vec2.z - vec1.x * vec2.z,
    .z = vec1.x * vec2.y - vec1.y * vec2.x,
  };
}

Vec3 Vec3Add(Vec3 vec1, Vec3 vec2) {
  return (Vec3) {
    .x = vec1.x + vec2.x,
    .y = vec1.y + vec2.y,
    .z = vec1.z + vec2.z,
  };
}

void PrintMat4x4(Mat4 mat) {}

void Vec2Print(Vec2* vec) {
  printf("(%f, %f)\n", vec->x, vec->y);
}
