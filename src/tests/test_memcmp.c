#include "test_string.h"

START_TEST(_default) {
  char str1[32] = "kitty !!";
  char str2[32] = "kitty !!";
  s21_size_t n = 5;

  int result = s21_memcmp(str1, str2, n);
  int expected = memcmp(str1, str2, n);

  if (result > 0) result = 1;
  if (result < 0) result = -1;
  if (expected > 0) expected = 1;
  if (expected < 0) expected = -1;

  ck_assert_int_eq(expected, result);
}
END_TEST

START_TEST(_different_str) {
  char str1[32] = "kitty !!";
  char str2[32] = "puppies !!";
  s21_size_t n = 10;

  int result = s21_memcmp(str1, str2, n);
  int expected = memcmp(str1, str2, n);

  if (result > 0) result = 1;
  if (result < 0) result = -1;
  if (expected > 0) expected = 1;
  if (expected < 0) expected = -1;

  ck_assert_int_eq(expected, result);
}
END_TEST

START_TEST(_different_str_2) {
  char str1[32] = "kitty !!";
  char str2[32] = "kittens";
  s21_size_t n = 1;

  int result = s21_memcmp(str1, str2, n);
  int expected = memcmp(str1, str2, n);

  if (result > 0) result = 1;
  if (result < 0) result = -1;
  if (expected > 0) expected = 1;
  if (expected < 0) expected = -1;

  ck_assert_int_eq(expected, result);
}
END_TEST

START_TEST(_register) {
  char str1[32] = "kitty !!";
  char str2[32] = "kiTTy !!";
  s21_size_t n = 24;

  int result = s21_memcmp(str1, str2, n);
  int expected = memcmp(str1, str2, n);

  if (result > 0) result = 1;
  if (result < 0) result = -1;
  if (expected > 0) expected = 1;
  if (expected < 0) expected = -1;

  ck_assert_int_eq(expected, result);
}
END_TEST

START_TEST(_zero_n) {
  char str1[64] = "kittens are Very cute! ";
  char str2[64] = "kittens are Very cute! ";
  s21_size_t n = 0;

  int result = s21_memcmp(str1, str2, n);
  int expected = memcmp(str1, str2, n);

  if (result > 0) result = 1;
  if (result < 0) result = -1;
  if (expected > 0) expected = 1;
  if (expected < 0) expected = -1;

  ck_assert_int_eq(expected, result);
}
END_TEST

START_TEST(_void_str1) {
  char str1[32] = "  ";
  char str2[32] = "meow meow meow";
  s21_size_t n = 12;

  int result = s21_memcmp(str1, str2, n);
  int expected = memcmp(str1, str2, n);

  if (result > 0) result = 1;
  if (result < 0) result = -1;
  if (expected > 0) expected = 1;
  if (expected < 0) expected = -1;

  ck_assert_int_eq(expected, result);
}
END_TEST

START_TEST(_void_str2) {
  char str1[32] = " meow meow meow ";
  char str2[32] = " ";
  s21_size_t n = 12;

  int result = s21_memcmp(str1, str2, n);
  int expected = memcmp(str1, str2, n);

  if (result > 0) result = 1;
  if (result < 0) result = -1;
  if (expected > 0) expected = 1;
  if (expected < 0) expected = -1;

  ck_assert_int_eq(expected, result);
}
END_TEST

START_TEST(_void_all_str) {
  char str1[32] = " ";
  char str2[32] = " ";
  s21_size_t n = 24;

  int result = s21_memcmp(str1, str2, n);
  int expected = memcmp(str1, str2, n);

  if (result > 0) result = 1;
  if (result < 0) result = -1;
  if (expected > 0) expected = 1;
  if (expected < 0) expected = -1;

  ck_assert_int_eq(expected, result);
}
END_TEST

START_TEST(_NULL_all_str) {
  char *str1 = NULL;
  char *str2 = NULL;
  s21_size_t n = 0;

  int result = s21_memcmp(str1, str2, n);
  int expected = memcmp(str1, str2, n);

  if (result > 0) result = 1;
  if (result < 0) result = -1;
  if (expected > 0) expected = 1;
  if (expected < 0) expected = -1;

  ck_assert_int_eq(expected, result);
}
END_TEST

Suite *memcmp_suite() {
  Suite *s = suite_create("Tests for memcmp");
  TCase *tc = tcase_create("Tests for memcmp");

  tcase_add_test(tc, _default);
  tcase_add_test(tc, _different_str);
  tcase_add_test(tc, _different_str_2);
  tcase_add_test(tc, _register);
  tcase_add_test(tc, _zero_n);
  tcase_add_test(tc, _void_str1);
  tcase_add_test(tc, _void_str2);
  tcase_add_test(tc, _void_all_str);
  tcase_add_test(tc, _NULL_all_str);

  suite_add_tcase(s, tc);

  return s;
}
