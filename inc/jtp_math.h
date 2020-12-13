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

typedef struct Mat4x4 {
  float x0, x1, x2, x3;
  float y0, y1, y2, y3;
  float z0, z1, z2, z3;
  float w0, w1, w2, w3;
} Mat4x4;

Mat4x4 Ortho(double left, double right, double bottom, double top, double near,
             double far);
Mat4x4 Mat4(float);
const float* Mat4Cols(Mat4x4 mat);

Vec2 MultMat4x4ByVec2(Mat4x4 mat, Vec2 vec);
Vec3 MultMat4x4ByVec3(Mat4x4 mat, Vec3 vec);
Vec4 MultMat4x4ByVec4(Mat4x4 mat, Vec4 vec);
Mat4x4 MultMat4Mat4(Mat4x4 m0, Mat4x4 m1);
Mat4x4 ScaleMat4x4(Mat4x4 mat, Vec4 vec);
Mat4x4 GetScaleMatrix(Vec4 vec);

#endif
