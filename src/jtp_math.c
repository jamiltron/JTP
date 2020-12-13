#include "jtp_math.h"
#include <stdio.h>

Mat4x4 Ortho(double left, double right, double bottom, double top, double near, double far) {
  float x = (float)(right - left);
  float y = (float)(top - bottom);
  float z = (float)(far - near);

  Mat4x4 m = { 0 };
  m.x0 = 2.0f / x;
  m.y0 = 0;
  m.z0 = 0;
  m.w0 = 0;

  m.x1 = 0;
  m.y1 = 2.0f / y;
  m.z1 = 0;
  m.w1 = 0;

  m.x2 = 0;
  m.y2 = 0;
  m.z2 = -2.0f / z;
  m.w2 = 0;

  m.x3 = -(left + right) / x;
  m.y3 = -(top + bottom) / y;
  m.z3 = -(far + near) / z;
  m.w3 = 1.0f;

  return m;
}

Vec2 MultMat4x4ByVec2(Mat4x4 mat, Vec2 vec) {
  Vec4 vec4 = (Vec4) { .x = vec.x, .y = vec.y, .z = 0, .w = 0.0f};
  vec4 = MultMat4x4ByVec4(mat, vec4);
  return (Vec2) { .x = vec4.x, .y = vec4.y };
}

Vec3 MultMat4x4ByVec3(Mat4x4 mat, Vec3 vec) {
  Vec4 vec4 = (Vec4) { .x = vec.x, .y = vec.y, .z = vec.z, .w = 0.0f};
  vec4 = MultMat4x4ByVec4(mat, vec4);
  return (Vec3) { .x = vec4.x, .y = vec4.y, .z = vec4.z };
}

Vec4 MultMat4x4ByVec4(Mat4x4 mat, Vec4 vec) {
  Vec4 res = { 0 };

  res.x = mat.x0 * vec.x + mat.x1 * vec.y + mat.x2 * vec.z + mat.x3 * vec.w;
  res.y = mat.y0 * vec.x + mat.y1 * vec.y + mat.y2 * vec.z + mat.y3 * vec.w;
  res.z = mat.z0 * vec.x + mat.z1 * vec.y + mat.z2 * vec.z + mat.z3 * vec.w;
  res.w = mat.w0 * vec.x + mat.w1 * vec.y + mat.w2 * vec.z + mat.w3 * vec.w;

  return res;
}

Mat4x4 Mat4(float diagonal) {
  Mat4x4 mat = { 0 };
  mat.x0 = diagonal;
  mat.y1 = diagonal;
  mat.z2 = diagonal;
  mat.w3 = diagonal;

  return mat;
}

Mat4x4 MultMat4Mat4(Mat4x4 m0, Mat4x4 m1) {
  Mat4x4 res = { 0 };

  res.x0 = m0.x0 * m1.x0 + m0.x1 * m1.y0 + m0.x2 * m1.z0 + m0.x3 * m1.w0;
  res.x1 = (m0.x0 * m1.x1) + (m0.x1 * m1.y1) + (m0.x2 * m1.z1) + (m0.x3 * m1.w1);
  res.x2 = (m0.x0 * m1.x2) + (m0.x1 * m1.y2) + m0.x2 * m1.z2 + m0.x3 * m1.w2;
  res.x3 = (m0.x0 * m1.x3) + (m0.x1 * m1.y3) + m0.x2 * m1.z3 + m0.x3 * m1.w3;

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

Mat4x4 ScaleMat4x4(Mat4x4 mat, Vec4 vec) {
  return MultMat4Mat4(mat, GetScaleMatrix(vec));
}

Mat4x4 GetScaleMatrix(Vec4 vec) {
  Mat4x4 res = { 0 };
  res.x0 = vec.x;
  res.y1 = vec.y;
  res.z2 = vec.z;
  res.w3 = vec.w;
  return res;
}

void PrintMat4x4(Mat4x4 mat) {

}
