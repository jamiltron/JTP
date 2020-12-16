#ifndef JTP_STRING_H
#define JTP_STRING_H
#include <stdbool.h>

char* StringLeftTrim(const char* string, const char* chaff);
char* StringRightTrim(const char* string, const char* chaff);
bool StringContainsCharacter(const char* string, char character);
bool StringContainsAnyCharacter(const char* string, const char* characters);

#endif