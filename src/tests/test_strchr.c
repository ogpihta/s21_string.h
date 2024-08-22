#include "test_string.h"

START_TEST(_default) {
  char str[12] = "kitty";
  int sym = 't';

  ck_assert_pstr_eq(strchr(str, sym), s21_strchr(str, sym));
}
END_TEST

START_TEST(_void_str) {
  char str[32] = "";
  int sym = '^';

  ck_assert_pstr_eq(strchr(str, sym), s21_strchr(str, sym));
}
END_TEST

START_TEST(_void_sym) {
  char str[32] = "kittens are very cute! meow";
  int sym = ' ';

  ck_assert_pstr_eq(strchr(str, sym), s21_strchr(str, sym));
}
END_TEST

START_TEST(_register) {
  char str[32] = "kittens are very cutE! meow";
  int sym = 'E';

  ck_assert_pstr_eq(strchr(str, sym), s21_strchr(str, sym));
}
END_TEST

START_TEST(_default_sym) {
  char str[32] = "kittens are very cutE! meow";
  int sym = '!';

  ck_assert_pstr_eq(strchr(str, sym), s21_strchr(str, sym));
}
END_TEST

START_TEST(_default_end) {
  char str[32] = "kittens are very cutE! meow";
  int sym = 'w';

  ck_assert_pstr_eq(strchr(str, sym), s21_strchr(str, sym));
}
END_TEST

START_TEST(_without_sym_in_str) {
  char str[32] = "kittens are very cutE! meow";
  int sym = 'x';

  ck_assert_pstr_eq(strchr(str, sym), s21_strchr(str, sym));
}
END_TEST

START_TEST(_sym_0) {
  char str[32] = "kittens are very cutE! meow";
  int sym = '\0';

  ck_assert_pstr_eq(strchr(str, sym), s21_strchr(str, sym));
}
END_TEST

Suite *strchr_suite() {
  Suite *s = suite_create("Tests for strchr");
  TCase *tc = tcase_create("Tests for strchr");

  tcase_add_test(tc, _default);
  tcase_add_test(tc, _void_str);
  tcase_add_test(tc, _void_sym);
  tcase_add_test(tc, _register);
  tcase_add_test(tc, _default_sym);
  tcase_add_test(tc, _default_end);
  tcase_add_test(tc, _without_sym_in_str);
  tcase_add_test(tc, _sym_0);

  suite_add_tcase(s, tc);

  return s;
}
