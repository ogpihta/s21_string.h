#include "test_string.h"

START_TEST(_default) {
  char str[] = "kittens are Very cute! <333 ";

  ck_assert_int_eq(strlen(str), s21_strlen(str));
}
END_TEST

START_TEST(_void_str) {
  char str[] = " ";

  ck_assert_int_eq(strlen(str), s21_strlen(str));
}
END_TEST

START_TEST(_with_zero) {
  char str[] = "kittens are Very cute! <333 \0 ˓˓ก₍⸍⸌̣ʷ̣̫⸍̣⸌₎ค˒˒ ";

  ck_assert_int_eq(strlen(str), s21_strlen(str));
}
END_TEST

START_TEST(_with_only_zero) {
  char str[] = "\0";

  ck_assert_int_eq(strlen(str), s21_strlen(str));
}
END_TEST

Suite *strlen_suite() {
  Suite *s = suite_create("Tests for strlen");
  TCase *tc = tcase_create("Tests for strlen");

  tcase_add_test(tc, _default);
  tcase_add_test(tc, _void_str);
  tcase_add_test(tc, _with_zero);
  tcase_add_test(tc, _with_only_zero);

  suite_add_tcase(s, tc);

  return s;
}
