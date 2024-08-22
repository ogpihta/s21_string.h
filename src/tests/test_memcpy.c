#include "test_string.h"

START_TEST(_default_with_void_dest) {
  char result[10];
  char expected[10];
  char src[10] = " meow ";
  s21_size_t n = 7;

  s21_memcpy(result, src, n);
  memcpy(expected, src, n);
  ck_assert_mem_eq(expected, result, n);
}
END_TEST

START_TEST(_default_with_zero_n) {
  char result[10];
  char expected[10];
  char src[10] = " meow ";
  s21_size_t n = 0;

  s21_memcpy(result, src, n);
  memcpy(expected, src, n);
  ck_assert_mem_eq(expected, result, n);
}
END_TEST

START_TEST(_with_diff_str) {
  char result[10] = "kitty";
  char expected[10] = "kitty";
  char src[10] = " meow ";
  s21_size_t n = 0;

  s21_memcpy(result, src, n);
  memcpy(expected, src, n);
  ck_assert_mem_eq(expected, result, n);
}
END_TEST

START_TEST(_long_str_with_register) {
  char result[64];
  char expected[64];
  char *src = "kittens are Very cute! ";
  s21_size_t n = 15;

  s21_memcpy(result, src, n);
  memcpy(expected, src, n);
  ck_assert_mem_eq(expected, result, n);
}
END_TEST

START_TEST(_long_str_with_register_sym_num) {
  char result[128];
  char expected[128];
  char *src = "kittens are Very cute! <333 ";
  s21_size_t n = 10;

  s21_memcpy(result, src, n);
  memcpy(expected, src, n);
  ck_assert_mem_eq(expected, result, n);
}
END_TEST

Suite *memcpy_suite() {
  Suite *s = suite_create("Tests for memcpy");
  TCase *tc = tcase_create("Tests for memcpy");

  tcase_add_test(tc, _default_with_void_dest);
  tcase_add_test(tc, _default_with_zero_n);
  tcase_add_test(tc, _with_diff_str);
  tcase_add_test(tc, _long_str_with_register);
  tcase_add_test(tc, _long_str_with_register_sym_num);

  suite_add_tcase(s, tc);

  return s;
}
