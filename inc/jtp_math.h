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

typedef Mat4x4 Mat4;

Mat4 Ortho(double left, double right, double bottom, double top, double near, double far);
Mat4 Mat4New(float diagonal);
const float* Mat4Cols(Mat4 mat);

Vec2 Mat4Vec2Mult(Mat4 mat, Vec2 vec);
Vec3 Mat4Vec3Mult(Mat4 mat, Vec3 vec);
Vec4 Mat4Vec4Mult(Mat4 mat, Vec4 vec);
Mat4 Mat4Mult(Mat4 m0, Mat4 m1);
Mat4 Mat4Scale(Mat4 mat, Vec4 vec);
Mat4 Mat4ScaleMatrix(Vec4 vec);
Mat4 Mat4Translate(Mat4 mat, Vec3 vec);
Mat4 Mat4TranslationMatrix(Vec3 vec);

Vec2 Vec2Normalize(Vec2 vec);
Vec2 Vec2Scale(Vec2 vec, float scalar);
float Vec2Dot(Vec2 vec1, Vec2 vec2);
float Vec2Length(Vec2 vec);
float Vec2Cross(Vec2 vec1, Vec2 vec2);
Vec2 Vec2Add(Vec2 vec1, Vec2 vec2);

Vec3 Vec3Normalize(Vec3 vec);
Vec3 Vec3Scale(Vec3 vec, float scalar);
float Vec3Dot(Vec3 vec1, Vec3 vec2);
float Vec3Length(Vec3 vec);
Vec3 Vec3Cross(Vec3 vec1, Vec3 vec2);
Vec3 Vec3Add(Vec3 vec1, Vec3 vec2);

Vec4 Vec4FromColor(Color color);

void PrintMat4x4(Mat4 mat);
void Vec2Print(Vec2* vec);

#endif
