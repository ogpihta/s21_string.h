#include "test_string.h"

START_TEST(_default) {
  char str[15] = "kitty !!";
  char expected_str[15] = "kitty !!";
  char pattern[] = " meow";

  ck_assert_str_eq(strcat(expected_str, pattern), s21_strcat(str, pattern));
}
END_TEST

START_TEST(_void_pattern) {
  char str[15] = "kitty !!";
  char expected_str[15] = "kitty !!";
  char pattern[] = "";

  ck_assert_str_eq(strcat(expected_str, pattern), s21_strcat(str, pattern));
}
END_TEST

START_TEST(_void_str) {
  char str[15] = "";
  char expected_str[15] = "";
  char pattern[] = "meow";

  ck_assert_str_eq(strcat(expected_str, pattern), s21_strcat(str, pattern));
}
END_TEST

START_TEST(_zero_pattern) {
  char str[15] = "kitty !!";
  char expected_str[15] = "kitty !!";
  char pattern[] = "\0";

  ck_assert_str_eq(strcat(expected_str, pattern), s21_strcat(str, pattern));
}
END_TEST

START_TEST(_zero_str) {
  char str[15] = "\0";
  char expected_str[15] = "\0";
  char pattern[] = "meow";

  ck_assert_str_eq(strcat(expected_str, pattern), s21_strcat(str, pattern));
}
END_TEST

Suite *strcat_suite() {
  Suite *s = suite_create("Tests for strcat");
  TCase *tc = tcase_create("Tests for strcat");

  tcase_add_test(tc, _default);
  tcase_add_test(tc, _void_pattern);
  tcase_add_test(tc, _void_str);
  tcase_add_test(tc, _zero_pattern);
  tcase_add_test(tc, _zero_str);

  suite_add_tcase(s, tc);

  return s;
}
