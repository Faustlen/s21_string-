#ifndef S21_SPRINTF
#define S21_SPRINTF

#include <stdarg.h>

#include "s21_stddef.h"
#include "s21_strlen.h"

void processChar(char **buffer_ptr, char ch, int width, int alig, int space);
void processInt(char **buffer_ptr, long int num, int width, int alig, int space,
                int plus, int modif, int dac);
void processDouble(char **buffer_ptr, double num, int width, int alig,
                   int space, int plus, int accuracy);
void processString(char **buffer_ptr, const char *str, int width, int alig,
                   int space, int dac);
void processUnsigned(char **buffer_ptr, unsigned long num, int width, int alig,
                     int space, int modif, int dac);
void fillWithSpaces(char ***buffer_ptr, int count);
void parseFormatString(const char **format, int *plus, int *alig, int *space,
                       int *width, int *modif, int *accuracy, int *dac);
void oleg(const char ***format, int **alig);

double roundWithPrecision(double number, int precision);
int s21_sprintf(char *buffer, const char *format, ...);

#endif