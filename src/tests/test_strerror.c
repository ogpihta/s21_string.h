#include "test_string.h"

START_TEST(_all_errors) {
  for (int i = 0; i < SIZE_OF_ERRORLIST; i++) {
    char *result = s21_strerror(i);
    char *expected = strerror(i);
    ck_assert_str_eq(expected, result);
  }
}
END_TEST

START_TEST(_unknown_errors_more) {
  for (int i = SIZE_OF_ERRORLIST; i < 150; i++) {
    char *result = s21_strerror(i);
    char *expected = strerror(i);
    ck_assert_str_eq(expected, result);
  }
}
END_TEST

START_TEST(_unknown_errors_less) {
  for (int i = -100; i < 0; i++) {
    char *result = s21_strerror(i);
    char *expected = strerror(i);
    ck_assert_str_eq(expected, result);
  }
}
END_TEST

Suite *strerror_suite() {
  Suite *s = suite_create("Tests for strerror");
  TCase *tc = tcase_create("Tests for strerror");

  tcase_add_test(tc, _all_errors);
  tcase_add_test(tc, _unknown_errors_more);
  tcase_add_test(tc, _unknown_errors_less);

  suite_add_tcase(s, tc);

  return s;
}
