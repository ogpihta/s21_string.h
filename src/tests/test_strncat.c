#include "test_string.h"

START_TEST(_default) {
  char result[100] = "kitties !!";
  char expected[100] = "kitties !!";
  char pattern[20] = "wow !!";
  s21_size_t n = 100;

  ck_assert_str_eq(strncat(expected, pattern, n),
                   s21_strncat(result, pattern, n));
}
END_TEST

START_TEST(_void_str) {
  char result[100] = "";
  char expected[100] = "";
  char pattern[20] = "kitty !";
  s21_size_t n = 100;

  ck_assert_str_eq(strncat(expected, pattern, n),
                   s21_strncat(result, pattern, n));
}
END_TEST

START_TEST(_void_pattern) {
  char result[100] = "kitties !!";
  char expected[100] = "kitties !!";
  char pattern[20] = " ";
  s21_size_t n = 20;

  ck_assert_str_eq(strncat(expected, pattern, n),
                   s21_strncat(result, pattern, n));
}
END_TEST

START_TEST(_zero_n) {
  char result[100] = "kitties !!";
  char expected[100] = "kitties !!";
  char pattern[20] = " <3 ";
  s21_size_t n = 0;

  ck_assert_str_eq(strncat(expected, pattern, n),
                   s21_strncat(result, pattern, n));
}
END_TEST

START_TEST(_zero_pattern) {
  char result[100] = "kitties !!";
  char expected[100] = "kitties !!";
  char pattern[20] = " \0 ";
  s21_size_t n = 0;

  ck_assert_str_eq(strncat(expected, pattern, n),
                   s21_strncat(result, pattern, n));
}
END_TEST

START_TEST(_zero_str) {
  char result[100] = "\0";
  char expected[100] = "\0";
  char pattern[20] = " kitty ! ";
  s21_size_t n = 0;

  ck_assert_str_eq(strncat(expected, pattern, n),
                   s21_strncat(result, pattern, n));
}
END_TEST

START_TEST(_big_pattern) {
  char result[20] = "\0";
  char expected[20] = "\0";
  char pattern[100] = " kitty ! Kitty ! kitties !!";
  s21_size_t n = 0;

  ck_assert_str_eq(strncat(expected, pattern, n),
                   s21_strncat(result, pattern, n));
}
END_TEST

Suite *strncat_suite() {
  Suite *s = suite_create("Tests for strncat");
  TCase *tc = tcase_create("Tests for strncat");

  tcase_add_test(tc, _default);
  tcase_add_test(tc, _void_str);
  tcase_add_test(tc, _void_pattern);
  tcase_add_test(tc, _zero_n);
  tcase_add_test(tc, _zero_pattern);
  tcase_add_test(tc, _zero_str);
  tcase_add_test(tc, _big_pattern);

  suite_add_tcase(s, tc);

  return s;
}
