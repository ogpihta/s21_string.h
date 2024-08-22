#include "test_string.h"

START_TEST(_default) {
  char str[] = "kitties !!";
  int sym = 't';
  ck_assert_ptr_eq(strrchr(str, sym), s21_strrchr(str, sym));
}
END_TEST

START_TEST(_void_str) {
  char str[] = "";
  int sym = 't';
  ck_assert_ptr_eq(strrchr(str, sym), s21_strrchr(str, sym));
}
END_TEST

START_TEST(_void_sym) {
  char str[] = "kitties!!";
  int sym = ' ';
  ck_assert_ptr_eq(strrchr(str, sym), s21_strrchr(str, sym));
}
END_TEST

START_TEST(_without_sym_in_str) {
  char str[] = "kitties !!";
  int sym = 'x';
  ck_assert_ptr_eq(strrchr(str, sym), s21_strrchr(str, sym));
}
END_TEST

START_TEST(_zero_sym) {
  char str[] = "kitties !!";
  int sym = '\0';
  ck_assert_ptr_eq(strrchr(str, sym), s21_strrchr(str, sym));
}
END_TEST

START_TEST(_zero_sym_2) {
  char str[] = "kitties !! \0 <3";
  int sym = '\0';
  ck_assert_ptr_eq(strrchr(str, sym), s21_strrchr(str, sym));
}
END_TEST

START_TEST(_register) {
  char str[] = "kittens are very cutE! meow";
  int sym = 'E';
  ck_assert_ptr_eq(strrchr(str, sym), s21_strrchr(str, sym));
}
END_TEST

START_TEST(_sym_num) {
  char str[] = "kittens are very cutE! <<3 meow <<3";
  int sym = '3';
  ck_assert_ptr_eq(strrchr(str, sym), s21_strrchr(str, sym));
}
END_TEST

Suite *strrchr_suite() {
  Suite *s = suite_create("Tests for strrchr");
  TCase *tc = tcase_create("Tests for strrchr");

  tcase_add_test(tc, _default);
  tcase_add_test(tc, _void_str);
  tcase_add_test(tc, _void_sym);
  tcase_add_test(tc, _without_sym_in_str);
  tcase_add_test(tc, _zero_sym);
  tcase_add_test(tc, _zero_sym_2);
  tcase_add_test(tc, _register);
  tcase_add_test(tc, _sym_num);

  suite_add_tcase(s, tc);

  return s;
}
