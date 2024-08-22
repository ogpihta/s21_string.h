#include "test_string.h"

START_TEST(_default_with_void_dest) {
  char result[10];
  char expected[10];
  char src[10] = " meow ";
  s21_size_t n = 7;

  s21_strncpy(result, src, n);
  strncpy(expected, src, n);
  ck_assert_str_eq(expected, result);
}
END_TEST

START_TEST(_default_with_zero_n) {
  char result[10] = "meow ";
  char expected[10] = "meow ";
  char src[10] = " meow ";
  s21_size_t n = 0;

  s21_strncpy(result, src, n);
  strncpy(expected, src, n);
  ck_assert_str_eq(expected, result);
}
END_TEST

START_TEST(_with_diff_str) {
  char result[10] = "kitty";
  char expected[10] = "kitty";
  char src[10] = " meow ";
  s21_size_t n = 0;

  s21_strncpy(result, src, n);
  strncpy(expected, src, n);
  ck_assert_str_eq(expected, result);
}
END_TEST

START_TEST(_long_str_with_register) {
  char result[64];
  char expected[64];
  char *src = "kittens are Very cute! ";
  s21_size_t n = 48;

  s21_strncpy(result, src, n);
  strncpy(expected, src, n);
  ck_assert_str_eq(expected, result);
}
END_TEST

START_TEST(_long_str_with_register_sym_num) {
  char result[128];
  char expected[128];
  char *src = "kittens are Very cute! <333 ";
  s21_size_t n = 128;

  s21_strncpy(result, src, n);
  strncpy(expected, src, n);
  ck_assert_str_eq(expected, result);
}
END_TEST

START_TEST(_void_all) {
  char result[128];
  char expected[128];
  char *src = " ";
  s21_size_t n = 128;

  s21_strncpy(result, src, n);
  strncpy(expected, src, n);
  ck_assert_str_eq(expected, result);
}
END_TEST

Suite *strncpy_suite() {
  Suite *s = suite_create("Tests for strncpy");
  TCase *tc = tcase_create("Tests for strncpy");

  tcase_add_test(tc, _default_with_void_dest);
  tcase_add_test(tc, _default_with_zero_n);
  tcase_add_test(tc, _with_diff_str);
  tcase_add_test(tc, _long_str_with_register);
  tcase_add_test(tc, _long_str_with_register_sym_num);
  tcase_add_test(tc, _void_all);

  suite_add_tcase(s, tc);

  return s;
}
