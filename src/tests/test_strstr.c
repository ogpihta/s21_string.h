#include "test_string.h"

START_TEST(_default) {
  char str1[] = "kittens are very cute! <333 ";
  char str2[] = "cute!";

  ck_assert_ptr_eq(strstr(str1, str2), s21_strstr(str1, str2));
}
END_TEST

START_TEST(_default_2) {
  char str1[] = "kittens are very cute! <333 ";
  char str2[] = "kitty";

  ck_assert_ptr_eq(strstr(str1, str2), s21_strstr(str1, str2));
}
END_TEST

START_TEST(_sym_num) {
  char str1[] = "kittens are very cute! <333 ";
  char str2[] = "<3";

  ck_assert_ptr_eq(strstr(str1, str2), s21_strstr(str1, str2));
}
END_TEST

START_TEST(_default_without_str2) {
  char str1[] = "kittens are very cute! <333 ";
  char str2[] = "puppies";

  ck_assert_ptr_eq(strstr(str1, str2), s21_strstr(str1, str2));
}
END_TEST

START_TEST(_void_str1) {
  char str1[] = " ";
  char str2[] = "cute!";

  ck_assert_ptr_eq(strstr(str1, str2), s21_strstr(str1, str2));
}
END_TEST

START_TEST(_void_str2) {
  char str1[] = "kittens are very cute! <333 ";
  char str2[] = " ";

  ck_assert_ptr_eq(strstr(str1, str2), s21_strstr(str1, str2));
}
END_TEST

START_TEST(_void_all) {
  char str1[] = " ";
  char str2[] = " ";

  ck_assert_ptr_eq(strstr(str1, str2), s21_strstr(str1, str2));
}
END_TEST

Suite *strstr_suite() {
  Suite *s = suite_create("Tests for strstr");
  TCase *tc = tcase_create("Tests for strstr");

  tcase_add_test(tc, _default);
  tcase_add_test(tc, _default_2);
  tcase_add_test(tc, _sym_num);
  tcase_add_test(tc, _default_without_str2);
  tcase_add_test(tc, _void_str1);
  tcase_add_test(tc, _void_str2);
  tcase_add_test(tc, _void_all);

  suite_add_tcase(s, tc);

  return s;
}
