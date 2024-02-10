#include <math.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

#include "s21_sprintf.h"


int s21_sprintf(char *buffer, const char *format, ...) {
  va_list args;
  va_start(args, format);

  char *buffer_ptr = buffer;

  while (*format != '\0') {
    int plus = 0, alig = 0, space = 0, width = 0, modif = 0, accuracy = 6,
        dac = 0;
    if (*format == '%') {
      format++;

      parseFormatString(&format, &plus, &alig, &space, &width, &modif,
                        &accuracy, &dac);

      // Обработка спецификаторов
      switch (*format) {
        case 'c':
          processChar(&buffer_ptr, (char)va_arg(args, int), width, alig, space);
          break;
        case 'd': {
          processInt(&buffer_ptr,
                     (modif == 1) ? va_arg(args, long int) : va_arg(args, int),
                     width, alig, space, plus, modif, dac);
        } break;
        case 'f': {
          processDouble(&buffer_ptr, va_arg(args, double), width, alig, space,
                        plus, accuracy);
        } break;
        case 's': {
          processString(&buffer_ptr, va_arg(args, const char *), width, alig,
                        space, dac);
        } break;
        case 'u': {
          processUnsigned(&buffer_ptr,
                          (modif == 1) ? va_arg(args, long unsigned)
                                       : va_arg(args, unsigned),
                          width, alig, space, modif, dac);
        } break;
        case '%':
          *buffer_ptr = '%';
          buffer_ptr++;
          break;
        default:
          // Неизвестный спецификатор, игнорируем
          break;
      }
    } else {
      *buffer_ptr = *format;
      buffer_ptr++;
    }

    format++;
  }

  *buffer_ptr = '\0';  // Завершаем строку нулевым символом
  va_end(args);
  return (buffer_ptr - buffer);
}

double roundWithPrecision(double number, int precision) {
  double factor = pow(10, precision);
  double roundedValue = floor(number * factor + 0.5) / factor;
  return roundedValue;
}

void processChar(char **buffer_ptr, char ch, int width, int alig, int space) {
  // Заполнение пробелами
  if (!alig) {
    fillWithSpaces(&buffer_ptr, width - space - 1);
  }

  **buffer_ptr = ch;
  (*buffer_ptr)++;

  // Заполнение пробелами
  if (alig) {
    fillWithSpaces(&buffer_ptr, width - space - 1);
  }
}

void processInt(char **buffer_ptr, long int num, int width, int alig, int space,
                int plus, int modif, int dac) {
  long int divisor = 1, min = 0;
  int digits = 1;

  if (num < 0) {
    min = 1;
    num = -num;
  }

  while (num / divisor > 9) {
    divisor *= 10;
    digits++;
  }

  if (!min && space) {
    **buffer_ptr = ' ';
    (*buffer_ptr)++;
  }
  space = min ? 0 : space;
  plus = min ? 0 : plus;

  // Заполнение пробелами перед числом
  if (!alig) {
    fillWithSpaces(&buffer_ptr, width - space - min - plus - ((dac>digits) ? dac : digits));
  }

  if (min) {
    **buffer_ptr = '-';
    (*buffer_ptr)++;
  }

  if (plus && !min) {
    **buffer_ptr = '+';
    (*buffer_ptr)++;
  }
  if (dac) {
    for (int i = 0; i < dac-digits; i++) {
      **buffer_ptr = '0';
      (*buffer_ptr)++;
    }
  }
  // Заполнение числа
  while (divisor >= 1) {
    **buffer_ptr = '0' + num / divisor;
    (*buffer_ptr)++;
    num %= divisor;
    divisor /= 10;
  }

  // Заполнение пробелами после числа
  if (alig) {
    fillWithSpaces(&buffer_ptr, width - space - min - plus - ((dac>digits) ? dac : digits));
  }
}

void processDouble(char **buffer_ptr, double num, int width, int alig,
                   int space, int plus, int accuracy) {

  int int_part;
  if (accuracy == 0) {
    int_part = (int)round(num);
  } else {
  int_part = (int)num;
  }

  num -= int_part;

  // Расчёт целой части
  long int divisor = 1, min = 0;
  int digits = 1 + accuracy;
  digits = (accuracy == 0) ? digits : (digits + 1);

  if (int_part < 0) {
    min = 1;
    int_part = -int_part;
    num = -num;
  }
  while (int_part / divisor > 9) {
    divisor *= 10;
    digits++;
  }

  if (!min && space) {
    **buffer_ptr = ' ';
    (*buffer_ptr)++;
  }
  space = min ? 0 : space;
  plus = min ? 0 : plus;

  // Заполнение пробелами перед числом
  if (!alig) {
    fillWithSpaces(&buffer_ptr, width - digits - space - min - plus);
  }

  if (min) {
    **buffer_ptr = '-';
    (*buffer_ptr)++;
  }

  if (plus && !min) {
    **buffer_ptr = '+';
    (*buffer_ptr)++;
  }
  // Заполнение целой части
  while (divisor >= 1) {
    **buffer_ptr = '0' + int_part / divisor;
    (*buffer_ptr)++;
    int_part %= divisor;
    divisor /= 10;
  }

  // Десятичная точка
  if (accuracy > 0) {
    **buffer_ptr = '.';
    (*buffer_ptr)++;
  }

  // Заполнение десятичной части
  for (int i = 0; i < accuracy; i++) {
    num *= 10;
    **buffer_ptr = '0' + ((accuracy == i+1) ? (int)round(num) : (int)roundWithPrecision(num, 2));
    (*buffer_ptr)++;
    num -= (int)roundWithPrecision(num, 2);
  }

  // Заполнение пробелами после числа
  if (alig) {
    fillWithSpaces(&buffer_ptr, width - digits - space - min - plus);
  }
}

void processString(char **buffer_ptr, const char *str, int width, int alig,
                   int space, int dac) {
  int str_len = s21_strlen(str);
  if (space) {
    **buffer_ptr = ' ';
    (*buffer_ptr)++;
  }

  // Заполнение пробелами перед строкой
  if (!alig) {
    fillWithSpaces(&buffer_ptr, width - str_len - space);
  }

  //for (int i; i<dac )
  while (*str != '\0') {
    **buffer_ptr = *str;
    (*buffer_ptr)++;
    str++;
  }

  // Заполнение пробелами после строки
  if (alig) {
    fillWithSpaces(&buffer_ptr, width - str_len - space);
  }
}

void processUnsigned(char **buffer_ptr, unsigned long num, int width, int alig,
                     int space, int modif, int dac) {
  unsigned long divisor = 1;
  int digits = 1;
  while (num / divisor > 9) {
    divisor *= 10;
    digits++;
  }

  if (space) {
    **buffer_ptr = ' ';
    (*buffer_ptr)++;
  }

  if (dac) {
    for (int i = 0; i < dac-digits; i++) {
      **buffer_ptr = '0';
      (*buffer_ptr)++;
    }
  }

  // Заполнение пробелами перед числом
  if (!alig) {
    fillWithSpaces(&buffer_ptr, width - space - ((dac>digits) ? dac : digits));
  }

  while (divisor >= 1) {
    **buffer_ptr = '0' + num / divisor;
    (*buffer_ptr)++;
    num %= divisor;
    divisor /= 10;
  }

  // Заполнение пробелами после числа
  if (alig) {
    fillWithSpaces(&buffer_ptr, width - space - ((dac>digits) ? dac : digits));
  }
}

void fillWithSpaces(char ***buffer_ptr, int count) {
  for (int i = 0; i < count; i++) {
    ***buffer_ptr = ' ';
    (**buffer_ptr)++;
  }
}

void parseFormatString(const char **format, int *plus, int *alig, int *space,
                       int *width, int *modif, int *accuracy, int *dac) {
  // Обработка олега
  oleg(&format, &alig);

  if (**format == ' ') {
    (*format)++;
    if (**format != '+') {
      *space = 1;
    }
  }

  if (**format == '+') {
    *plus = 1;
    (*format)++;
  }
  // Обработка олега
  oleg(&format, &alig);

  // Обработка ширины
  while (**format >= '0' && **format <= '9') {
    *width = *width * 10 + (**format - '0');
    (*format)++;
  }

  // Обработка точности после запятой
  if (**format == '.') {
    (*format)++;
    *accuracy = 0;

    while (**format >= '0' && **format <= '9') {
      *accuracy = *accuracy * 10 + (**format - '0');
      *dac = *dac * 10 + (**format - '0');
      (*format)++;
    }
  }

  // Обработка длины
  if (**format == 'l') {
    *modif = 1;
    (*format)++;
  } else if (**format == 'h') {
    *modif = -1;
    (*format)++;
  }
}

// знакомьтесь, олег
void oleg(const char ***format, int **alig) {
  if (***format == '-') {
    **alig = 1;
    (**format)++;
  }
}