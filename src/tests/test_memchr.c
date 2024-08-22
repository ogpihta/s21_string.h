#include "test_string.h"

START_TEST(_with_void_string) {
  char str[12] = "";
  int find = '\0';
  s21_size_t n = 0;

  ck_assert_ptr_eq(memchr(str, find, n), s21_memchr(str, find, n));
}
END_TEST

START_TEST(_default) {
  char str[12] = "1234567";
  int find = 5;
  s21_size_t n = 12;

  ck_assert_ptr_eq(memchr(str, find, n), s21_memchr(str, find, n));
}
END_TEST

START_TEST(_without_find_in_string) {
  char str[10] = "meow meow";
  int find = 'z';
  s21_size_t n = 6;

  ck_assert_ptr_eq(memchr(str, find, n), s21_memchr(str, find, n));
}
END_TEST

START_TEST(_without_find) {
  char str[10] = "meow meow";
  int find = ' ';
  s21_size_t n = 6;

  ck_assert_ptr_eq(memchr(str, find, n), s21_memchr(str, find, n));
}
END_TEST

START_TEST(_with_same) {
  char str[10] = "x";
  int find = 'x';
  s21_size_t n = 10;

  ck_assert_ptr_eq(memchr(str, find, n), s21_memchr(str, find, n));
}
END_TEST

START_TEST(_num_twice) {
  char str[64] = "1 2 6 1 9";
  int find = 1;
  s21_size_t n = 32;

  ck_assert_ptr_eq(memchr(str, find, n), s21_memchr(str, find, n));
}
END_TEST

Suite *memchr_suite() {
  Suite *s = suite_create("Tests for memchr");
  TCase *tc = tcase_create("Tests for memchr");

  tcase_add_test(tc, _with_void_string);
  tcase_add_test(tc, _default);
  tcase_add_test(tc, _without_find_in_string);
  tcase_add_test(tc, _without_find);
  tcase_add_test(tc, _with_same);
  tcase_add_test(tc, _num_twice);

  suite_add_tcase(s, tc);

  return s;
}
