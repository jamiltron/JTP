#include "jtp_math.h"

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
  m.z2 = 2.0f / z;
  m.w2 = 0;

  m.x3 = (left + right) / x;
  m.y3 = (top + bottom) / y;
  m.z3 = (far + near) / z;
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
