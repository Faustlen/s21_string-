#include "s21_string.h"

#include <stdlib.h>

#include "errors.h"

char *s21_strchr(const char *str, int c) {
  char *q = s21_NULL;

  char occurrence = (char)c;
  while (*str && *str != occurrence) str++;
  if (*str == occurrence) q = (char *)str;

  return q;
}

char *s21_strrchr(const char *str, int c) {
  char *last_occurrence = s21_NULL;
  int i = 0;
  for (; str[i]; i++) {
    if (str[i] == c) {
      last_occurrence = (char *)str + i;
    }
  }
  if (c == '\0') {
    last_occurrence = (char *)str + i;
  }
  return last_occurrence;
}

void *s21_to_upper(const char *str) {
  if (str == s21_NULL) return s21_NULL;
  s21_size_t length = s21_strlen(str);
  char *result = (char *)calloc(length + 1, sizeof(char));
  if (result == s21_NULL) {
    return s21_NULL;
  }

  for (s21_size_t i = 0; i < length; ++i) {
    if (str[i] >= 'a' && str[i] <= 'z') {
      result[i] = str[i] - ('a' - 'A');
    } else {
      result[i] = str[i];
    }
  }

  result[length] = '\0';
  return result;
}

void *s21_to_lower(const char *str) {
  if (str == s21_NULL) return s21_NULL;
  s21_size_t length = s21_strlen(str);
  char *result = (char *)calloc(length + 1, sizeof(char));
  if (result == s21_NULL) {
    return s21_NULL;
  }

  for (s21_size_t i = 0; i < length; ++i) {
    if (str[i] >= 'A' && str[i] <= 'Z') {
      result[i] = str[i] + ('a' - 'A');
    } else {
      result[i] = str[i];
    }
  }

  result[length] = '\0';
  return result;
}

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  if (str == s21_NULL || src == s21_NULL) return s21_NULL;
  int err = 0;
  char *array = s21_NULL;
  if (start_index <= (s21_strlen(src))) {
    array = (char *)calloc(s21_strlen(src) + s21_strlen(str) + 1, sizeof(char));
    if (array == s21_NULL) {
      err = 1;
    }
    s21_size_t i = 0;
    for (; i < start_index; i++) {
      array[i] = src[i];
    }
    s21_size_t end = i;
    for (s21_size_t j = 0; j < s21_strlen(str); j++, i++) {
      array[i] = str[j];
    }
    for (; end < s21_strlen(src); end++, i++) {
      array[i] = src[end];
    }
    array[s21_strlen(array)] = '\0';
  } else {
    err = 1;
  }

  return err ? s21_NULL : (void *)array;
}

void *s21_trim(const char *src, const char *trim_chars) {
  if (src == s21_NULL || trim_chars == s21_NULL) return s21_NULL;
  void *q = s21_NULL;
  s21_size_t src_length = s21_strlen(src);

  s21_size_t start_index = 0;
  while (start_index < src_length &&
         s21_strchr(trim_chars, src[start_index]) != s21_NULL) {
    ++start_index;
  }

  s21_size_t end_index = src_length - 1;
  while (end_index > start_index &&
         s21_strchr(trim_chars, src[end_index]) != s21_NULL) {
    --end_index;
  }

  s21_size_t trimmed_length =
      (end_index >= start_index) ? (end_index - start_index + 1) : 0;

  char *result = (char *)calloc(trimmed_length + 1, sizeof(char));
  if (result != s21_NULL) {
    for (s21_size_t i = 0; i < trimmed_length; ++i) {
      result[i] = src[start_index + i];
    }

    result[trimmed_length] = '\0';
    q = result;
  }
  return q;
}

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  if (src == s21_NULL || dest == s21_NULL) return s21_NULL;
  s21_size_t dest_length = s21_strlen(dest);
  s21_size_t i;

  for (i = 0; i < n && src[i] != '\0'; ++i) {
    dest[dest_length + i] = src[i];
  }

  dest[dest_length + i] = '\0';
  return dest;
}

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  if (str1 == s21_NULL || str2 == s21_NULL) return 0;
  int q = 0;
  const unsigned char *s1 = str1;
  const unsigned char *s2 = str2;

  for (s21_size_t i = 0; i < n && q == 0; ++i) {
    if (s1[i] != s2[i]) {
      q = s1[i] - s2[i];
    }
  }

  return q;
}

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  if (src == s21_NULL || dest == s21_NULL) return s21_NULL;
  unsigned char *d = dest;
  const unsigned char *s = src;

  for (s21_size_t i = 0; i < n; ++i) {
    d[i] = s[i];
  }

  return dest;
}

void *s21_memset(void *str, int c, s21_size_t n) {
  if (str == s21_NULL) return s21_NULL;
  unsigned char *s = str;
  unsigned char uc = c;

  for (s21_size_t i = 0; i < n; ++i) {
    s[i] = uc;
  }

  return str;
}

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  if (str1 == s21_NULL || str2 == s21_NULL) return 0;
  int q = 0;

  s21_size_t i = 0;
  while (i < n && str1[i] != '\0' && str1[i] == str2[i]) {
    ++i;
  }

  if (i < n) {
    q = str1[i] - str2[i];
  }

  return q;
}

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  if (src == s21_NULL || dest == s21_NULL) return s21_NULL;
  s21_size_t i;

  for (i = 0; (i < n) && src[i] != '\0'; ++i) dest[i] = src[i];

  for (; i < n; ++i) dest[i] = '\0';

  return dest;
}

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  if (str1 == s21_NULL || str2 == s21_NULL) return 0;
  s21_size_t count = 0;
  while (str1[count] != '\0' && s21_strchr(str2, str1[count]) == s21_NULL) {
    ++count;
  }
  return count;
}

char *s21_strerror(int errnum) {
  char *res = s21_NULL;
  static char arr[128] = {'\0'};
  if (errnum <= MIN_ERRLIST || errnum >= MAX_ERRLIST) {
    s21_sprintf(arr, "%s%d", ERROR, errnum);
    res = arr;
  } else {
    res = (char *)err_sys_list[errnum];
  }
  return res;
}

char *s21_strpbrk(const char *str1, const char *str2) {
  if (str1 == s21_NULL || str2 == s21_NULL) return s21_NULL;
  char *q = s21_NULL;
  while (*str1 != '\0') {
    if (s21_strchr(str2, *str1) != s21_NULL) {
      q = (char *)str1;
      break;
    }
    ++str1;
  }
  return q;
}

char *s21_strstr(const char *haystack, const char *needle) {
  while (*haystack) {
    const char *h = haystack;
    const char *n = needle;
    
    while (*h && *n && *h == *n) {
      h++;
      n++;
    }
    if (*n == '\0') {
      return (char *)haystack;
    }
    haystack++;
  }

  return s21_NULL;
}

char *s21_strtok(char *str, const char *delim) {
  static char *lastToken = s21_NULL;
  char *token = s21_NULL;

  if ((str != s21_NULL || (lastToken != s21_NULL && *lastToken != '\0'))) {
    if (str != s21_NULL) {
      lastToken = str;
    }

    while (*lastToken && s21_strchr(delim, *lastToken) != s21_NULL) {
      ++lastToken;
    }

    if (*lastToken != '\0') {
      token = lastToken;

      while (*lastToken && s21_strchr(delim, *lastToken) == s21_NULL) {
        ++lastToken;
      }

      if (*lastToken != '\0') {
        *lastToken = '\0';
        ++lastToken;
      }
    }
  }

  return token;
}

void *s21_memchr(const void *ptr, int value, s21_size_t num) {
  if (ptr == s21_NULL) return s21_NULL;
  void *q = s21_NULL;
  const unsigned char *p = ptr;
  unsigned char v = (unsigned char)value;

  while (num-- > 0 && q == s21_NULL) {
    if (*p == v) {
      q = (void *)p;
    }
    ++p;
  }

  return q;
}