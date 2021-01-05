#include "jtp_texture2d.h"
#include <stdlib.h>

static void _Texture2D_SetParameteri(Texture2D *texture, GLenum parameter, GLint value);

Texture2D *Texture2D_New(uint width, uint height, bool alpha, uchar *data) {
  Texture2D *texture = malloc(sizeof(Texture2D));

  glGenTextures(1, &texture->id);
  texture->width = width;
  texture->height = height;
  if (alpha) {
    texture->internalFormat = GL_RGBA;
    texture->imageFormat = GL_RGBA;
  } else {
    texture->internalFormat = GL_RGB;
    texture->imageFormat = GL_RGB;
  }
  texture->wrapS = GL_REPEAT;
  texture->wrapT = GL_REPEAT;
  texture->filterMin = GL_NEAREST;
  texture->filterMag = GL_NEAREST;

  glBindTexture(GL_TEXTURE_2D, texture->id);
  glTexImage2D(GL_TEXTURE_2D, 0, texture->internalFormat, width, height, 0, texture->imageFormat, GL_UNSIGNED_BYTE, data);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, texture->wrapS);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, texture->wrapT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, texture->filterMin);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, texture->filterMag);

  glBindTexture(GL_TEXTURE_2D, 0);

  return texture;
}

void Texture2D_Delete(Texture2D *texture) {
  glDeleteTextures(1, &texture->id);
  free(texture);
}

void Texture2D_Bind(Texture2D *texture) {
  glBindTexture(GL_TEXTURE_2D, texture->id);
}

void Texture2D_SetFilterMin(Texture2D *texture, uint filterMin) {
  texture->filterMin = filterMin;
  _Texture2D_SetParameteri(texture, GL_TEXTURE_MIN_FILTER, filterMin);
}

void Texture2D_SetFilterMag(Texture2D *texture, uint filterMag) {
  texture->filterMag = filterMag;
  _Texture2D_SetParameteri(texture, GL_TEXTURE_MAG_FILTER, filterMag);
}

void Texture2D_SetWrapS(Texture2D *texture, uint wrapS) {
  texture->wrapS = wrapS;
  _Texture2D_SetParameteri(texture, GL_TEXTURE_WRAP_S, wrapS);
}
void Texture2D_SetWrapT(Texture2D *texture, uint wrapT) {
  texture->wrapT = wrapT;
  _Texture2D_SetParameteri(texture, GL_TEXTURE_WRAP_T, wrapT);
}

static void _Texture2D_SetParameteri(Texture2D *texture, GLenum parameter, GLint value) {
  Texture2D_Bind(texture);
  glTexParameteri(GL_TEXTURE_2D, parameter, value);
  glBindTexture(GL_TEXTURE_2D, 0);
}
