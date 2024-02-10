#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_string.h"  // Ваш заголовочный файл с реализацией функций

// Проверка для s21_to_upper
START_TEST(test_to_upper) {
  const char *input = "Hello, World!";
  char *expected = "HELLO, WORLD!";
  char *result = s21_to_upper(input);
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

// Проверка для s21_to_lower
START_TEST(test_to_lower) {
  const char *input = "Hello, World!";
  char *expected = "hello, world!";
  char *result = s21_to_lower(input);
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

// Проверка для s21_insert
START_TEST(test_insert) {
  const char *src = "Hello, !";
  const char *str = "World";
  s21_size_t start_index = 7;
  char *expected = "Hello, World!";
  char *result = s21_insert(src, str, start_index);
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

// Проверка для s21_trim
START_TEST(test_trim) {
  const char *src = "  Hello, World!  ";
  const char *trim_chars = " ";
  char *expected = "Hello, World!";
  char *result = s21_trim(src, trim_chars);
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

// Проверка для s21_strncat
START_TEST(test_strncat) {
  char dest[20] = "Hello, ";
  const char *src = "Wowrld!";
  char *expected = strncat(dest, src, s21_strlen(src));
  char *result = s21_strncat(dest, src, s21_strlen(src));
  ck_assert_str_eq(result, expected);
}
END_TEST

// Проверка для s21_memcmp
START_TEST(test_memcmp) {
  const char *str2 = "aaa";
  ck_assert_int_eq(s21_memcmp("aab", str2, 2), memcmp("aab", str2, 2));
}
END_TEST

// Проверка для s21_memcpy
START_TEST(test_memcpy) {
  const char *src = "Haello";
  char dest[10];
  char *expected = memcpy(dest, src, s21_strlen(src));
  char *result = s21_memcpy(dest, src, s21_strlen(src));
  ck_assert_mem_eq(result, expected, s21_strlen(src));
}
END_TEST

// Проверка для s21_memset
START_TEST(test_memset) {
  char str[10];
  s21_size_t n = 5;
  int c = 'A';
  char *expected = memset(str, c, n);
  char *result = s21_memset(str, c, n);
  ck_assert_mem_eq(result, expected, n);
}
END_TEST

// Проверка для s21_strncmp
START_TEST(test_strncmp) {
  const char *str1 = "Hello, World!";
  const char *str2 = "Hello, World!";
  s21_size_t n = 20;
  int result = s21_strncmp(str1, str2, n);
  int expected = strncmp(str1, str2, n);
  ck_assert_int_eq(result, expected);
}
END_TEST

// Проверка для s21_strncpy
START_TEST(test_strncpy) {
  const char *src = "Hello, World!";
  s21_size_t n = 5;
  char dest[10] = "";
  char *expected = strncpy(dest, src, n);
  char *result = s21_strncpy(dest, src, n);
  ck_assert_str_eq(result, expected);
}
END_TEST

// Проверка для s21_strcspn
START_TEST(test_strcspn) {
  const char *str1 = "Hello, World!";
  const char *str2 = "rWd";
  double expected = strcspn(str1, str2);
  s21_size_t result = s21_strcspn(str1, str2);
  ck_assert_int_eq(result, expected);
}
END_TEST

// Проверка для s21_strerror
START_TEST(test_strerror) {
  int errnum = 9;  // Пример кода ошибки (может быть изменен)
  const char *result = s21_strerror(errnum);
  const char *expected = strerror(errnum);
  ck_assert_str_eq(result, expected);
}
END_TEST

// Проверка для s21_strlen
START_TEST(test_strlen) {
  const char *input = "Hello, World!";
  s21_size_t expected = strlen(input);
  s21_size_t result = s21_strlen(input);
  ck_assert_int_eq(result, expected);
}
END_TEST

// Проверка для s21_strpbrk
START_TEST(test_strpbrk) {
  const char *str1 = "Hello, World!";
  const char *str2 = "aeiou";
  const char *expected = strpbrk(str1, str2);
  char *result = s21_strpbrk(str1, str2);
  ck_assert_str_eq(result, expected);
}
END_TEST

// Проверка для s21_strchr
START_TEST(test_strchr) {
  const char *input = "Hello, World!";
  const char c = 'a';
  char *expected = strchr(input, c);
  char *result = s21_strchr(input, c);
  ck_assert_pstr_eq(result, expected);
}
END_TEST

// Проверка для s21_strrchr
START_TEST(test_strrchr) {
  const char *input = "Hello, World!";
  int c = 'k';
  char *expected = strrchr(input, c);
  char *result = s21_strrchr(input, c);
  ck_assert_pstr_eq(result, expected);
}
END_TEST

// Проверка для s21_strstr
START_TEST(test_strstr) {
  const char *haystack = "Hellohea123llohello";
  const char *needle = "3";
  const char *expected = strstr(haystack, needle);
  char *result = s21_strstr(haystack, needle);
  ck_assert_pstr_eq(result, expected);
}
END_TEST

// Проверка для s21_strtok
START_TEST(test_strtok) {
  char input[] = "pepepupu";
  const char *delim = " ";
  char *expected = strtok(input, delim);
  char *result = s21_strtok(input, delim);

  ck_assert_str_eq(result, expected);
  result = s21_strtok(s21_NULL, delim);
}
END_TEST

// Проверка для s21_memchr
START_TEST(test_memchr) {
  const char *str = "Hello, World!";
  int character_to_find = ',';
  s21_size_t length = strlen(str);

  const void *expected = memchr(str, character_to_find, length);
  void *result = s21_memchr(str, character_to_find, length);
  ck_assert_ptr_eq(result, expected);
}
END_TEST

// Проверка для s21_sprintf
START_TEST(test_sprintf_s) {
  char buffer[50];
  char *value = {"pepepupu"};
  sprintf(buffer, "Value: %20.5s", value);

  char s21_buffer[50];
  s21_sprintf(s21_buffer, "Value: %20.5s", value);

  ck_assert_str_eq(buffer, s21_buffer);
}
END_TEST

START_TEST(test_sprintf_c) {
  char buffer[50];
  char value = 'i';
  sprintf(buffer, "Value: %c", value);

  char s21_buffer[50];
  s21_sprintf(s21_buffer, "Value: %c", value);

  ck_assert_str_eq(buffer, s21_buffer);
}
END_TEST

START_TEST(test_sprintf_d) {
  char buffer[50];
   int value = 222;
  sprintf(buffer, "Value: % -10d", value);

  char s21_buffer[50];
  s21_sprintf(s21_buffer, "Value: % -10d", value);
  //ck_assert_int_eq(res, exp);
  ck_assert_str_eq(buffer, s21_buffer);
}
END_TEST

START_TEST(test_sprintf_f) {
  // char buffer[50];
  // double value = 123.5;
  // sprintf(buffer, "Value: %- f", value);

  // char s21_buffer[50];
  // s21_sprintf(s21_buffer, "Value: %- f", value);

  // ck_assert_str_eq(buffer, s21_buffer);
}
END_TEST

START_TEST(test_sprintf_u) {
  char buffer[50];
  unsigned short int value = 213;
  sprintf(buffer, "Value: %-6.10hu", value);

  char s21_buffer[50];
  s21_sprintf(s21_buffer, "Value: %-6.10hu", value);

  ck_assert_str_eq(buffer, s21_buffer);
}
END_TEST

START_TEST(test_sprintf_percent) {
  char buffer[50];
  double z = -1.5555;
  sprintf(buffer, "Value: %.8f", z);

  char s21_buffer[50];
  s21_sprintf(s21_buffer, "Value: %.8f", z);
  ck_assert_str_eq(buffer, s21_buffer);
}
END_TEST

// Определение сьюта тестов
Suite *s21_string_suite(void) {
  Suite *suite = suite_create("s21_string");

  TCase *case_to_upper = tcase_create("to_upper");
  tcase_add_test(case_to_upper, test_to_upper);
  suite_add_tcase(suite, case_to_upper);

  TCase *case_to_lower = tcase_create("to_lower");
  tcase_add_test(case_to_lower, test_to_lower);
  suite_add_tcase(suite, case_to_lower);

  TCase *case_insert = tcase_create("insert");
  tcase_add_test(case_insert, test_insert);
  suite_add_tcase(suite, case_insert);

  TCase *case_trim = tcase_create("trim");
  tcase_add_test(case_trim, test_trim);
  suite_add_tcase(suite, case_trim);

  TCase *case_strncmp = tcase_create("strncmp");
  tcase_add_test(case_strncmp, test_strncmp);
  suite_add_tcase(suite, case_strncmp);

  TCase *case_strncpy = tcase_create("strncpy");
  tcase_add_test(case_strncpy, test_strncpy);
  suite_add_tcase(suite, case_strncpy);

  TCase *case_strcspn = tcase_create("strcspn");
  tcase_add_test(case_strcspn, test_strcspn);
  suite_add_tcase(suite, case_strcspn);

  TCase *case_strerror = tcase_create("strerror");
  tcase_add_test(case_strerror, test_strerror);
  suite_add_tcase(suite, case_strerror);

  TCase *case_strncat = tcase_create("strncat");
  tcase_add_test(case_strncat, test_strncat);
  suite_add_tcase(suite, case_strncat);

  TCase *case_memcmp = tcase_create("memcmp");
  tcase_add_test(case_memcmp, test_memcmp);
  suite_add_tcase(suite, case_memcmp);

  TCase *case_memcpy = tcase_create("memcpy");
  tcase_add_test(case_memcpy, test_memcpy);
  suite_add_tcase(suite, case_memcpy);

  TCase *case_memset = tcase_create("memset");
  tcase_add_test(case_memset, test_memset);
  suite_add_tcase(suite, case_memset);

  TCase *case_strlen = tcase_create("strlen");
  tcase_add_test(case_strlen, test_strlen);
  suite_add_tcase(suite, case_strlen);

  TCase *case_strpbrk = tcase_create("strpbrk");
  tcase_add_test(case_strpbrk, test_strpbrk);
  suite_add_tcase(suite, case_strpbrk);

  TCase *case_strchr = tcase_create("strchr");
  tcase_add_test(case_strchr, test_strchr);
  suite_add_tcase(suite, case_strchr);

  TCase *case_strrchr = tcase_create("strrchr");
  tcase_add_test(case_strrchr, test_strrchr);
  suite_add_tcase(suite, case_strrchr);

  TCase *case_strstr = tcase_create("strstr");
  tcase_add_test(case_strstr, test_strstr);
  suite_add_tcase(suite, case_strstr);

  TCase *case_strtok = tcase_create("strtok");
  tcase_add_test(case_strtok, test_strtok);
  suite_add_tcase(suite, case_strtok);

  TCase *case_memchr = tcase_create("memchr");
  tcase_add_test(case_memchr, test_memchr);
  suite_add_tcase(suite, case_memchr);

  TCase *case_sprintf_c = tcase_create("sprintf_c");
  tcase_add_test(case_sprintf_c, test_sprintf_c);
  suite_add_tcase(suite, case_sprintf_c);

  TCase *case_sprintf_d = tcase_create("sprintf_d");
  tcase_add_test(case_sprintf_d, test_sprintf_d);
  suite_add_tcase(suite, case_sprintf_d);

  TCase *case_sprintf_f = tcase_create("sprintf_f");
  tcase_add_test(case_sprintf_f, test_sprintf_f);
  suite_add_tcase(suite, case_sprintf_f);

  TCase *case_sprintf_u = tcase_create("sprintf_u");
  tcase_add_test(case_sprintf_u, test_sprintf_u);
  suite_add_tcase(suite, case_sprintf_u);

  TCase *case_sprintf_s = tcase_create("sprintf_s");
  tcase_add_test(case_sprintf_s, test_sprintf_s);
  suite_add_tcase(suite, case_sprintf_s);

  TCase *case_sprintf_percent = tcase_create("sprintf_percent");
  tcase_add_test(case_sprintf_percent, test_sprintf_percent);
  suite_add_tcase(suite, case_sprintf_percent);

  /*
  TCase *case_sscanf = tcase_create("sscanf");
  tcase_add_test(case_sscanf, test_sscanf);
  suite_add_tcase(suite, case_sscanf);
  */

  return suite;
}

// Входная функция для запуска тестов
int main() {
  Suite *suite = s21_string_suite();
  SRunner *runner = srunner_create(suite);

  srunner_run_all(runner, CK_NORMAL);
  int failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
