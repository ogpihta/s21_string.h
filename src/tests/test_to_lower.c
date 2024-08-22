#include "test_string.h"

START_TEST(_to_lower_1) {
  char original[] = "hhhQQQjJjQweRTy";
  char str_lower[] = "hhhqqqjjjqwerty";

  char *res = s21_to_lower(original);
  ck_assert_str_eq(str_lower, res);
  free(res);
}
END_TEST

START_TEST(_to_lower_zero) {
  char original[] = "\0";
  char str_lower[] = "\0";

  char *res = s21_to_lower(original);
  ck_assert_str_eq(str_lower, res);
  free(res);
}
END_TEST

START_TEST(_to_lower_void_str) {
  char original[] = " ";
  char str_lower[] = " ";

  char *res = s21_to_lower(original);
  ck_assert_str_eq(str_lower, res);
  free(res);
}
END_TEST

START_TEST(_to_lower_different_1) {
  char original[] = "  asdfGHJKL;zxC1234  ";
  char str_lower[] = "  asdfghjkl;zxc1234  ";

  char *res = s21_to_lower(original);
  ck_assert_str_eq(str_lower, res);
  free(res);
}
END_TEST

START_TEST(_to_lower_different_2) {
  char original[] = "\n\tDaY123nO. _ZAZA\\";
  char str_lower[] = "\n\tday123no. _zaza\\";

  char *res = s21_to_lower(original);
  ck_assert_str_eq(str_lower, res);
  free(res);
}
END_TEST

START_TEST(_to_lower_different_3) {
  char original[] = "LAL LALALA LOA    LOAAA  ";
  char str_lower[] = "lal lalala loa    loaaa  ";

  char *res = s21_to_lower(original);
  ck_assert_str_eq(str_lower, res);
  free(res);
}
END_TEST

Suite *to_lower_suite() {
  Suite *s = suite_create("Tests for to_lower");
  TCase *tc = tcase_create("Tests for to_lower");

  tcase_add_test(tc, _to_lower_1);
  tcase_add_test(tc, _to_lower_zero);
  tcase_add_test(tc, _to_lower_void_str);
  tcase_add_test(tc, _to_lower_different_1);
  tcase_add_test(tc, _to_lower_different_2);
  tcase_add_test(tc, _to_lower_different_3);

  suite_add_tcase(s, tc);

  return s;
}
