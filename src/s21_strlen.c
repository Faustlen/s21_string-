#include "s21_strlen.h"

#include <stdlib.h>

s21_size_t s21_strlen(const char *str) {
  if (str == s21_NULL) return 0;
  const char *end = str;
  while (*end != '\0') {
    ++end;
  }
  return (s21_size_t)(end - str);
}