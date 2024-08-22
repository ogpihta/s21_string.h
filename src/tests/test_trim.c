#include "test_string.h"

void *s21_trim(const char *src, const char *trim_chars);

START_TEST(_trim_different_1) {
  const char str_original[] = "-------- . meow . -----";
  const char trim_chars[] = "-";
  char str_trimmed[] = " . meow . ";

  char *res = s21_trim(str_original, trim_chars);

  ck_assert_str_eq(str_trimmed, res);
  free(res);
}
END_TEST

START_TEST(_trim_backslashn) {
  char str_original[] = "\n-------- . meow . -----\n";
  char trim_chars[] = "\n";
  char str_trimmed[] = "-------- . meow . -----";

  char *res = s21_trim(str_original, trim_chars);

  ck_assert_str_eq(str_trimmed, res);
  free(res);
}
END_TEST

START_TEST(_trim_space) {
  char str_original[] = "        asdf           ";
  char trim_chars[] = " ";
  char str_trimmed[] = "asdf";

  char *res = s21_trim(str_original, trim_chars);

  ck_assert_str_eq(str_trimmed, res);
  free(res);
}
END_TEST

START_TEST(_trim_zero) {
  char str_original[] = "\0";
  char trim_chars[] = "\0";
  char str_trimmed[] = "\0";

  char *res = s21_trim(str_original, trim_chars);

  ck_assert_str_eq(str_trimmed, res);
  free(res);
}
END_TEST

START_TEST(_trim_different_2) {
  char str_original[] = "ffffasdfasAAAfasdasdfAAasfadasdff";
  char trim_chars[] = "asdf";
  char str_trimmed[] = "AAAfasdasdfAA";

  char *res = s21_trim(str_original, trim_chars);

  ck_assert_str_eq(str_trimmed, res);
  free(res);
}
END_TEST

START_TEST(_trim_different_3) {
  char str_original[] = "+!!++Abo+ba++00";
  char trim_chars[] = "+!0-";
  char str_trimmed[] = "Abo+ba";

  char *res = s21_trim(str_original, trim_chars);

  ck_assert_str_eq(str_trimmed, res);
  free(res);
}
END_TEST

Suite *trim_suite() {
  Suite *s = suite_create("Tests for trim");
  TCase *tc = tcase_create("Tests for trim");

  tcase_add_test(tc, _trim_different_1);
  tcase_add_test(tc, _trim_backslashn);
  tcase_add_test(tc, _trim_space);
  tcase_add_test(tc, _trim_zero);
  tcase_add_test(tc, _trim_different_2);
  tcase_add_test(tc, _trim_different_3);

  suite_add_tcase(s, tc);

  return s;
}
