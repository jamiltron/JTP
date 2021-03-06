#ifndef JTP_TEXTURE_2D_H
#define JTP_TEXTURE_2D_H
#include <glad/glad.h>
#include "jtp_math.h"
#include <stdbool.h>

typedef struct Texture2D Texture2D;

Texture2D *Texture2D_New(uint width, uint height, bool alpha, uchar *data);
void Texture2D_Delete(Texture2D *texture);
void Texture2D_Bind(Texture2D *texture);
void Texture2D_SetFilterMin(Texture2D *texture, uint filterMin);
void Texture2D_SetFilterMag(Texture2D *texture, uint filterMag);
void Texture2D_SetWrapS(Texture2D *texture, uint wrapS);
void Texture2D_SetWrapT(Texture2D *texture, uint wrapT);

#endif
