#include "test_string.h"

START_TEST(_default) {
  char result[] = "                     ";
  char expected[] = "                     ";
  int sym = '^';
  s21_size_t n = 12;

  s21_memset(result, sym, n);
  memset(expected, sym, n);
  ck_assert_str_eq(expected, result);
}
END_TEST

START_TEST(_zero_n) {
  char *result = "kittens are very cute!";
  char *expected = "kittens are very cute!";
  int sym = 7;
  s21_size_t n = 0;

  s21_memset(result, sym, n);
  memset(expected, sym, n);
  ck_assert_str_eq(expected, result);
}
END_TEST

START_TEST(_long_str) {
  char result[] = "kittens are very cute! meow";
  char expected[] = "kittens are very cute! meow";
  int sym = 'x';
  s21_size_t n = 28;

  s21_memset(result, sym, n);
  memset(expected, sym, n);
  ck_assert_str_eq(expected, result);
}
END_TEST

START_TEST(_void_str) {
  char result[32] = "";
  char expected[32] = "";
  int sym = '<';
  s21_size_t n = 12;

  s21_memset(result, sym, n);
  memset(expected, sym, n);
  ck_assert_str_eq(expected, result);
}
END_TEST

START_TEST(_void_sym) {
  char result[32] = "kittens are very cute! meow";
  char expected[32] = "kittens are very cute! meow";
  int sym = ' ';
  s21_size_t n = 24;

  s21_memset(result, sym, n);
  memset(expected, sym, n);
  ck_assert_str_eq(expected, result);
}
END_TEST

Suite *memset_suite() {
  Suite *s = suite_create("Tests for memset");
  TCase *tc = tcase_create("Tests for memset");

  tcase_add_test(tc, _default);
  tcase_add_test(tc, _zero_n);
  tcase_add_test(tc, _long_str);
  tcase_add_test(tc, _void_str);
  tcase_add_test(tc, _void_sym);

  suite_add_tcase(s, tc);

  return s;
}
