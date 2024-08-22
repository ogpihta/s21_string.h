#include "test_string.h"

START_TEST(_to_upper_1) {
  char str_original[] = "hhhQQQjjjQwerty";
  char str_upper[] = "HHHQQQJJJQWERTY";

  char *res = s21_to_upper(str_original);

  ck_assert_str_eq(str_upper, res);
  free(res);
}
END_TEST

START_TEST(_to_upper_zero) {
  char str_original[] = "\0";
  char str_upper[] = "\0";

  char *res = s21_to_upper(str_original);

  ck_assert_str_eq(str_upper, res);
  free(res);
}
END_TEST

START_TEST(_to_upper_void_str) {
  char str_original[] = " ";
  char str_upper[] = " ";

  char *res = s21_to_upper(str_original);

  ck_assert_str_eq(str_upper, res);
  free(res);
}
END_TEST

START_TEST(_to_upper_different_1) {
  char str_original[] = "  asdfGHJKL;zxc1234  ";
  char str_upper[] = "  ASDFGHJKL;ZXC1234  ";

  char *res = s21_to_upper(str_original);

  ck_assert_str_eq(str_upper, res);
  free(res);
}
END_TEST

START_TEST(_to_upper_different_2) {
  char str_original[] = "\n\tDaY123no_zaza\\";
  char str_upper[] = "\n\tDAY123NO_ZAZA\\";

  char *res = s21_to_upper(str_original);

  ck_assert_str_eq(str_upper, res);
  free(res);
}
END_TEST

START_TEST(_to_upper_different_3) {
  char str_original[] = "lal lalala loa    loaaa  ";
  char str_upper[] = "LAL LALALA LOA    LOAAA  ";

  char *res = s21_to_upper(str_original);

  ck_assert_str_eq(str_upper, res);
  free(res);
}
END_TEST

Suite *to_upper_suite() {
  Suite *s = suite_create("Tests for to_upper");
  TCase *tc = tcase_create("Tests for to_upper");

  tcase_add_test(tc, _to_upper_1);
  tcase_add_test(tc, _to_upper_zero);
  tcase_add_test(tc, _to_upper_void_str);
  tcase_add_test(tc, _to_upper_different_1);
  tcase_add_test(tc, _to_upper_different_2);
  tcase_add_test(tc, _to_upper_different_3);

  suite_add_tcase(s, tc);

  return s;
}
