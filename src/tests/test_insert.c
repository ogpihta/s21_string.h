#include "test_string.h"

START_TEST(_insert_1) {
  const char original[] = "chto vi delaete v holodilnike";
  const char insert_str[] = "moem ";
  s21_size_t start_index = 18;
  char result[] = "chto vi delaete v moem holodilnike";

  char *res = s21_insert(original, insert_str, start_index);

  ck_assert_str_eq(result, res);
  if (res) free(res);
}
END_TEST

START_TEST(_insert_2) {
  const char original[] = "kak dela";
  const char insert_str[] = "privet, ";
  s21_size_t start_index = 0;
  char result[] = "privet, kak dela";

  char *res = s21_insert(original, insert_str, start_index);

  ck_assert_str_eq(result, res);
  if (res) free(res);
}
END_TEST

START_TEST(_insert_zero) {
  const char original[] = "\0";
  const char insert_str[] = "utro";
  s21_size_t start_index = 0;
  char result[] = "utro";

  char *res = s21_insert(original, insert_str, start_index);

  ck_assert_str_eq(result, res);
  if (res) free(res);
}
END_TEST

START_TEST(_insert_n) {
  const char original[] = ".\n\n.";
  const char insert_str[] = "a";
  s21_size_t start_index = 2;
  char result[] = ".\na\n.";

  char *res = s21_insert(original, insert_str, start_index);

  ck_assert_str_eq(result, res);
  if (res) free(res);
}
END_TEST

START_TEST(_insert_add_zero) {
  const char original[] = "vorobei";
  const char insert_str[] = "\0";
  s21_size_t start_index = 4;
  char result[] = "vorobei";

  char *res = s21_insert(original, insert_str, start_index);

  ck_assert_str_eq(result, res);
  if (res) free(res);
}
END_TEST

START_TEST(_insert_last_position) {
  const char original[] = "a";
  const char insert_str[] = "a";
  s21_size_t start_index = 1;
  char result[] = "aa";

  char *res = s21_insert(original, insert_str, start_index);

  ck_assert_str_eq(result, res);
  if (res) free(res);
}
END_TEST

START_TEST(_insert_4) {
  const char original[] = "eshkere";
  const char insert_str[] = "dabchik";
  s21_size_t start_index = 7;
  char result[] = "eshkeredabchik";

  char *res = s21_insert(original, insert_str, start_index);

  ck_assert_str_eq(result, res);
  if (res) free(res);
}
END_TEST

Suite *insert_suite() {
  Suite *s = suite_create("Tests for insert");
  TCase *tc = tcase_create("Tests for insert");

  tcase_add_test(tc, _insert_1);
  tcase_add_test(tc, _insert_2);
  tcase_add_test(tc, _insert_zero);
  tcase_add_test(tc, _insert_n);
  tcase_add_test(tc, _insert_add_zero);
  tcase_add_test(tc, _insert_last_position);
  tcase_add_test(tc, _insert_4);

  suite_add_tcase(s, tc);

  return s;
}
